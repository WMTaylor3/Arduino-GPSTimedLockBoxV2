#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Time.h>
#include <DS1307RTC.h>
#include <EEPROM.h>
#include "CommonDataTypes.h"
#include "SinglePointConfiguration.h"

class Setup
{
private:
	static uint8_t numberOfPoints;
	static uint8_t currentPointIndex;
	static time_t gameStartDateTime;
	static SinglePointConfiguration* singlePointConfigurationCollection[];
	static bool timeExtended;

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
	static uint16_t PromptForWindowDuration();
	static bool ValidateUserInputWindowDuration(char* rx_string);
	static bool ValidateWindowDuration(uint16_t durationInSeconds);

	static void StoreUnsignedInt32AsBytesInEEPROM(uint32_t data, uint8_t startIndex);
	static void StoreSignedInt32AsBytesInEEPROM(int32_t data, uint8_t startIndex);
	static uint32_t ReadUnsignedInt32AsBytesFromEEPROM(uint8_t startIndex);
	static int32_t ReadSignedInt32AsBytesFromEEPROM(uint8_t startIndex);
	static void ZeroConfigAndEEPROM();

public:
	Setup();
	// ~Setup(); // Removed as is now empty due to class being static. Add back if we make class non-static.

	static void printErrorInvalidInputLength();
	static void printErrorRequiredCharacterOmmitted();
	static void printErrorInvalidCharacterFoundInField();
	static void printErrorValueIsLogicallyInvalid();
	static void printInfoTimeInputFormatting();
	static void printInfoLocationInputFormatting(bool isLongitude);

	static void Initialize();
	static time_t GetGameStartDateTime();
	static latLongLocation GetCurrentPointLocation();
	static time_t GetCurrentPointWindowOpenTime();
	static time_t GetCurrentPointWindowCloseTime();
	static uint8_t GetCurrentPointNumber();
	static uint8_t GetTotalPointCount();
	
	static void ProgressToNextPoint();
	static bool IsFinalPoint();
	static void ExtendTime(uint32_t duration, bool isInWindow);

	static void LoadConfigFromEEPROM();
	static void SaveConfigToEEPROM();
};

#endif

