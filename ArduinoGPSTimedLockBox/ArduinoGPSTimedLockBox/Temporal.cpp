/*
 Name:		Arduino_MomentMaker.ino
 Created:	6/8/2019 2:17:32 PM
 Author:	William Taylor
*/

#include "Temporal.h"
#include <Time.h>
#include <math.h>

DS1307RTC* Temporal::rtc = new DS1307RTC();

Temporal::Temporal()
{
}

TimeSpanDuration Temporal::ConvertToTimeSpanDuration(uint32_t duration)
{
	TimeSpanDuration dateTime;
	dateTime.Days = duration / 86400;
	dateTime.Hours = (duration % 86400) / 3600;
	dateTime.Minutes = ((duration % 86400) % 3600) / 60;
	dateTime.Seconds = (((duration % 86400) % 3600) % 60) / 60;
	return dateTime;
}

time_t Temporal::GetCurrentDateTime()
{
	time_t currentTime = rtc->get();
	if (currentTime == 0) {
		Serial.println("Error reading from RTC. Possibly set to 0.");
	}
	return currentTime;
}

bool Temporal::SetCurrentTime(time_t currentTime)
{
	rtc->set(currentTime);
	return (rtc->get() == currentTime);
}

TimeSpanDuration Temporal::GetTimeUntilGameStart()
{
	if (systemConfig.getGameStartDateTime() > GetCurrentDateTime()) {
		return ConvertToTimeSpanDuration(systemConfig.getGameStartDateTime() - GetCurrentDateTime());
	}
	TimeSpanDuration empty;
	return empty;
}

TimeSpanDuration Temporal::GetTimeUntilNextPoint() {
	// TODO Implement.
}

//DateTime Temporal::GetRemainingTimeToUnlock()
//{
//	if (unlockDateTime <= rtc->get())
//	{
//		DateTime zero;
//		return zero;
//	}
//	uint32_t remainingInTimeT = unlockDateTime - rtc->get();
//	return ConvertToDateTime(remainingInTimeT);
//}

//DateTime Temporal::GetRemainingTimeToPreUnlock()
//{
//	if (preUnlockDateTime <= rtc->get())
//	{
//		DateTime zero;
//		return zero;
//	}
//	uint32_t remainingInTimeT = preUnlockDateTime - rtc->get();
//	return ConvertToDateTime(remainingInTimeT);
//}
//
//DateTime Temporal::GetRemainingWindow()
//{
//	if ((unlockDateTime + 1800) <= rtc->get())
//	{
//		DateTime zero;
//		return zero;
//	}
//	uint32_t window = (unlockDateTime + 1800) - rtc->get();
//	return ConvertToDateTime(window);
//}
//
//bool Temporal::UnlockReached()
//{
//	return(unlockDateTime <= rtc->get());
//}
//
//bool Temporal::PreUnlockReached()
//{
//	return(preUnlockDateTime <= rtc->get());
//}
//
//bool Temporal::WindowExpired()
//{
//	return((unlockDateTime + 1800) <= rtc->get());
//}
//
//uint32_t Temporal::ConvertToSeconds(DateTime _time)
//{
//	return((_time.Days * 86400) + (_time.Hours * 3600) + (_time.Minutes * 60));
//}
//
//
//// EEPROM related methods.
//void Temporal::StoreDateTimeToEEPROM()
//{
//	DateTime unlockInElements;
//	unlockInElements = ConvertToDateTime(unlockDateTime);
//
//	DateTime preUnlockInElements;
//	preUnlockInElements = ConvertToDateTime(preUnlockDateTime);
//
//	if (unlockInElements.Days > 255)
//	{
//		EEPROM.update(10, unlockInElements.Days / 255);
//		EEPROM.update(11, unlockInElements.Days % 255);
//		EEPROM.update(12, 1);
//	}
//	else
//	{
//		EEPROM.update(10, unlockInElements.Days);
//		EEPROM.update(12, 0);
//	}
//	EEPROM.update(20, unlockInElements.Hours);
//	EEPROM.update(30, unlockInElements.Minutes);
//
//	if (preUnlockInElements.Days > 255)
//	{
//		EEPROM.update(40, preUnlockInElements.Days / 255);
//		EEPROM.update(41, preUnlockInElements.Days % 255);
//		EEPROM.update(42, 1);
//	}
//	else
//	{
//		EEPROM.update(40, preUnlockInElements.Days);
//		EEPROM.update(42, 0);
//	}
//	EEPROM.update(50, preUnlockInElements.Hours);
//	EEPROM.update(60, preUnlockInElements.Minutes);
//}
//
//void Temporal::ReadDateTimeFromEEPROM()
//{
//	DateTime unlockInElements;
//	DateTime preUnlockInElements;
//
//	if (EEPROM.read(12) == 1)
//	{
//		unlockInElements.Days = (EEPROM.read(10) * 255) + EEPROM.read(11);
//	}
//	else
//	{
//		unlockInElements.Days = EEPROM.read(10);
//	}
//
//	unlockInElements.Hours = EEPROM.read(20);
//	unlockInElements.Minutes = EEPROM.read(30);
//
//	if (EEPROM.read(42) == 1)
//	{
//		preUnlockInElements.Days = (EEPROM.read(40) * 255) + EEPROM.read(41);
//	}
//	else
//	{
//		preUnlockInElements.Days = EEPROM.read(40);
//	}
//	preUnlockInElements.Hours = EEPROM.read(50);
//	preUnlockInElements.Minutes = EEPROM.read(60);
//
//	unlockDateTime = ConvertToSeconds(unlockInElements);
//	preUnlockDateTime = ConvertToSeconds(preUnlockInElements);
//}