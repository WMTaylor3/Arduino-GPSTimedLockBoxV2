// Configuration.h

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SinglePointConfiguration
{
private:
	uint8_t holder;
public:
	SinglePointConfiguration();
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
	uint8_t GetNumberOfPoints();
	bool ValidateNumberOfPoints(uint8_t numberOfPoints);
	double GetUnlockLatitude();
	bool ValidateUnlockLatitude(double unlockLatitude);

public:
	Setup();
	~Setup();
	SystemConfiguration* InitialConfiguration();
};

#endif

