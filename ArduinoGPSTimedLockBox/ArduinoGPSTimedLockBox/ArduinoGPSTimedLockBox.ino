/*
 Name:		ArduinoGPSTimedLockBox.ino
 Created:	3/28/2020 3:42:30 PM
 Author:	William Taylor
*/

#include "UserInput.h"
#include "NeoPhysical.h"
#include "Setup.h"
//#include "Temporal.h"
//#include "Display.h"

#include <NeoSWSerial.h>
#include <NMEAGPS.h>
#include <Time.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <string.h>
#include <Wire.h>
#include <Streamers.h>

Setup systemConfig;
NeoPhysical gps;
//Temporal realTimeClock;
//Display display;

void setup() {
    Serial.begin(9600);
    systemConfig.Initialize();
}

void loop() {
    latLongLocation loc1 = systemConfig.getCurrentPointLocation();
    Serial.println(loc1.latitude);
    Serial.println(gps.GetAbsoluteDistanceFromPoint(loc1));
}
