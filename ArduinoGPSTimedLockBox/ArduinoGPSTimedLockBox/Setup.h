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
#include "CommonDataTypes.h"
#include "SinglePointConfiguration.h"

class Setup
{
private:
	static uint8_t numberOfPoints;
	static uint8_t currentPointIndex;
	static time_t timeAtBoot;
	static time_t gameStartDateTime;
	static SinglePointConfiguration* singlePointConfigurationCollection[];
	static bool timeExtended;

	static void CreateBasicConfig(uint8_t _numberOfPoints);
	static void AwaitUserInput();
	static void GetUserInput(char* rx_string, uint8_t maxStringLength);
	static bool ValidateUserInputDateTime(char* rx_string);
	static time_t ParseDateTimeInputToTimeT(char* dateTimeString);
	static uint16_t ParseMinutesStringToSeconds(char* durationString);
	static int32_t ParseLatLongStringToInt32(char* locationString, latOrLong latOrLong);

	static void ClearScreen();
	static void PrintSplashScreen();
	static uint8_t PromptForNumberOfPoints();
	static bool ValidateUserInputNumberOfPoints(char* rx_string);
	static bool ValidateNumberOfPoints(uint8_t numberOfPoints);
	static time_t PromptForGameStartDateTime();
	static bool ValidateGameStartDateTime(time_t startDateTime);
	static int32_t PromptForLatitude(bool final);
	static bool ValidateUserInputLatitude(char* rx_string);
	static bool ValidateLatitude(int32_t latitude);
	static int32_t PromptForLongitude(bool final);
	static bool ValidateUserInputLongitude(char* rx_string);
	static bool ValidateLongitude(int32_t longitude);
	static time_t PromptForNextPointDateTime(bool final);
	static bool ValidateNextPointDateTime(time_t nextPointDateTime);
	static uint16_t PromptForGracePeriodDuration();
	static bool ValidateUserInputGracePeriod(char* rx_string);
	static bool ValidateGracePeriodDuration(uint16_t durationInSeconds);

public:
	Setup();
	// ~Setup(); // Removed as is now empty due to class being static. Add back if we make class non-static.
	static void Initialize();
	static time_t GetGameStartDateTime();
	static latLongLocation GetCurrentPointLocation();
	static time_t GetCurrentPointActionTime();
	static time_t GetCurrentPointGracePeriodEndTime();
	static void ProgressToNextPoint();
	static bool IsFinalPoint();
	static void ExtendTime(uint32_t duration);
};

#endif

