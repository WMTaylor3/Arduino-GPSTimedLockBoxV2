#include "SinglePointConfiguration.h"

SinglePointConfiguration::SinglePointConfiguration()
{
    location.latitude = 0;
    location.longitude = 0;
    dateTime = 0;
    gracePeriodEndDateTime = 0;
}

void SinglePointConfiguration::SetLocation(int32_t _lat, int32_t _lon)
{
    location.latitude = _lat;
    location.longitude = _lon;
}

void SinglePointConfiguration::SetDateTime(time_t _time)
{
    dateTime = _time;
}

void SinglePointConfiguration::SetGracePeriodEndDateTime(time_t _time)
{
    gracePeriodEndDateTime = _time;
}

latLongLocation SinglePointConfiguration::GetLocation()
{
    return location;
}

time_t SinglePointConfiguration::GetDateTime()
{
    return dateTime;
}

time_t SinglePointConfiguration::GetGracePeriodEndDateTime()
{
    return gracePeriodEndDateTime;
}