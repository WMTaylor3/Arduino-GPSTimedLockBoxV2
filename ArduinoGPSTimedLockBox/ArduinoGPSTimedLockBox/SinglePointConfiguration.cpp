// 
// 
// 

#include "SinglePointConfiguration.h"

SinglePointConfiguration::SinglePointConfiguration()
{
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

void SinglePointConfiguration::SetGracePeriodEndTime(time_t _time)
{
    dateTime = _time;
}

latLongLocation SinglePointConfiguration::getLocation()
{
    return location;
}

time_t SinglePointConfiguration::getDateTime()
{
    return dateTime;
}

time_t SinglePointConfiguration::getGracePeriodEndDateTime()
{
    return gracePeriodEndTime;
}