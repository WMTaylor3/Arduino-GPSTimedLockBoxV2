#include "Temporal.h"
#include <Time.h>
#include <math.h>

DS1307RTC* Temporal::rtc = new DS1307RTC();

Temporal::Temporal()
{
}

TimeSpanDuration Temporal::ConvertToTimeSpanDuration(uint32_t duration)
{
	TimeSpanDuration windowOpenDateTime;
	windowOpenDateTime.Days = duration / 86400;
	windowOpenDateTime.Hours = (duration % 86400) / 3600;
	windowOpenDateTime.Minutes = ((duration % 86400) % 3600) / 60;
	windowOpenDateTime.Seconds = (((duration % 86400) % 3600) % 60) / 60;
	return windowOpenDateTime;
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
	if (systemConfig.GetCurrentPointWindowCloseTime() > rtc->get())
	{
		return ConvertToTimeSpanDuration(systemConfig.GetCurrentPointWindowCloseTime() - rtc->get());
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
	return(rtc->get() >= systemConfig.GetCurrentPointWindowOpenTime());
}

bool Temporal::HasWindowExpired()
{
	return(rtc->get() >= systemConfig.GetCurrentPointWindowCloseTime());
}