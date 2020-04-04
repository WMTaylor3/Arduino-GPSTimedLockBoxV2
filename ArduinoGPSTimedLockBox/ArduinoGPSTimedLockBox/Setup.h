// Configuration.h

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Time.h>
#include <DS1307RTC.h>

class SinglePointConfiguration
{
private:
	uint8_t holder;
public:
	SinglePointConfiguration();
	void SetLocation(double lat, double long);
	void SetDateTime(time_t time);
	void SetGracePeriodEndTime(time_t time);
};

class Setup
{
private:
	uint8_t numberOfPoints;
	uint8_t currentPointIndex;
	time_t timeAtBoot;
	time_t gameStartDateTime;
	SinglePointConfiguration* singlePointConfigurationCollection[];

	void StubBasicConfig(uint8_t _numberOfPoints);
	void AwaitUserInput();
	void GetUserInput(char* rx_string, uint8_t maxStringLength);
	bool ValidateUserInputDateTime(char* rx_string);
	time_t ParseDateTimeInputToTimeT(char* dateTimeString);
	uint16_t ParseMinutesStringToSeconds(char* durationString);
	void ClearScreen();
	void PrintSplashScreen();
	uint8_t PromptForNumberOfPoints();
	bool ValidateUserInputNumberOfPoints(char* rx_string);
	bool ValidateNumberOfPoints(uint8_t numberOfPoints);
	time_t PromptForGameStartDateTime();
	bool ValidateGameStartDateTime(time_t startDateTime);
	double PromptForLatitude(bool final);
	bool ValidateUserInputLatitude(char* rx_string);
	bool ValidateLatitude(double latitude);
	double PromptForLongitude(bool final);
	bool ValidateUserInputLongitude(char* rx_string);
	bool ValidateLongitude(double longitude);
	time_t PromptForNextPointDateTime(bool final);
	bool ValidateNextPointDateTime(time_t nextPointDateTime);
	uint16_t PromptForGracePeriodDuration();
	bool ValidateUserInputGracePeriod(char* rx_string);
	bool ValidateGracePeriodDuration(uint16_t durationInSeconds);
public:
	Setup();
	~Setup();
	void Initialize();
};

#endif

