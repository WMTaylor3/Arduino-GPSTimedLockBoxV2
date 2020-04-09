#ifndef _COMMONSTRUCTURES_h
#define _COMMONSTRUCTURES_h

enum latOrLong { latitude, longitude };

struct latLongLocation
{
	int32_t latitude;
	int32_t longitude;
};

#endif