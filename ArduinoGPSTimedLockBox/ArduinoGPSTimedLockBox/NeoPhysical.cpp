// 
// 
// 

#include "NeoPhysical.h"

NeoPhysical::NeoPhysical() : gpsPort(RX_PIN, TX_PIN)
{
    gpsPort.begin(9600);
}

void NeoPhysical::SerialEnd()
{
    gpsPort.end();
}

void NeoPhysical::UpdateGPS()
{
    int period = 3000;
    uint32_t time_now = 0;

    while (!fix.valid.location || !fix.valid.date || !fix.valid.time) {
        if (millis() - time_now > period) {
            time_now = millis();
            Serial.println(F("GPS INVALID:"));
            if (!fix.valid.location) {
                Serial.println(F("    Location"));
            }
            if (!fix.valid.date) {
                Serial.println(F("    Date"));
            }
            if (!fix.valid.time) {
                Serial.println(F("    Time"));
            }
        }
        while (gps.available(gpsPort)) {
            fix = gps.read();
        }
    }
}

time_t NeoPhysical::GetDateTimeInUtc()
{
    while (true) {
        UpdateGPS();
        if (fix.valid.date && fix.valid.time) {
            return fix.dateTime + SECS_YR_2000; // dateTime object seems to want to resturn the time since 2000. I prefer 1970 as my epoch.
        }
    }
}

float NeoPhysical::GetAbsoluteDistanceFromPoint(latLongLocation targetLocation)
{
    while (true) {
        UpdateGPS();
        if (fix.valid.location) {
            NeoGPS::Location_t target(targetLocation.latitude, targetLocation.longitude);
             return fix.location.DistanceKm(target) * 1000; // Convert from kilometers to meters.
        }
    }
}


bool NeoPhysical::IsWithinRadius(latLongLocation targetLocation)
{
    return (GetAbsoluteDistanceFromPoint(targetLocation) <= 30);
}