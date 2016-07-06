/*
Adapted code from Johan Boeckx - Arduino/RPi(2) nRF24L01+ : Raspberry Pi (2)
Using RF24 lib: Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

Written by Thomas Schemmer (Thomas.Schemmer@rwth-aachen.de) for the Workshop at Fraunhofer FIT
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <RF24/RF24.h>

#include <bson.h>
#include <bcon.h>
#include <mongoc.h>

using namespace std;

RF24 radio(RPI_V2_GPIO_P1_22, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_4MHZ);


/********** User Config *********/
bool radioNumber = 0;
unsigned long timeoutPeriod = 3000;     

/*********** Defines **********/

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };   // Radio pipe addresses for the 2 nodes to communicate.
char data[32] = {"00000000000000000000000000000000"};            //Data buffer

mongoc_client_t *client;
mongoc_database_t *database;
mongoc_collection_t *dhtCol, tslCol, bmpCol;
bson_t  *command, reply, *insert;
bson_error_t error;
char *str;
bool retval;



void initRadio(void){
  printf("Init Radio´: ");
  
  radio.begin();
  radio.setRetries(15,15);
  radio.setChannel(1);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  memset(&data,'\0',sizeof(data));
  radio.startListening();

  printf("ok\n");
}

void cleanup(void){
   //Release our handles and clean up libmongoc
  bson_destroy (insert);
  bson_destroy (&reply);
  bson_destroy (command);
  bson_free (str);

  mongoc_collection_destroy (collection);
  mongoc_database_destroy (database);
  mongoc_client_destroy (client);
  mongoc_cleanup ();

  radio.stopListening();
}

char[] getTime(void){
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return buf;
}

void showData(void){
  printf("Data: ");
  for(int i=0; i<32; i++){
    if(data[i] != 0){
	    printf("data[%i]: %i, ", i, data[i]);
    }
  }
  printf("\n\r");
}

float calculateLux(uint16_t ch0, uint16_t ch1){
  //adapted from https://github.com/adafruit/Adafruit_TSL2591_Library/blob/master/Adafruit_TSL2591.cpp
  float    atime, again;
  float    cpl, lux;

  // Check for overflow conditions first
  if ((ch0 == 0xFFFF) | (ch1 == 0xFFFF))
  {
    // Signal an overflow
    return 0;
  }

  // current arduino settings
  atime = 100.0F;
  again = 25.0F;
  // cpl = (ATIME * AGAIN) / DF
  cpl = (atime * again) / 408.0F;

  // Alternate lux calculation
  lux = ( (float)ch0 - ( 1.7F * (float)ch1 ) ) / cpl;
  return lux;
}

void storeTSL(void){

  uint16_t ir = data[2] << 8 | data[3];
  uint16_t full = data[4] << 8 | data[5];

  float lux = calculateLux(full, ir);

  insert = BCON_NEW ("Sensor", BCON_INT32(data[0]), "Payloadnr", BCON_INT32(data[1]), "Timestamp", BCON_UTF8(getTime()), "Lux", BCON_DOUBLE(lux));

  if (!mongoc_collection_insert (tslCol, MONGOC_INSERT_NONE, insert, NULL, &error)) {
    fprintf (stderr, "%s\n", error.message);
  }
  fflush(stdout);
}

void storeDHT(void){
  uint32_t tempU;
  uint32_t humU;

  humU = data[2] << 24 | data[3] << 16 | data[4] << 8 | data[5];
  tempU = data[6] << 24 | data[7] << 16 | data[8] << 8 | data[9];

  double hum = *((double*)&humU);
  double temp = *((double*)&tempU);

  insert = BCON_NEW ("Sensor", BCON_INT32(data[0]), "Payloadnr", BCON_INT32(data[1]), "Timestamp", BCON_UTF8(getTime()), "Temperature", BCON_DOUBLE(temp), "Humidity", BCON_DOUBLE(hum));

  if (!mongoc_collection_insert (dhtCol, MONGOC_INSERT_NONE, insert, NULL, &error)) {
    fprintf (stderr, "%s\n", error.message);
  }
  fflush(stdout);
}

void storeBMP(void){
  int32_t pressure;
  uint32_t pres_u = data[2] << 24 | data[3] << 16 | data[4] << 8 | data[5];
  pressure = *((int32_t*)&pres_u);

  float temperature;
  uint8_t temp_int = data[6];
  uint8_t temp_rest = data[7];
  temperature = (float)temp_int + temp_rest / 100.0f;

  float altitude;
  altitude = 44330 * (1.0 - pow(pressure /101325,0.1903));  //Adafruit code from https://github.com/adafruit/Adafruit-BMP085-Library/blob/master/Adafruit_BMP085.h

  insert = BCON_NEW ("Sensor", BCON_INT32(data[0]), "Payloadnr", BCON_INT32(data[1]), "Timestamp", BCON_UTF8(getTime()), "Temperature", BCON_DOUBLE(temperature), "Pressure", BCON_INT32(pressure), "Altitude", BCON_DOUBLE(altitude));

  if (!mongoc_collection_insert (bmpCol, MONGOC_INSERT_NONE, insert, NULL, &error)) {
    fprintf (stderr, "%s\n", error.message);
  }
  fflush(stdout);
}

void storeData(void){
  //check which id the data is from
  switch(data[0]){
    case 420:
      storeBMP();
      break;
    case 42:
      storeDHT();
      break;
    case 1337:
      storeTSL();
      break;
    default:
      printf("Couldn't find adequate db/sensor: unknown number %i!\n", data[0]);
      break;
  }
}

int main(int argc, char** argv){
  //Create a new client instance
  mongoc_init ();
  client = mongoc_client_new ("mongodb://172.17.0.2:27017");

  database = mongoc_client_get_database (client, "weather_station");
  tslCol = mongoc_client_get_collection (client, "weather_station", "tslTable");
  bmpCol = mongoc_client_get_collection (client, "weather_station", "bmpTable");
  dhtCol = mongoc_client_get_collection (client, "weather_station", "dhtTable");

  radio.printDetails();

  while (1)
  {
      
      if(radio.available()){
          // Read any available payloads for analysis
          radio.read(&data,32);
          // Dump the printable data of the payload
          showData();
          storeData();
      }
      delay(5);
  } // forever loop

  cleanup();
  return 0;
}
