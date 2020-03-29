// SerialCommunication.h

#ifndef _SERIALCOMMUNICATION_h
#define _SERIALCOMMUNICATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class UserInput
{
private:
	void AwaitUserInput();
	void GetUserInput(char* rx_string, uint8_t maxStringLength);
	void ClearScreen();
	void PrintSplashScreen();
	uint8_t ConfigureNumberOf4DPoints();
public:
	UserInput();
	void InitialConfiguration();
};

#endif

