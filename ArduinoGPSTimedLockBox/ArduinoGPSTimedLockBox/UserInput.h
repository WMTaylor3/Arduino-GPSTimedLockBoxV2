#ifndef _USERINPUT_h
#define _USERINPUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "CommonDataTypes.h"
#include "Display.h"

#define key 12
#define buttonOne 9
#define buttonTwo 10
#define buttonThree 11

#define codeOverride "1323122133"
#define codeExtraTime "1233213"
#define codeCalibrate "1121321"
#define codeConfigure "1221213"

class UserInput
{
private:
	static Display display;
	static buttonState GetCurrentButtons();
public:
	static startupMode GetStartUpMode();
	static bool ValidateCodeForStartupMode(startupMode modeToAuthenticate);
	static uint32_t GetExtraTimeValue();
	static void AwaitKeyLock();
	static bool IsKeyStateUnlocked();
};

#endif

