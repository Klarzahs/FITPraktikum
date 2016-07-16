#include <Arduino.h>
#include <LowPower.h>

/*
2015-04-06 : Johan Boeckx - Arduino/RPi(2) nRF24L01+ : Arduino UNO R3 code
  Tested on Arduino UNO R3 and Raspberry Pi B Rev. 2.0 and Raspberry Pi 2 B


TMRh20 2014
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.
*/
/** Reliably transmitting large volumes of data with a low signal or in noisy environments
* This example demonstrates data transfer functionality with the use of auto-retry
and auto-reUse functionality enabled. This sketch demonstrates how a user can extend
the auto-retry functionality to any chosen time period, preventing data loss and ensuring
the consistency of data.

This sketh demonstrates use of the writeBlocking() functionality, and extends the standard
retry functionality of the radio. Payloads will be auto-retried until successful or the
extended timeout period is reached.
*/
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"


/*************  RADIO Configuration *****************************/
RF24 radio(9,10);                        // Set up nRF24L01 radio on SPI bus plus pins 7 & 8
unsigned long timeoutPeriod = 3000;     // Set a user-defined timeout period. With auto-retransmit set to (15,15) retransmission will take up to 60ms and as little as 7.5ms with it set to (1,15).
                                        // With a timeout period of 1000, the radio will retry each payload for up to 1 second before giving up on the transmission and starting over

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };   // Radio pipe addresses for the 2 nodes to communicate.
byte data[32] = {""};                           //Data buffer
volatile byte counter;
unsigned long rxTimer,startTime, stopTime, payloads = 0;
//bool TX=1,RX=0,role=0, transferInProgress = 0;
bool transferInProgress = 0;
unsigned int TX=1,RX=0,role=1,lastrole=0,SKIP=2,RXPRINT=3,RXDUMP=4;
unsigned int offset=0;

#define ID 1337

/*************  TSL Configuration *****************************/
// connect SCL to analog 5
// connect SDA to analog 4
// connect Vin to 3.3-5V DC
// connect GROUND to common ground

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); 

/*************  FUNCTIONS *****************************/

void displaySensorDetails(void)
{
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void configureSensor(void)
{
  tsl.setGain(TSL2591_GAIN_MED); 
  tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS); 
}

void setup(void) {
  Serial.begin(9600);
  if (tsl.begin()) 
  {
    Serial.println("Found a TSL2591 sensor");
  } 
  else 
  {
    Serial.println("No sensor found ... check your wiring?");
    while (1);
  }
    
  displaySensorDetails();
  configureSensor();

  printf_begin();
  radio.begin();                          
  
  radio.setChannel(1);                     // Set the channel
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  //radio.setDataRate(RF24_2MBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries. Want the number of auto-retries as high as possible (15)
  radio.setCRCLength(RF24_CRC_16);         // Set CRC length to 16-bit to ensure quality of data

  radio.openWritingPipe(pipes[1]);         // Open the default reading and writing pipe
  radio.openReadingPipe(1,pipes[0]);
  radio.stopListening();
  printf("\n\rRF24 Sender online!\n\r");
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging

  //radio.powerUp();                        //Power up the radio
}

void sleep()
{
  for (int i = 0; i < 8; i++) { 
     LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  }
}

void showData(void)
{
      printf("Data: ");
      for(int i=0; i<32; i++){
        if(data[i] != 0){
          Serial.print(i);
          Serial.print(": ");
          Serial.println(data[i]);
        }
      }
      printf("\n\r");
}

void loop(void){                                           
  if(radio.txStandBy(timeoutPeriod)){                       // If transfer initiation was successful, do the following

      boolean timedOut = 0;  

      data[0] = ID;
      data[1] = counter;
      
      uint32_t lum = tsl.getFullLuminosity();
      uint16_t ir, full;
      ir = lum >> 16;
      full = lum & 0xFFFF;
      data[2] = ir >> 8;
      data[3] = ir & 0xFF;
      data[4] = lum >> 8;
      data[5] = lum & 0xFF;
      Serial.print("[ "); Serial.print(millis()); Serial.print(" ms ] ");
      Serial.print("IR: "); Serial.print(ir);  Serial.print("  ");
      Serial.print("Full: "); Serial.print(full); Serial.print("  ");
      Serial.print("Visible: "); Serial.print(full - ir); Serial.print("  ");
      Serial.print("Lux: "); Serial.println(tsl.calculateLux(full, ir));
      
      if(!radio.writeBlocking(&data,32,timeoutPeriod)){   // If retries are failing and the user defined timeout is exceeded
          timedOut = 1;                                   // Indicate failure
          Serial.println("Failure!");
      }
      counter++;
     //This should be called to wait for completion and put the radio in standby mode after transmission, returns 0 if data still in FIFO (timed out), 1 if success
     if(timedOut){ radio.txStandBy(); }                     //Partially blocking standby, blocks until success or max retries. FIFO flushed if auto timeout reached
     else{ radio.txStandBy(timeoutPeriod);     }            //Standby, block until FIFO empty (sent) or user specified timeout reached. FIFO flushed if user timeout reached.

 }else{
     Serial.println("Communication not established");       //If unsuccessful initiating transfer, exit and retry later
 }
  showData();
  sleep();
}
