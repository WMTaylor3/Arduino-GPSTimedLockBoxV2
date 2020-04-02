// 
// 
// 

#include "Setup.h"

/////////////////////////////////////// User Input ///////////////////////////////////////

Setup::Setup()
{
}

Setup::~Setup() {
    delete sysConfig;
}

void Setup::AwaitUserInput() {
    while (!Serial.available()) {}
    while (Serial.available()) { Serial.read(); } // Clear buffer
}

// Prompts user for input on serial terminal.
// Param rx_string: char* to char[] in which to store the string, must be 1 more than max expected string length.
// Param maxStringLength: uint8_t containing maximum expected string length not including null termination.
void Setup::GetUserInput(char* rx_string, uint8_t maxStringLength) {
    while (Serial.available()) { Serial.read(); } // Clear buffer
    uint8_t i = 0;
    char rx_char = 0;
    uint8_t maxLengthIncludingTermination = maxStringLength + 1;

    while (true) {
        if (Serial.available()) {
            rx_char = Serial.read();
            Serial.write(rx_char);
            // If they have submitted their string, append NUL and return.
            if (i < maxLengthIncludingTermination && rx_char == '\r') {
                rx_string[i] = '\0';
                Serial.println();
                break;
            }
            // Continue reading input till one less than the array size, leaving room for the NUL.
            else if (i < maxStringLength && rx_char != '\r') {
                rx_string[i] = rx_char;
                i++;
            }
            else
            {
                Serial.println();
                Serial.print(F("Entry too long. Maximum input length is "));
                Serial.print(maxStringLength);
                Serial.print(F(" characters: "));
                i = 0; // Reset to allow new input.
                rx_char = 0;
            }
        }
    }
}

void Setup::ClearScreen() {
    Serial.write(27);       // ESC command
    Serial.print("[2J");    // clear screen command
    Serial.write(27);
    Serial.print("[H");     // cursor to home command
}

void Setup::PrintSplashScreen() {
    Serial.println(F("+-------------------------+"));
    Serial.println(F("|                         |"));
    Serial.println(F("|    Timed GPS Lockbox    |"));
    Serial.println(F("|      Initial Setup      |"));
    Serial.println(F("|                         |"));
    Serial.println(F("+-------------------------+"));
    Serial.println(F("To continue, press any key..."));
}

uint8_t Setup::PromptForNumberOfPoints()
{
    char charInput = '0';
    char* rx_string = NULL;
    Serial.print(F("How many 4D points do you wish to configure? (Between 1 and 5): "));
    rx_string = new char[2];
    GetUserInput(rx_string, 1);
    charInput = rx_string[0];
    delete(rx_string);
    rx_string = NULL;
    return charInput - 48; // Convert to integer.
}

bool Setup::ValidateNumberOfPoints(uint8_t numberOfPoints)
{
    return (numberOfPoints > 0 && numberOfPoints < 6);
}

double Setup::PromptForUnlockLatitude()
{
    return 0.0;
}

bool Setup::ValidateUnlockLatitude(double unlockLatitude)
{
    return false;
}

double Setup::PromptForUnlockLongitude()
{
    return 0.0;
}

bool Setup::ValidateUnlockLongitude(double unlockLatitude)
{
    return false;
}

time_t Setup::PromptForHintRevealDateTime()
{
    return time_t();
}

bool Setup::ValidateHintRevealDateTime(time_t unlockLatitude)
{
    return false;
}

time_t Setup::PromptForUnlockDateTime()
{
    return time_t();
}

bool Setup::ValidateUnlockDateTime(time_t unlockLatitude)
{
    return false;
}

time_t Setup::PromptForGracePeriodEndTime()
{
    return time_t();
}

bool Setup::ValidateGracePeriodEndTime(time_t unlockLatitude)
{
    return false;
}

SystemConfiguration* Setup::InitialConfiguration()
{
    ClearScreen();
    PrintSplashScreen();
    AwaitUserInput();
    ClearScreen();
    
    // Total number of times/places to be included in the hunt.
    uint8_t numberOfPoints = 0; // Invalid.
    while (!ValidateNumberOfPoints(numberOfPoints)) {
        numberOfPoints = PromptForNumberOfPoints();
    }
    sysConfig = new SystemConfiguration(numberOfPoints);
    ClearScreen();

    // For each time/place as quantified above.
    for (uint8_t i = 0; i < numberOfPoints; i++) {
        double unlockLatitude = 100; // Invalid.
        while (!ValidateUnlockLatitude(unlockLatitude)) {
            unlockLatitude = PromptForUnlockLatitude();
        }

        double unlockLongitude = 200; // Invalid.
        while (!ValidateUnlockLongitude(unlockLongitude)) {
            unlockLongitude = PromptForUnlockLongitude();
        }
       
        time_t hintRevealDateTime = 0; // Invalid. 1 January 1970.
        while (!ValidateHintRevealDateTime(hintRevealDateTime)) {
            hintRevealDateTime = PromptForHintRevealDateTime();
        }

        time_t unlockDateTime = 0; // Invalid. 1 January 1970.
        while (!ValidateUnlockDateTime(unlockDateTime)) {
            unlockDateTime = PromptForUnlockDateTime();
        }

        time_t gracePeriodEndTime = 0; // Invalid. 1 January 1970.
        while (!ValidateGracePeriodEndTime(gracePeriodEndTime)) {
            gracePeriodEndTime = PromptForGracePeriodEndTime();
        }

        sysConfig->getPoint(i)->SetUnlockLocation(unlockLatitude, unlockLongitude);
        sysConfig->getPoint(i)->SetHintRevealDateTime(hintRevealDateTime);
        sysConfig->getPoint(i)->SetUnlockDateTime(unlockDateTime);
        sysConfig->getPoint(i)->SetGracePeriodEndTime(gracePeriodEndTime);
    }
}

/////////////////////////////////////// System Configuration ///////////////////////////////////////

SystemConfiguration::SystemConfiguration(uint8_t _numberOfPoints)
{
    if (_numberOfPoints < 6 && _numberOfPoints > 0) {
        numberOfPoints = _numberOfPoints;
    }
    else {
        numberOfPoints = 0;
    }
    currentPointIndex = 0;
    for (uint8_t i = 0; i < numberOfPoints; i++) {
        SinglePointConfigurationCollection[i] = new SinglePointConfiguration();
    }
}

SystemConfiguration::~SystemConfiguration() {
    delete[] SinglePointConfigurationCollection;
}

SinglePointConfiguration* SystemConfiguration::getPoint(uint8_t index)
{
    if (index > 0 && index < numberOfPoints) {
        return SinglePointConfigurationCollection[index];
    }
    return nullptr;
}

/////////////////////////////////////// Single Point Configuration ///////////////////////////////////////

SinglePointConfiguration::SinglePointConfiguration()
{
}

void SinglePointConfiguration::SetUnlockLocation(double lat, double long)
{
}

void SinglePointConfiguration::SetHintRevealDateTime(time_t time)
{
}

void SinglePointConfiguration::SetUnlockDateTime(time_t time)
{
}

void SinglePointConfiguration::SetGracePeriodEndTime(time_t time)
{
}
