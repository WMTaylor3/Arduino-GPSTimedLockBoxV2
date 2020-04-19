/*
 Name:		Arduino_MomentMaker.ino
 Created:	6/8/2019 2:17:32 PM
 Author:	William Taylor
*/

#include "Display.h"

//Slider
#define screenI2C 0x27
// Hook
//#define screenI2C 0x38

LiquidCrystal_I2C* Display::lcd = new LiquidCrystal_I2C(screenI2C, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

Display::Display()
{
}

void Display::Initialize()
{
	lcd->begin(16, 2);
}

void Display::LcdOn()
{
	lcd->on();
}

void Display::LcdOff()
{
	lcd->off();
}

void Display::Write(String lineOne, String lineTwo = "")
{
	Clear();
	lcd->setCursor(0, 0);
	lcd->print(lineOne);
	if (lineTwo != "")
	{
		lcd->setCursor(0, 1);
		lcd->print(lineTwo);
	}
}

void Display::WriteSearchBeginsIn(uint32_t days, uint32_t hours, uint32_t minutes)
{
	Clear();
	Write("Search will", "begin in...");
	delay(3000);
	if (days + hours + minutes <= 0)
	{
		Write("Less than", "a minute");
	}
	String dayString = String(days);
	String hourString = String(hours);
	String minuteString = String(minutes);
	Write(dayString + " Days " + hourString + " Hours", minuteString + " Minutes");
	delay(3000);
	Clear();
}

void Display::WriteNextStageBeginsNow()
{
	Clear();
	Write("Next stage", "commencing");
	delay(3000);
	Clear();
}

void Display::WriteStageXOfYComplete(uint8_t currentPoint, uint8_t totalPoints)
{
	Clear();
	String currentPointString = String(currentPoint);
	String totalPointsString = String(totalPoints);
	Write("Stage #" + currentPointString + " of " + totalPointsString, "complete");
	delay(3000);
	Clear();
}

void Display::WriteObtainingGPSLocationFix()
{
	Clear();
	Write("Obtaining GPS", "location fix...");
	delay(3000);
	Clear();
}

void Display::WriteDistanceRemaining(uint32_t distance)
{
	Clear();
	Write("Distance to", "location...");
	delay(3000);
	String distanceString = String(distance);
	Write(distanceString + " Meters");
	delay(3000);
	Clear();
}

void Display::WriteLocationReached()
{
	Clear();
	Write("Location has", "been found");
	delay(3000);
	Clear();
}

void Display::WriteTimeToUnlock(uint32_t days, uint32_t hours, uint32_t minutes)
{
	Clear();
	Write("Unlock window", "will start in...");
	delay(3000);
	if (days + hours + minutes <= 0)
	{
		Write("Less than", "a minute");
	}
	String dayString = String(days);
	String hourString = String(hours);
	String minuteString = String(minutes);
	Write(dayString + " Days " + hourString + " Hours", minuteString + " Minutes");
	delay(3000);
	Clear();
}

void Display::WriteUnlockTimeRemaining(uint32_t days, uint32_t hours, uint32_t minutes)
{
	Clear();
	Write("Unlock window", "will last for...");
	delay(3000);
	if (days + hours + minutes <= 0)
	{
		Write("Less than", "a minute");
	}
	String dayString = String(days);
	String hourString = String(hours);
	String minuteString = String(minutes);
	Write(dayString + " Days " + hourString + " Hours", minuteString + " Minutes");
	delay(3000);
	Clear();
}

void Display::WriteSerialMode()
{
	Clear();
	Write("Serial mode");
}

void Display::WriteCalibratingRTC()
{
	Clear();
	Write("Calibrating RTC", "from GPS fix...");
}

void Display::WriteRTCOffBy(uint32_t delta)
{
	Clear();
	Write("Real Time Clock", "was off by...");
	delay(3000);
	Write(String(delta), "Seconds");
	delay(3000);
	Clear();
}

void Display::WriteTimeExtensionValues(uint8_t hours, uint8_t mins)
{
	Clear();
	Write("Enter Value:");
	lcd->setCursor(0, 1);
	if (hours < 10) {
		lcd->print('0');
		lcd->setCursor(1, 1);
	}
	String hoursString = String(hours);
	lcd->print(hoursString);
	lcd->setCursor(14, 1);
	if (mins < 10) {
		lcd->print('0');
		lcd->setCursor(15, 1);
	}
	String minutesString = String(mins);
	lcd->print(mins);
	delay(3000);
	Clear();
}

void Display::WriteTimeExtended()
{
	Clear();
	Write("Time Extended", "Goodbye!");
	delay(3000);
	Clear();
}

void Display::WriteEnterPasscode()
{
	Clear();
	Write("Passcode:");
	delay(3000);
	Clear();
}

void Display::CharTyped(uint8_t dotCount)
{
	lcd->setCursor(dotCount, 1);
	lcd->print("*");
}

void Display::WriteInsertBothKeys()
{
	Write("Insert second", "key to unlock");
	delay(3000);
	Clear();
}

void Display::WriteAccessGranted()
{
	Write("Access Granted", "Welcome");
	delay(3000);
	Clear();
}

void Display::WriteAccessDenied()
{
	Write("Access Denied");
	delay(3000);
	Clear();
}

void Display::WriteTooLate()
{
	Write("Too Late", "Window Missed");
	delay(3000);
	Clear();
}

void Display::WriteGoodbye()
{
	Write("Goodbye");
	delay(3000);
	Clear();
}

void Display::Clear()
{
	lcd->setCursor(0, 0);
	lcd->print("                ");
	lcd->setCursor(0, 1);
	lcd->print("                ");
}