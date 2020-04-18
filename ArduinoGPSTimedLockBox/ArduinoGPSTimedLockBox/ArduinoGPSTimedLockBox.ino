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
#include <Servo.h>

// Slider
#define servoDegreesLock 10
#define servoDegreesUnlock 70

// Hook
//#define servoDegreesLock 80
//#define servoDegreesUnlock 165

Setup systemConfig;
Physical globalPositioningModule;
Temporal realTimeClock;
Display display;
UserInput input;
Servo servo;

void setup()
{
    Serial.begin(9600);

    //union convertUnsignedInt32_t {
    //    int32_t int32;
    //    byte byteArray[4];
    //} unsignedInt32Union;

    //uint8_t a = EEPROM.read(7);
    //uint8_t b = EEPROM.read(8);
    //uint8_t c = EEPROM.read(9);
    //uint8_t d = EEPROM.read(10);

    //Serial.println(a);
    //Serial.println(b);
    //Serial.println(c);
    //Serial.println(d);

    //unsignedInt32Union.byteArray[0] = EEPROM.read(11);
    //unsignedInt32Union.byteArray[1] = EEPROM.read(12);
    //unsignedInt32Union.byteArray[2] = EEPROM.read(13);
    //unsignedInt32Union.byteArray[3] = EEPROM.read(14);
    //Serial.println(unsignedInt32Union.int32);

    //unsignedInt32Union.int32 = -900000000;
    //Serial.println(unsignedInt32Union.byteArray[0]);
    //Serial.println(unsignedInt32Union.byteArray[1]);
    //Serial.println(unsignedInt32Union.byteArray[2]);
    //Serial.println(unsignedInt32Union.byteArray[3]);


    //display.Initialize();

    //systemConfig.Initialize();

    systemConfig.LoadConfigFromEEPROM();
    //Serial.println();
    //Serial.println(systemConfig.GetCurrentPointActionTime());
    //Serial.println(systemConfig.GetCurrentPointLocation().latitude);
    //Serial.println(systemConfig.GetCurrentPointLocation().longitude);
    //Serial.println(systemConfig.GetCurrentPointGracePeriodEndTime());
    //systemConfig.ProgressToNextPoint();

    //switch (input.GetStartUpMode())
    //{
    //case(normal):
    //    RunNormal();
    //    break;
    //case(overrideUnlock):
    //    RunOverride();
    //    break;
    //case(extraTime):
    //    RunExtraTime();
    //    break;
    //case(calibrateClock):
    //    RunCalibrateRTC();
    //    break;
    //case(configureUnit):
    //    RunConfigureUnit();
    //    break;
    //default:
    //    RunNormal();
    //    break;
    //}
}

void RunNormal()
{

}

void RunOverride() {
    if (input.ValidateCodeForStartupMode(overrideUnlock))
    {
        display.WriteAccessGranted();
        Lock(false);
    }
    else
    {
        display.WriteAccessDenied();
    }
    delay(2000);
    Die();
}

void RunExtraTime()
{
    input.ValidateCodeForStartupMode(extraTime);
}

void RunCalibrateRTC()
{
    if (input.ValidateCodeForStartupMode(calibrateClock))
    {
        display.WriteCalibratingRTC();
        Serial.println(F("Calibrating RTC from GPS"));
        time_t currentTime = realTimeClock.GetCurrentDateTime();
        Serial.print(F("Current RTC time: "));
        Serial.println(currentTime);
        time_t newTime = globalPositioningModule.GetDateTimeInUtc();
        Serial.print(F("Current GPS time: "));
        Serial.println(newTime);
        realTimeClock.SetCurrentTime(newTime);
        delay(2000);
        uint32_t delta = abs(newTime - currentTime);
        Serial.print(F("Absolute time delta: "));
        Serial.println(delta);
        Serial.print(F("New RTC time: "));
        Serial.println(realTimeClock.GetCurrentDateTime());
        display.WriteRTCOffBy(delta);
    }
    else
    {
        display.WriteAccessDenied();
    }
    delay(2000);
    Die();
}

void RunConfigureUnit()
{
    input.ValidateCodeForStartupMode(configureUnit);
}

void Lock(bool lock)
{
    Serial.end();
    globalPositioningModule.SerialEnd();

    Servo servo;

    servo.attach(8);
    delay(200);
    if (lock)
    {
        servo.write(servoDegreesLock);
    }
    else
    {
        servo.write(servoDegreesUnlock);
    }
    delay(1000);
    servo.detach();

    Die();
}

void TooLate()
{
    display.WriteTooLate();
    while (true) {}
}

void Die()
{
    display.WriteGoodbye();
    display.Clear();
    display.LcdOff();
    while (true) {}
}

void loop()
{
    // Empty. The unit runs once per power cycle.
}
