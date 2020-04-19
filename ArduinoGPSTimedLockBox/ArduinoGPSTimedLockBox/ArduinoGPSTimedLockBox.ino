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

    display.Initialize();

    systemConfig.Initialize();

    switch (input.GetStartUpMode())
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

void RunNormal()
{
    systemConfig.LoadConfigFromEEPROM();
    if (!realTimeClock.IsGameStartReached()) // Game hadn't started yet.
    {
        TimeSpanDuration timeUntilGameStart = realTimeClock.GetTimeUntilGameStart();
        display.WriteSearchBeginsIn(timeUntilGameStart.Days, timeUntilGameStart.Hours, timeUntilGameStart.Minutes);
        delay(2000);
        Die();
    }
    else // Game has started. Begin checking things like GPS and RTC.
    {
        if (!realTimeClock.HasWindowOpened()) // Before unlock window
        {
            display.WriteObtainingGPSLocationFix();
            if (globalPositioningModule.IsWithinRadius(systemConfig.GetCurrentPointLocation()))
            {
                display.WriteLocationReached();
            }
            else
            {
                display.WriteDistanceRemaining(globalPositioningModule.GetAbsoluteDistanceFromPoint(systemConfig.GetCurrentPointLocation()));
            }
            TimeSpanDuration timeUntilWindow = realTimeClock.GetTimeUntilWindowOpens();
            display.WriteTimeToUnlock(timeUntilWindow.Days, timeUntilWindow.Hours, timeUntilWindow.Minutes);

        }
        else if (realTimeClock.HasWindowOpened() && !realTimeClock.HasWindowExpired()) // Currently in unlock window
        {
            display.WriteObtainingGPSLocationFix();
            if (globalPositioningModule.IsWithinRadius(systemConfig.GetCurrentPointLocation()))
            {
                display.WriteLocationReached();
                if (systemConfig.IsFinalPoint())
                {
                    FinalPointReached();
                }
                else
                {
                    NextStageReached();
                }
            }
        }
        else if (realTimeClock.HasWindowExpired()) // After unlock window.
        {
            TooLate();
        }
    }
    Die();
}

void FinalPointReached()
{
    while (!realTimeClock.HasWindowExpired())
    {
        TimeSpanDuration remainingWindow = realTimeClock.GetTimeUntilWindowClose();
        display.WriteUnlockTimeRemaining(remainingWindow.Days, remainingWindow.Hours, remainingWindow.Minutes);
        if (input.IsKeyStateUnlocked())
        {
            display.WriteInsertBothKeys();
        }
        uint32_t startTime = millis();
        while (millis() - startTime >= 3000)
        {
            if (input.IsKeyStateUnlocked())
            {
                Lock(false);
            }
        }
    }
}

void NextStageReached()
{
    while (!realTimeClock.HasWindowExpired())
    {
        TimeSpanDuration remainingWindow = realTimeClock.GetTimeUntilWindowClose();
        uint8_t currentPoint = systemConfig.GetCurrentPointNumber();
        uint8_t totalPoints = systemConfig.GetTotalPointCount();
        display.WriteStageXOfYComplete(currentPoint, totalPoints);
        display.WriteNextStageBeginsNow();
        systemConfig.ProgressToNextPoint();
    }
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
    Die();
}

void RunExtraTime()
{
    if (input.ValidateCodeForStartupMode(extraTime))
    {
        uint32_t duration = input.GetExtraTimeValue();
        systemConfig.ExtendTime(duration, (realTimeClock.HasWindowOpened() && !realTimeClock.HasWindowExpired()));
        display.WriteTimeExtended();
    }
    Die();
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
    Die();
}

void RunConfigureUnit()
{
    if (input.ValidateCodeForStartupMode(configureUnit))
    {
        systemConfig.Initialize();
        Lock(false);
        input.AwaitKeyLock();
        Lock(true);
    }
    Die();
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
    Die();
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
