// NeoPhysical.h

#ifndef _PHYSICAL_h
#define _PHYSICAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <NeoSWSerial.h>
#include <NMEAGPS.h>
#include <Time.h>
#include "CommonDataTypes.h"

#define RX_PIN 6
#define TX_PIN 7

class Physical
{
private:
	static NeoSWSerial gpsPort;
	static NMEAGPS gps;
	static gps_fix fix;
	static void UpdateGPS();
public:
	Physical();
	static void SerialEnd();
	static time_t GetDateTimeInUtc();
	static float GetAbsoluteDistanceFromPoint(latLongLocation targetLocation);
	static bool IsWithinRadius(latLongLocation targetLocation);
};

#endif

