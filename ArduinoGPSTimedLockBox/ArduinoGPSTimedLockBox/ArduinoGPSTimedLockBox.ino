/*
 Name:		ArduinoGPSTimedLockBox.ino
 Created:	3/28/2020 3:42:30 PM
 Author:	William Taylor
*/

#include "Setup.h"
//#include "Physical.h"
//#include "Temporal.h"
//#include "Display.h"

#include <Time.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <string.h>
#include <SoftwareSerial.h>
#include <Wire.h>

Setup userInput;
//Physical gps;
//Temporal realTimeClock;
//Display display;

void setup() {
    Serial.begin(9600);
    configureUnit();
}

void loop() {
  
}

void configureUnit() {
    userInput.InitialConfiguration();
}

