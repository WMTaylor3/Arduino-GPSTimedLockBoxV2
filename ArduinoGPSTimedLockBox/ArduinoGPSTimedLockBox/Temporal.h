/*
 Name:		Arduino_MomentMaker.ino
 Created:	6/8/2019 2:17:32 PM
 Author:	William Taylor
*/

#ifndef _TEMPORAL_h
#define _TEMPORAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <DS1307RTC.h>
#include <Time.h>

struct DateTime
{
	uint16_t Years = 0;
	uint16_t Months = 0;
	uint16_t Days = 0;
	uint16_t Hours = 0;
	uint16_t Minutes = 0;
	uint16_t Seconds = 0;
};

class Temporal
{
private:
	static DS1307RTC *rtc;
	//static uint32_t unlockDateTime;
	//static uint32_t preUnlockDateTime;
	//static uint32_t Temporal::ConvertToSeconds(DateTime);
	//static DateTime Temporal::ConvertToDateTime(uint32_t);
	//static void StoreDateTimeToEEPROM();
	//static void ReadDateTimeFromEEPROM();
public:
	Temporal();
	static time_t GetCurrentDateTime();
	static bool SetCurrentTime(time_t newTime);
	//static void SetUnlockDateTime(DateTime, DateTime);
	//static DateTime GetRemainingTimeToUnlock();
	//static DateTime GetRemainingTimeToPreUnlock();
	//static DateTime GetRemainingWindow();
	//static bool UnlockReached();
	//static bool PreUnlockReached();
	//static bool WindowExpired();
};

#endif

