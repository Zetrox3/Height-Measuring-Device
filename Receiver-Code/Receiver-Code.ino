/*
 Copyright (C) 2012 James Coliz, Jr. <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 
 Update 2014 - TMRh20
 */

/**
 * Simplest possible example of using RF24Network,
 *
 * RECEIVER NODE
 * Listens for messages from the transmitter and prints them out.
 */

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>


RF24 radio(7,8);                // nRF24L01(+) radio attached using Getting Started board 
LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

RF24Network network(radio);      // Network uses that radio
const uint16_t this_node = 00;    // Address of our node in Octal format ( 04,031, etc)
const uint16_t other_node = 01;   // Address of the other node in Octal format
int show;

struct payload_t {                 // Structure of our payload
  int measuredDistance;
};


void setup(void)
{
  Serial.begin(57600);
  
  int error;
  Serial.println("Height Measuring Sensor Display");

  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
 
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
  lcd.begin(16, 2); // initialize the lcd
  show = 0;
}
int measuredHeight = 0;
void loop(void){
  
  network.update();                  // Check the network regularly

  
  while ( network.available() ) {     // Is there anything ready for us?
    
    RF24NetworkHeader header;        // If so, grab it and print it out
    payload_t payload;
    network.read(header,&payload,sizeof(payload));
    Serial.print("Measured distance: ");
    measuredHeight = payload.measuredDistance;
    Serial.print(measuredHeight);
    if (measuredHeight > 0)
    {
      showHeightOnLCD (measuredHeight);
    }
  }
}

void showHeightOnLCD (int measuredHeight)
{
  
  lcd.setBacklight(255);
    //lcd.home(); lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Height (cm):");
    lcd.print(measuredHeight);
    lcd.setCursor(0, 1);
    lcd.print("Height (ft):");
    int heightInInches = measuredHeight / 2.54;
    int inches = heightInInches % 12;
    int feet = ((heightInInches - inches) / 12);
    
    lcd.print(feet);
    lcd.print("'");
    lcd.print(inches);
    lcd.print("\"");
}
