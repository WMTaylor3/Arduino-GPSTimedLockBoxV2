/*
 Name:		Arduino_MomentMaker.ino
 Created:	6/8/2019 2:17:32 PM
 Author:	William Taylor
*/

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LiquidCrystal_I2C.h>
#include <string.h>

class Display
{
private:
	LiquidCrystal_I2C* lcd;
	String screenData[2];
	void Write(String, String = "");
public:
	Display();
	void Initialize();
	void LcdOn();
	void LcdOff();
	void WriteLocationRevealedIn(uint32_t, uint32_t, uint32_t);
	void WriteObtainingGPSLocationFix();
	void WriteDistanceRemaining(uint32_t);
	void WriteTimeToUnlock(uint32_t, uint32_t, uint32_t);
	void WriteLocationReached();
	void WriteUnlockTimeRemaining(uint32_t, uint32_t, uint32_t);
	void WriteEnterPasscode();
	void CharTyped(uint8_t);
	void WriteInsertBothKeys();
	void WriteAccessGranted();
	void WriteAccessDenied();
	void WriteTooLate();
	void WriteGoodbye();
	void Clear();
};

#endif

