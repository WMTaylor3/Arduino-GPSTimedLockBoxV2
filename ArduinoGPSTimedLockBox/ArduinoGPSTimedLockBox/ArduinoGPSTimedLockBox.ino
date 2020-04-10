/*
 Name:		ArduinoGPSTimedLockBox.ino
 Created:	3/28/2020 3:42:30 PM
 Author:	William Taylor
*/

#include "UserInput.h"
#include "NeoPhysical.h"
#include "Setup.h"
#include "Display.h"
//#include "Temporal.h"

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
Display display;
UserInput input;

void setup() {
    Serial.begin(9600);

    display.Initialize();
    display.LcdOn();

    switch (input.getStartUpMode())
    {
    case(normal):
        RunDefault();
        break;
    case(overrideUnlock):
        RunOverride();
        break;
    case(extraTime):
        RunExtraTime();
        break;
    case(calibrateClock):
        RunCalibrateRTC();
        break;
    case(configureUnit):
        RunConfigureUnit();
        break;
    default:
        RunDefault();
        break;
    }
}

void RunDefault() {

}

void RunOverride() {
    String enteredCode = "";
    uint8_t count = 0
}

void RunExtraTime() {

}

void RunCalibrateRTC() {

}

void RunConfigureUnit() {

}

void loop() {
    // Empty. The unit runs once per power cycle.
}
