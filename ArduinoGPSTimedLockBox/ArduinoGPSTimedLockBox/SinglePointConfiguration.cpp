#include "SinglePointConfiguration.h"

SinglePointConfiguration::SinglePointConfiguration()
{
    location.latitude = 0;
    location.longitude = 0;
    windowOpenDateTime = 0;
    windowCloseDateTime = 0;
}

void SinglePointConfiguration::SetLocation(int32_t _lat, int32_t _lon)
{
    location.latitude = _lat;
    location.longitude = _lon;
}

void SinglePointConfiguration::SetWindowOpenDateTime(time_t _time)
{
    windowOpenDateTime = _time;
}

void SinglePointConfiguration::SetWindowCloseDateTime(time_t _time)
{
    windowCloseDateTime = _time;
}

latLongLocation SinglePointConfiguration::GetLocation()
{
    return location;
}

time_t SinglePointConfiguration::GetWindowOpenDateTime()
{
    return windowOpenDateTime;
}

time_t SinglePointConfiguration::GetWindowCloseDateTime()
{
    return windowCloseDateTime;
}