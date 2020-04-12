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
	static LiquidCrystal_I2C* lcd;
	static void Write(String, String = "");
public:
	Display();
	static void Initialize();
	static void LcdOn();
	static void LcdOff();
	static void WriteSearchBeginsIn(uint32_t, uint32_t, uint32_t);
	static void WriteNextStageBeginsIn(uint32_t, uint32_t, uint32_t);
	static void WriteObtainingGPSLocationFix();
	static void WriteDistanceRemaining(uint32_t);
	static void WriteTimeToUnlock(uint32_t, uint32_t, uint32_t);
	static void WriteLocationReached();
	static void WriteUnlockTimeRemaining(uint32_t, uint32_t, uint32_t);
	static void WriteSerialMode();
	static void WriteEnterValue();
	static void WriteCalibratingRTC();
	static void WriteRTCOffBy(uint32_t delta);
	static void WriteEnterPasscode();
	static void CharTyped(uint8_t);
	static void WriteInsertBothKeys();
	static void WriteTimeIncreasedBy(uint32_t days, uint32_t hours, uint32_t minutes);
	static void WriteAccessGranted();
	static void WriteAccessDenied();
	static void WriteTooLate();
	static void WriteGoodbye();
	static void Clear();
};

#endif

