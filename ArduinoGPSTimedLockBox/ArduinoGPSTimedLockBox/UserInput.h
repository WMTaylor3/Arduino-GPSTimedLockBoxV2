// UserInput.h

#ifndef _USERINPUT_h
#define _USERINPUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define key 12
#define buttonOne 9
#define buttonTwo 10
#define buttonThree 11

class UserInput
{
public:
	startupMode getStartUpMode();
};

#endif
