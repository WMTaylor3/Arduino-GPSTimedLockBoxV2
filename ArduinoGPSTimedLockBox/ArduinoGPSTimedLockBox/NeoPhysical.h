// NeoPhysical.h

#ifndef _NEOPHYSICAL_h
#define _NEOPHYSICAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <NeoSWSerial.h>
#include <NMEAGPS.h>
#include <Streamers.h>
#include <Time.h>
#include "CommonDataTypes.h"

#define RX_PIN 6
#define TX_PIN 7

class NeoPhysical
{
private:
	NeoSWSerial gpsPort;
	NMEAGPS gps;
	gps_fix fix;
	void UpdateGPS();
public:
	NeoPhysical();
	void SerialEnd();
	time_t GetDateTimeInUtc();
	float GetAbsoluteDistanceFromPoint(latLongLocation targetLocation);
	bool IsWithinRadius(latLongLocation targetLocation);
};

#endif

