// 
// 
// 

#include "Physical.h"

NeoSWSerial Physical::gpsPort(RX_PIN, TX_PIN);
NMEAGPS Physical::gps;
gps_fix Physical::fix;

Physical::Physical()
{
    gpsPort.begin(9600);
}

void Physical::SerialEnd()
{
    gpsPort.end();
}

void Physical::UpdateGPS()
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

time_t Physical::GetDateTimeInUtc()
{
    while (true) {
        UpdateGPS();
        if (fix.valid.date && fix.valid.time) {
            Serial.println(F("GPS VALID"));
            return fix.dateTime + SECS_YR_2000; // dateTime object seems to want to resturn the time since 2000. I prefer 1970 as my epoch.
        }
    }
}

float Physical::GetAbsoluteDistanceFromPoint(latLongLocation targetLocation)
{
    while (true) {
        UpdateGPS();
        if (fix.valid.location) {
            Serial.println(F("GPS VALID"));
            NeoGPS::Location_t target(targetLocation.latitude, targetLocation.longitude);
             return fix.location.DistanceKm(target) * 1000; // Convert from kilometers to meters.
        }
    }
}


bool Physical::IsWithinRadius(latLongLocation targetLocation)
{
    return (GetAbsoluteDistanceFromPoint(targetLocation) <= 30);
}