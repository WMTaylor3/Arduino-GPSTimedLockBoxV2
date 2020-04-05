// 
// 
// 

#include "NeoPhysical.h"

NeoPhysical::NeoPhysical() : gpsPort(RX_PIN, TX_PIN)
{
    gpsPort.begin(9600);
}

void NeoPhysical::doSomeWork()
{
    // Print all the things!

    trace_all(Serial, gps, fix);

    Serial.print(F("Location: "));
    if (fix.valid.location) {
        Serial.print(fix.latitude(), 5);
        Serial.print(',');
        Serial.print(fix.longitude(), 5);
    }
    else {
        Serial.print(F("INVALID"));
    }
    Serial.print(F("  Speed: "));
    if (fix.valid.speed) {
        Serial.print(fix.speed_kph());
        Serial.print(F(" KMPH "));
    }
    else {
        Serial.print(F("INVALID"));
    }

    // Shift the date/time to local time
    NeoGPS::clock_t localSeconds;
    NeoGPS::time_t  localTime;
    if (fix.valid.date && fix.valid.time) {
        using namespace NeoGPS; // save a little typing below...

        localSeconds = (clock_t)fix.dateTime; // convert structure to a second count
        localSeconds += 12 * SECONDS_PER_HOUR + 00 * SECONDS_PER_MINUTE; // shift timezone
        localTime = localSeconds;              // convert back to a structure
    }

    Serial.print(F("  Date : "));
    if (fix.valid.date) {
        Serial.print(localTime.month);
        Serial.print('/');
        Serial.print(localTime.date);
        Serial.print('/');
        Serial.print(localTime.year);
    }
    else {
        Serial.print(F("INVALID"));
    }

    Serial.print(F("  Time : "));
    if (fix.valid.time) {
        Serial.print(localTime.hours);
        Serial.print(':');
        if (localTime.minutes < 10) Serial.print('0');
        Serial.print(localTime.minutes);
        Serial.print(':');
        if (localTime.seconds < 10) Serial.print(F("0"));
        Serial.print(localTime.seconds);
    }
    else {
        Serial.print(F("INVALID"));
    }
    Serial.println("");

} // doSomeWork

void NeoPhysical::run()
{
    while (gps.available(gpsPort)) {
        fix = gps.read();
        doSomeWork();
    }
}

void NeoPhysical::SerialEnd()
{
    gpsPort.end();
}

void NeoPhysical::UpdateGPS() // Test this bad boy.. He looks shifty and I don't like it.
{
    do {
        while (gps.available(gpsPort)) {
            fix = gps.read();
        }
    } while (!fix.valid.location || !fix.valid.date || !fix.valid.time);
}


bool Physical::UpdateGPS()
{
    uint8_t data;
    unsigned long endTime = millis() + 2000;
    while (millis() <= endTime)
    {
        if (gpsSerial->available() > 0)
        {
            data = gpsSerial->read();
            gps->encode(data);
        }
    }
    if (gps->location.age() <= 1000)
    {
        return true;
    }
    false;
}

bool Physical::IsLocationValid()
{
    if ((gps->location.lat() != 0) && (gps->location.lng() != 0))
    {
        return true;
    }
    return false;
}

uint32_t Physical::GetAbsoluteDistance()
{
    if (IsLocationValid())
    {
        return TinyGPSPlus::distanceBetween(latitude, longitude, gps->location.lat(), gps->location.lng());
    }

    return 100000;
}

bool Physical::IsWithinRadius()
{
    if (GetAbsoluteDistance() <= 30)
    {
        return true;
    }
    return false;
}