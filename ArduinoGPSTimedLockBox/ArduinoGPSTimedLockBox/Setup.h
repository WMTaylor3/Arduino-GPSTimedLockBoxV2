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
	void SetUnlockDateTime(time_t time);
	void SetGracePeriodEndTime(time_t time);
};

class SystemConfiguration
{
private:
	uint8_t numberOfPoints;
	uint8_t currentPointIndex;
	time_t gameStartDateTime;
	SinglePointConfiguration* SinglePointConfigurationCollection[];
public:
	SystemConfiguration(uint8_t _numberOfPoints);
	~SystemConfiguration();
	SinglePointConfiguration* getPoint(uint8_t index);
	void SetGameStartDateTime(time_t dateTime);
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
	bool ValidateUserInputNumberOfPoints(char* rx_string);
	bool ValidateNumberOfPoints(uint8_t numberOfPoints);
	time_t PromptForGameStartDateTime();
	bool ValidateUserInputGameStartTime(char* rx_string);
	bool ValidateGameStartDateTime(time_t unlockLatitude);
	double PromptForUnlockLatitude(bool final);
	bool ValidateUserInputLatitude(char* rx_string);
	bool ValidateUnlockLatitude(double unlockLatitude);
	double PromptForUnlockLongitude(bool final);
	bool ValidateUserInputLongitude(char* rx_string);
	bool ValidateUnlockLongitude(double unlockLatitude);
	time_t PromptForNextPointDateTime(bool final);
	bool ValidateUnlockDateTime(time_t unlockLatitude);
	time_t PromptForGracePeriodEndTime(bool final);
	bool ValidateGracePeriodEndTime(time_t unlockLatitude);
public:
	Setup();
	~Setup();
	SystemConfiguration* InitialConfiguration();
};

#endif

