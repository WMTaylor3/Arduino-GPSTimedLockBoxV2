/*
 Name:		Arduino_MomentMaker.ino
 Created:	6/8/2019 2:17:32 PM
 Author:	William Taylor
*/

#ifndef _PHYSICAL_h
#define _PHYSICAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

class Physical
{
private:
	SoftwareSerial* gpsSerial;
	TinyGPSPlus* gps;
	double latitude;
	double longitude;
public:
	Physical();
	void Initialize(double, double);
	void End();
	bool IsLocationValid();
	uint32_t GetAbsoluteDistance();
	bool IsWithinRadius();
	bool UpdateGPS();
};

#endif