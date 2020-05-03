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

bool Temporal::SetCurrentTime(time_t currentTime)
{
	rtc->set(currentTime);
	return (rtc->get() == currentTime);
}

TimeSpanDuration Temporal::GetTimeUntilGameStart()
{
	if (systemConfig.GetGameStartDateTime() > rtc->get())
	{
		return ConvertToTimeSpanDuration(systemConfig.GetGameStartDateTime() - rtc->get());
	}
	TimeSpanDuration empty;
	return empty;
}

TimeSpanDuration Temporal::GetTimeUntilWindowOpens()
{
	if (systemConfig.GetCurrentPointWindowOpenTime() > rtc->get())
	{
		return ConvertToTimeSpanDuration(systemConfig.GetCurrentPointWindowOpenTime() - rtc->get());
	}
	TimeSpanDuration empty;
	return empty;
}

TimeSpanDuration Temporal::GetTimeUntilWindowClose()
{
	if (systemConfig.GetCurrentPointGracePeriodEndTime() > rtc->get())
	{
		return ConvertToTimeSpanDuration(systemConfig.GetCurrentPointGracePeriodEndTime() - rtc->get());
	}
	TimeSpanDuration empty;
	return empty;
}

bool Temporal::IsGameStartReached()
{
	return(rtc->get() >= systemConfig.GetGameStartDateTime());
}

bool Temporal::HasWindowOpened()
{
	return(systemConfig.GetCurrentPointWindowOpenTime() >= rtc->get());
}

bool Temporal::HasWindowExpired()
{
	return(systemConfig.GetCurrentPointGracePeriodEndTime() >= rtc->get());
}