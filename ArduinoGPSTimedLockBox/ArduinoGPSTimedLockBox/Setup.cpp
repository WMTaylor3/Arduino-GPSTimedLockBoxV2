// 
// 
// 

#include "Setup.h"

/////////////////////////////////////// User Input ///////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////TODO: fix issue with backspacing on user input method
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
    char* rx_string = new char[2];
    Serial.print(F("How many 4D points do you wish to configure? (Between 1 and 5): "));
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
    double latInput = -36.696190;
    char* rx_string = new char[12];
    Serial.println(F("Enter the latitude value of the final unlock location."));
    Serial.println(F("Formatting:"));
    Serial.println(F("    Must have a + or - prepended to it."));
    Serial.println(F("    Must be formatted with two digits prior to the decimal point."));
    Serial.println(F("    Must be formatted with seven digits following the decimal point."));
    Serial.println(F("    Leading and trailing zeros are permitted, however, it is strongly encouraged to have as high a degree of precision as possible."));
    Serial.println(F("Examples:"));
    Serial.println(F("    +12.1234567 <- Acceptable form and precision of positive."));
    Serial.println(F("    -01.9876543 <- Acceptable form and precision of negative."));
    Serial.println(F("    +02.1234500 <- Acceptable form of positive but unideal precision."));
    Serial.println(F("    -11.1234500 <- Acceptable form of negative but unideal precision."));
    bool validUserInput = false;
    do {
        Serial.print(F(": "));
        GetUserInput(rx_string, 11);
    } while (!ValidateUserInputUnlockLatitude(rx_string));

    Serial.println(rx_string);
    delete(rx_string);
}

bool Setup::ValidateUserInputUnlockLatitude(char* rx_string)
{
    // Must be correct length.
    for (uint8_t i = 0; i < 11; i++) {
        if (rx_string[i] == '\0') {
            Serial.println(F("INVALID: Incorrect input length."));
            return false;
        }
    }
    if (rx_string[11] != '\0') {
        Serial.println(F("INVALID: Incorrect input length."));
        return false;
    }

    // Must start with + or -.
    if (rx_string[0] != '+' && rx_string[0] != '-') {
        Serial.println(F("INVALID: First character must be '+' or '-'."));
        return false;
    }

    // Next must be a decimal point.
    if (rx_string[3] != '.') {
        Serial.println(F("INVALID: Decimal point ommitted or incorrectly placed."));
        return false;
    }

    // Next must be two digits between 0 and 9.
    for (uint8_t i = 1; i < 3; i++) {
        if (rx_string[i] < '0' || rx_string[i] > '9') {
            Serial.println(F("INVALID: Invalid character found prior to decimal point."));
            return false;
        }
    }

    // Next must be seven digits between 0 and 9.
    for (uint8_t i = 4; i < 11; i++) {
        if (rx_string[i] < '0' || rx_string[i] > '9') {
            Serial.println(F("INVALID: Invalid character found following decimal point."));
            return false;
        }
    }

    return true;
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
        double unlockLatitude = 0;
        do {
            unlockLatitude = PromptForUnlockLatitude();
        } while (!ValidateUnlockLatitude(unlockLatitude));

        double unlockLongitude = 0;
        do {
            unlockLongitude = PromptForUnlockLongitude();
        } while (!ValidateUnlockLongitude(unlockLongitude));
       
        time_t hintRevealDateTime = 0;
        do {
            hintRevealDateTime = PromptForHintRevealDateTime();
        } while (!ValidateHintRevealDateTime(hintRevealDateTime));

        time_t unlockDateTime = 0;
        do {
            unlockDateTime = PromptForUnlockDateTime();
        } while (!ValidateUnlockDateTime(unlockDateTime));

        time_t gracePeriodEndTime = 0;
        do {
            gracePeriodEndTime = PromptForGracePeriodEndTime();
        } while (!ValidateGracePeriodEndTime(gracePeriodEndTime));

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
