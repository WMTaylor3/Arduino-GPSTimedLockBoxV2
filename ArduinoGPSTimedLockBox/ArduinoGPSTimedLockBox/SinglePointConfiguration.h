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
	time_t windowOpenDateTime;
	time_t windowCloseDateTime;
public:
	SinglePointConfiguration();

	void SetLocation(int32_t _lat, int32_t _lon);
	void SetWindowOpenDateTime(time_t _time);
	void SetWindowCloseDateTime(time_t _time);

	latLongLocation GetLocation();
	time_t GetWindowOpenDateTime();
	time_t GetWindowCloseDateTime();
};

#endif

