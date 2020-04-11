// Configuration.h

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <DS1307RTC.h>
#include "CommonDataTypes.h"
#include "SinglePointConfiguration.h"
#include <Time.h>

class Setup
{
private:
	uint8_t numberOfPoints;
	uint8_t currentPointIndex;
	time_t timeAtBoot;
	time_t gameStartDateTime;
	SinglePointConfiguration* singlePointConfigurationCollection[];

	void CreateBasicConfig(uint8_t _numberOfPoints);
	void AwaitUserInput();
	void GetUserInput(char* rx_string, uint8_t maxStringLength);
	bool ValidateUserInputDateTime(char* rx_string);
	time_t ParseDateTimeInputToTimeT(char* dateTimeString);
	uint16_t ParseMinutesStringToSeconds(char* durationString);
	int32_t ParseLatLongStringToInt32(char* locationString, latOrLong latOrLong);

	void ClearScreen();
	void PrintSplashScreen();
	uint8_t PromptForNumberOfPoints();
	bool ValidateUserInputNumberOfPoints(char* rx_string);
	bool ValidateNumberOfPoints(uint8_t numberOfPoints);
	time_t PromptForGameStartDateTime();
	bool ValidateGameStartDateTime(time_t startDateTime);
	int32_t PromptForLatitude(bool final);
	bool ValidateUserInputLatitude(char* rx_string);
	bool ValidateLatitude(int32_t latitude);
	int32_t PromptForLongitude(bool final);
	bool ValidateUserInputLongitude(char* rx_string);
	bool ValidateLongitude(int32_t longitude);
	time_t PromptForNextPointDateTime(bool final);
	bool ValidateNextPointDateTime(time_t nextPointDateTime);
	uint16_t PromptForGracePeriodDuration();
	bool ValidateUserInputGracePeriod(char* rx_string);
	bool ValidateGracePeriodDuration(uint16_t durationInSeconds);

public:
	Setup();
	~Setup();
	void Initialize();
	latLongLocation getCurrentPointLocation();
	time_t getCurrentPointTime();
	time_t getCurrentPointGracePeriodEndTime();
	void progressToNextPoint();
};

#endif

