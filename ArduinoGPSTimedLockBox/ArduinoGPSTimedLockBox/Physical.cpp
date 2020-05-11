#include "Physical.h"

NeoSWSerial Physical::gpsPort(RX_PIN, TX_PIN);
NMEAGPS Physical::gps;
gps_fix Physical::fix;

Physical::Physical()
{
    SerialBegin();
}

void Physical::SerialBegin()
{
    gpsPort.begin(9600);
}

void Physical::SerialEnd()
{
    gpsPort.end();
}

void Physical::UpdateGPS()
{
    while (!fix.valid.location || !fix.valid.date || !fix.valid.time)
    {
        while (gps.available(gpsPort))
        {
            fix = gps.read();
        }
    }
}

time_t Physical::GetDateTimeInUtc()
{
    while (true)
    {
        UpdateGPS();
        if (fix.valid.date && fix.valid.time)
        {
            return fix.dateTime + SECS_YR_2000; // dateTime object seems to want to resturn the time since 2000. I prefer 1970 as my epoch.
        }
    }
}

float Physical::GetAbsoluteDistanceFromPoint(latLongLocation targetLocation)
{
    while (true)
    {
        UpdateGPS();
        if (fix.valid.location)
        {
            NeoGPS::Location_t target(targetLocation.latitude, targetLocation.longitude);
            return fix.location.DistanceKm(target) * 1000; // Convert from kilometers to meters.
        }
        delay(100);
    }
}


bool Physical::IsWithinRadius(latLongLocation targetLocation)
{
    return (GetAbsoluteDistanceFromPoint(targetLocation) <= 10);
}