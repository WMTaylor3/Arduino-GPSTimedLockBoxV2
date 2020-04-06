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
	void doSomeWork();
	void run();
	void SerialEnd();
	time_t GetDateTimeInUtc();
	float GetAbsoluteDistanceFromPoint(NeoGPS::Location_t targetLocation);
	//void Initialize(double, double);
	//void End();
	//bool IsLocationValid();
	//uint32_t GetAbsoluteDistance();
	//bool IsWithinRadius();
	//bool UpdateGPS();
};

#endif

