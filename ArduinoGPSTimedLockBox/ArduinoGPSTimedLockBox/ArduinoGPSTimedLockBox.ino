/*
 Name:		ArduinoGPSTimedLockBox.ino
 Created:	3/28/2020 3:42:30 PM
 Author:	William Taylor
*/

#include "Display.h"
#include "UserInput.h"
#include "Physical.h"
#include "Setup.h"
#include "SinglePointConfiguration.h"
#include "Temporal.h"

#include <NeoSWSerial.h>
#include <NMEAGPS.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <string.h>
#include <Wire.h>
#include <Streamers.h>

Setup systemConfig;
Physical gps;
Temporal realTimeClock;
Display display;
UserInput input;

void setup() {
    Serial.begin(9600);

    display.Initialize();
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
    if (input.validateCodeForStartupMode(overrideUnlock)) {
        display.WriteAccessGranted();
        Unlock();
    }
    else {
        display.WriteAccessDenied();
    }
    delay(2000);
    Die();
}

void RunExtraTime() {
    input.validateCodeForStartupMode(extraTime);
}

void RunCalibrateRTC() {
    if (input.validateCodeForStartupMode(calibrateClock) || true) {
        display.WriteCalibratingRTC();
        time_t currentTime = realTimeClock.GetCurrentDateTime();
        time_t newTime = gps.GetDateTimeInUtc();
        //realTimeClock.SetCurrentTime(newTime);
        //delay(1000);
        //uint32_t delta = abs(currentTime) - abs(newTime);
        //display.WriteRTCOffBy(delta);
    }
    else {
        display.WriteAccessDenied();
    }
    delay(2000);
    Die();
}

void RunConfigureUnit() {
    input.validateCodeForStartupMode(configureUnit);
}

void Lock() {
    // TODO: Implement
}

void Unlock() {
    // TODO: Implement.
}

void Die()
{
    display.WriteGoodbye();
    display.Clear();
    display.LcdOff();
    while (true) {}
}

void loop() {
    // Empty. The unit runs once per power cycle.
}
