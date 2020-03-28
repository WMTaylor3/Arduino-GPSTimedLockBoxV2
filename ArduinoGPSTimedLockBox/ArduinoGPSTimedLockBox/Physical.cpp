/*
 Name:		Arduino_MomentMaker.ino
 Created:	6/8/2019 2:17:32 PM
 Author:	William Taylor
*/

#include "Physical.h"

Physical::Physical()
{
	gpsSerial = new SoftwareSerial(6, 7);
	gps = new TinyGPSPlus();
}

void Physical::Initialize(double _lat, double _lng)
{
	gpsSerial->begin(9600);
	latitude = _lat;
	longitude = _lng;
}

void Physical::End()
{
	gpsSerial->end();
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