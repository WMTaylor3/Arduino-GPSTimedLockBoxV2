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
    display.WriteAccessDenied();

    switch (input.getStartUpMode())
    {
    case(normal):
        RunNormal();
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
        RunNormal();
        break;
    }
}

void RunNormal() {

}

void RunOverride() {
    input.validateCodeForStartupMode(overrideUnlock);
}

void RunExtraTime() {
    input.validateCodeForStartupMode(extraTime);
}

void RunCalibrateRTC() {
    input.validateCodeForStartupMode(calibrateClock);
}

void RunConfigureUnit() {
    input.validateCodeForStartupMode(configureUnit);
}

void loop() {
    // Empty. The unit runs once per power cycle.
}
