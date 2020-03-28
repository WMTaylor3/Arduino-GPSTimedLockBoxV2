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
#include <TimeLib.h>

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
	DS1307RTC *rtc;
	uint32_t unlockDateTime;
	uint32_t preUnlockDateTime;
	uint32_t Temporal::ConvertToSeconds(DateTime);
	DateTime Temporal::ConvertToDateTime(uint32_t);
	void StoreDateTimeToEEPROM();
	void ReadDateTimeFromEEPROM();
public:
	Temporal();
	void ResetCurrentTime();
	void SetUnlockDateTime(DateTime, DateTime);
	void Initialize();
	DateTime GetRemainingTimeToUnlock();
	DateTime GetRemainingTimeToPreUnlock();
	DateTime GetRemainingWindow();
	bool UnlockReached();
	bool PreUnlockReached();
	bool WindowExpired();
};

#endif

