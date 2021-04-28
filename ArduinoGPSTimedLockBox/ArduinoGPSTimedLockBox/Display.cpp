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

void Display::Write(char *lineOne, char *lineTwo)
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

void Display::DaysHoursMinutes(uint8_t days, uint8_t hours, uint8_t minutes)
{
	if (days + hours + minutes <= 0)
	{
		Write("Less than", "a minute");
	}
	else
	{
		//Write(String(days) + " Days " + String(hours) + " Hours", String(minutes) + " Minutes");
	}
}

void Display::DelayClear()
{
	delay(3000);
	Clear();
}

void Display::WriteSearchBeginsIn(uint8_t days, uint8_t hours, uint8_t minutes)
{
	//Write("Search will", "begin in...");
	delay(3000);
	DaysHoursMinutes(days, hours, minutes);
	DelayClear();
}

void Display::WriteNextStageBeginsNow()
{
	//Write("Next stage", "commencing");
	DelayClear();
}

void Display::WriteStageXOfYComplete(uint8_t currentPoint, uint8_t totalPoints)
{
	//Write("Stage " + String(currentPoint) + " of " + String(totalPoints), "complete");
	DelayClear();
}

void Display::WriteObtainingGPSLocationFix()
{
	//Write("Obtaining GPS", "location fix...");
}

void Display::WriteDistanceRemaining(uint32_t distance)
{
	Clear();
	//Write("Distance to", "location...");
	delay(3000);
	//Write(String(distance) + " Meters");
	DelayClear();
}

void Display::WriteLocationReached()
{
	Clear();
	//Write("Location has", "been found");
	DelayClear();
}

void Display::WriteTimeToUnlock(uint8_t days, uint8_t hours, uint8_t minutes)
{
	//Write("Unlock window", "will start in...");
	delay(3000);
	//DaysHoursMinutes(days, hours, minutes);
	DelayClear();
}

void Display::WriteUnlockTimeRemaining(uint8_t days, uint8_t hours, uint8_t minutes)
{
	//Write("Unlock window", "will last for...");
	delay(3000);
	DaysHoursMinutes(days, hours, minutes);
	DelayClear();
}

void Display::WriteSerialMode()
{
	//Write("Serial mode");
}

void Display::WriteCalibratingRTC()
{
	//Write("Calibrating RTC", "from GPS fix...");
}

void Display::WriteRTCOffBy(uint32_t delta)
{
	//Write("Real Time Clock", "was off by...");
	delay(3000);
	//Write(String(delta), "Seconds");
	DelayClear();
}

void Display::WriteTimeExtensionValues(uint8_t hours, uint8_t mins)
{
	//Write("Enter Value:");
	lcd->setCursor(0, 1);
	if (hours < 10) {
		lcd->print('0');
		lcd->setCursor(1, 1);
	}
	lcd->print(hours);
	lcd->setCursor(14, 1);
	if (mins < 10) {
		lcd->print('0');
		lcd->setCursor(15, 1);
	}
	lcd->print(mins);
}

void Display::WriteTimeExtended()
{
	//Write("Time Extended");
	DelayClear();
}

void Display::WriteEnterPasscode()
{
	//Write("Passcode:");
}

void Display::CharTyped(uint8_t dotCount)
{
	lcd->setCursor(dotCount, 1);
	//lcd->print("*");
}

void Display::WriteInsertBothKeys()
{
	//Write("Insert second", "key to unlock");
	DelayClear();
}

void Display::WriteAccessGranted()
{
	//Write("Access Granted", "Welcome");
	DelayClear();
}

void Display::WriteAccessDenied()
{
	//Write("Access Denied");
	DelayClear();
}

void Display::WriteTooLate()
{
	Clear();
	//Write("Too Late", "Window Missed");
	DelayClear();
}

void Display::WriteGoodbye()
{
	//Write("Goodbye");
	DelayClear();
}

void Display::Clear()
{
	lcd->setCursor(0, 0);
	lcd->print("                ");
	lcd->setCursor(0, 1);
	lcd->print("                ");
}