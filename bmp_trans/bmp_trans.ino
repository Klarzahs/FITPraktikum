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

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP183.h>


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

#define ID 420
/*************  BMP Configuration *****************************/
#define BMP183_CLK  13
#define BMP183_SDO  12  // AKA MISO
#define BMP183_SDI  11  // AKA MOSI

// You'll also need a chip-select pin, use any pin!
#define BMP183_CS   4

Adafruit_BMP183 bmp = Adafruit_BMP183(BMP183_CS);   //BMP183_CLK, BMP183_SDO, BMP183_SDI, 

/*************  FUNCTIONS *****************************/
void setup(void) {
  Serial.begin(9600);
  if(!bmp.begin())
  {
    Serial.print("BMP183 inti failed");
    while(1);
  }

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
        Serial.print(i);
        Serial.print(": ");
        Serial.println(data[i]);
      }
      printf("\n\r");
}

void loop(void){                                         
  if(radio.txStandBy(timeoutPeriod)){                       // If transfer initiation was successful, do the following

      boolean timedOut = 0;  

      data[0] = ID;
      data[1] = counter;
      
      int32_t pressure = bmp.getPressure();
      uint32_t pres_u = *((uint32_t*)&pressure);
      data[2] = (byte)(pres_u >> 24);
      data[3] = (byte)(pres_u >> 16);
      data[4] = (byte)(pres_u >> 8);
      data[5] = (byte)(pres_u >> 0);

      float temperature = bmp.getTemperature();
      uint8_t temp_int = (uint8_t) temperature;;
      uint8_t temp_rest = (uint8_t)((temperature - temp_int) * 100);
      data[6] = temp_int;
      data[7] = temp_rest;
      Serial.print("Pressure: ");
      Serial.println(pres_u);
      Serial.print("Temperature: ");
      Serial.println(temperature);
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
