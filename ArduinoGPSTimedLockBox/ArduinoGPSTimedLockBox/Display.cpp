/*
 Name:		Arduino_MomentMaker.ino
 Created:	6/8/2019 2:17:32 PM
 Author:	William Taylor
*/

#include "Display.h"
//#define screenI2C 0x38
#define screenI2C 0x27

LiquidCrystal_I2C* Display::lcd = new LiquidCrystal_I2C(screenI2C, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

Display::Display()
{
}

void Display::Initialize()
{
	Display::lcd->begin(16, 2);
}

void Display::LcdOn()
{
	Display::lcd->on();
}

void Display::LcdOff()
{
	Display::lcd->off();
}

void Display::Write(String lineOne, String lineTwo = "")
{
	Clear();
	Display::lcd->setCursor(0, 0);
	Display::lcd->print(lineOne);
	if (lineTwo != "")
	{
		Display::lcd->setCursor(0, 1);
		Display::lcd->print(lineTwo);
	}
}

void Display::WriteSearchBeginsIn(uint32_t days, uint32_t hours, uint32_t minutes)
{
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

void Display::WriteNextStageBeginsIn(uint32_t days, uint32_t hours, uint32_t minutes)
{
	Write("Next stage will", "begin in...");
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

void Display::WriteObtainingGPSLocationFix()
{
	Write("Obtaining GPS", "location fix...");
}

void Display::WriteDistanceRemaining(uint32_t distance)
{
	Write("Distance to", "location...");
	delay(3000);
	String distanceString = String(distance);
	Write(distanceString + " Meters");
	delay(3000);
}

void Display::WriteLocationReached()
{
	Write("Location has", "been found");
	delay(3000);
}

void Display::WriteTimeToUnlock(uint32_t days, uint32_t hours, uint32_t minutes)
{
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
	Write("Serial mode");
}

void Display::WriteEnterValue()
{
	Write("Enter value: ");
}

void Display::WriteCalibratingRTC()
{
	Write("Calibrating RTC", "from GPS fix...");
}

void Display::WriteEnterPasscode()
{
	Write("Passcode:");
}

void Display::CharTyped(uint8_t dotCount)
{
	Display::lcd->setCursor(dotCount, 1);
	Display::lcd->print("*");
}

void Display::WriteInsertBothKeys()
{
	Write("Insert second", "key to unlock");
	delay(3000);
}

void Display::WriteTimeIncreasedBy(uint32_t days, uint32_t hours, uint32_t minutes)
{
	Write("Remaining time", "increased by...");
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

void Display::WriteAccessGranted()
{
	Write("Access Granted", "Welcome");
	delay(3000);
}

void Display::WriteAccessDenied()
{
	Write("Access Denied");
	delay(3000);
}

void Display::WriteTooLate()
{
	Write("Too Late", "Window Missed");
	delay(3000);
}

void Display::WriteGoodbye()
{
	Write("Goodbye");
	delay(3000);
}

void Display::Clear()
{
	Display::lcd->setCursor(0, 0);
	Display::lcd->print("                ");
	Display::lcd->setCursor(0, 1);
	Display::lcd->print("                ");
}