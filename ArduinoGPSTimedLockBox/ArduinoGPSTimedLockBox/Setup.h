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

enum latlong { latitude, longitude };

class SinglePointConfiguration
{
private:
	NeoGPS::Location_t location;
	time_t dateTime;
	time_t gracePeriodEndTime;
public:
	SinglePointConfiguration();

	void SetLocation(int32_t _lat, int32_t _lon);
	void SetDateTime(time_t _time);
	void SetGracePeriodEndTime(time_t _time);

	NeoGPS::Location_t& getLocation();
	time_t getDateTime();
	time_t getGracePeriodEndDateTime();
};

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
	int32_t ParseLatLongStringToInt32(char* locationString, latlong latOrLong);

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
	NeoGPS::Location_t& getCurrentPointLocation();
	time_t getCurrentPointTime();
	time_t getCurrentPointGracePeriodEndTime();
	void progressToNextPoint();
};

#endif

