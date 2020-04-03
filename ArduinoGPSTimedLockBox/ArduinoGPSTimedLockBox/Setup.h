// Configuration.h

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Time.h>

class SinglePointConfiguration
{
private:
	uint8_t holder;
public:
	SinglePointConfiguration();
	void SetUnlockLocation(double lat, double long);
	void SetHintRevealDateTime(time_t time);
	void SetUnlockDateTime(time_t time);
	void SetGracePeriodEndTime(time_t time);
};

class SystemConfiguration
{
private:
	uint8_t numberOfPoints;
	uint8_t currentPointIndex;
	SinglePointConfiguration* SinglePointConfigurationCollection[];
public:
	SystemConfiguration(uint8_t _numberOfPoints);
	~SystemConfiguration();
	SinglePointConfiguration* getPoint(uint8_t index);
};

class Setup
{
private:
	SystemConfiguration* sysConfig;
	void AwaitUserInput();
	void GetUserInput(char* rx_string, uint8_t maxStringLength);
	void ClearScreen();
	void PrintSplashScreen();
	uint8_t PromptForNumberOfPoints();
	bool ValidateNumberOfPoints(uint8_t numberOfPoints);
	double PromptForUnlockLatitude();
	bool ValidateUserInputLatitude(char* rx_string);
	bool ValidateUnlockLatitude(double unlockLatitude);
	double PromptForUnlockLongitude();
	bool ValidateUserInputLongitude(char* rx_string);
	bool ValidateUnlockLongitude(double unlockLatitude);
	time_t PromptForHintRevealDateTime();
	bool ValidateHintRevealDateTime(time_t unlockLatitude);
	time_t PromptForUnlockDateTime();
	bool ValidateUnlockDateTime(time_t unlockLatitude);
	time_t PromptForGracePeriodEndTime();
	bool ValidateGracePeriodEndTime(time_t unlockLatitude);
public:
	Setup();
	~Setup();
	SystemConfiguration* InitialConfiguration();
};

#endif

