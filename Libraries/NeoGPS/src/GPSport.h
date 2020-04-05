#ifndef GPSport_h
#define GPSport_h

#include <NeoSWSerial.h>
NeoSWSerial gpsPort(3, 2);
#define GPS_PORT_NAME "NeoSWSerial(3,2)"
#define DEBUG_PORT Serial

#endif
