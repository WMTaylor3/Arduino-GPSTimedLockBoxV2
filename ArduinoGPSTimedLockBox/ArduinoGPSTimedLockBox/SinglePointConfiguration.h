#ifndef _SINGLEPOINTCONFIGURATION_h
#define _SINGLEPOINTCONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "CommonDataTypes.h"
#include <Time.h>

class SinglePointConfiguration
{
private:
	latLongLocation location;
	time_t dateTime;
	time_t gracePeriodEndDateTime;
public:
	SinglePointConfiguration();

	void SetLocation(int32_t _lat, int32_t _lon);
	void SetDateTime(time_t _time);
	void SetGracePeriodEndDateTime(time_t _time);

	latLongLocation GetLocation();
	time_t GetDateTime();
	time_t GetGracePeriodEndDateTime();
};

#endif

