// 
// 
// 

#include "NeoPhysical.h"

NeoPhysical::NeoPhysical() : gpsPort(RX_PIN, TX_PIN)
{
    gpsPort.begin(9600);
}
//
//void NeoPhysical::doSomeWork()
//{
//    // Print all the things!
//
//    trace_all(Serial, gps, fix);
//
//    Serial.print(F("Location: "));
//    if (fix.valid.location) {
//        Serial.print(fix.latitude(), 5);
//        Serial.print(',');
//        Serial.print(fix.longitude(), 5);
//    }
//    else {
//        Serial.print(F("INVALID"));
//    }
//    Serial.print(F("  Speed: "));
//    if (fix.valid.speed) {
//        Serial.print(fix.speed_kph());
//        Serial.print(F(" KMPH "));
//    }
//    else {
//        Serial.print(F("INVALID"));
//    }
//
//    // Shift the date/time to local time
//    NeoGPS::clock_t localSeconds;
//    NeoGPS::time_t  localTime;
//    if (fix.valid.date && fix.valid.time) {
//        using namespace NeoGPS; // save a little typing below...
//
//        localSeconds = (clock_t)fix.dateTime; // convert structure to a second count
//        localSeconds += 12 * SECONDS_PER_HOUR + 00 * SECONDS_PER_MINUTE; // shift timezone
//        localTime = localSeconds;              // convert back to a structure
//    }
//
//    Serial.print(F("  Date : "));
//    if (fix.valid.date) {
//        Serial.print(localTime.month);
//        Serial.print('/');
//        Serial.print(localTime.date);
//        Serial.print('/');
//        Serial.print(localTime.year);
//    }
//    else {
//        Serial.print(F("INVALID"));
//    }
//
//    Serial.print(F("  Time : "));
//    if (fix.valid.time) {
//        Serial.print(localTime.hours);
//        Serial.print(':');
//        if (localTime.minutes < 10) Serial.print('0');
//        Serial.print(localTime.minutes);
//        Serial.print(':');
//        if (localTime.seconds < 10) Serial.print(F("0"));
//        Serial.print(localTime.seconds);
//    }
//    else {
//        Serial.print(F("INVALID"));
//    }
//    Serial.println("");
//
//} // doSomeWork
//
//void NeoPhysical::run()
//{
//    while (gps.available(gpsPort)) {
//        fix = gps.read();
//        doSomeWork();
//    }
//}

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