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

time_t Setup::ParseDateTimeInputToTimeT(char* dateTimeString)
{
    return time_t();
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
    char* rx_string = new char[2];
    Serial.print(F("How many 4D points do you wish to configure? (Between 1 and 5)."));
    bool validUserInput = false;
    do {
        Serial.print(F(": "));
        GetUserInput(rx_string, 1);
    } while (!ValidateUserInputNumberOfPoints(rx_string));

    uint8_t numPointInput = rx_string[0] - 48; // Convert to integer.
    delete(rx_string);
    return numPointInput;
}

bool Setup::ValidateUserInputNumberOfPoints(char* rx_string)
{
    return rx_string[0] > '0' && rx_string[0] < '6';
}

bool Setup::ValidateNumberOfPoints(uint8_t numberOfPoints)
{
    return (numberOfPoints > 0 && numberOfPoints < 6);
}

time_t Setup::PromptForGameStartDateTime()
{
    //ISO 8601 format without the timezone offset
    char* rx_string = new char[20];
    Serial.println(F("Enter the date/time value of the final unlock location"));
    Serial.println(F("Formatting:"));
    Serial.println(F("    Must be of format YYYY-MM-DDTHH:MM:SS."));
    Serial.println(F("    Time must be in 24 hour format."));
    Serial.println(F("    The hyphens, colons and 'T' characters are required"));
    Serial.println(F("    Leading and trailing zeros are permitted and must be used in single digit days, months and times."));
    Serial.println(F("Examples:"));
    Serial.println(F("    2020-04-03T23:53:26 <- 3rd March 2020 at 11:53PM and 26 seconds."));
    Serial.println(F("    2021-12-25T02:00:00 <- 25th Decemeber 2021 at 2:00AM."));
    bool validUserInput = false;
    do {
        Serial.print(F(": "));
        GetUserInput(rx_string, 19);
    } while (!ValidateUserInputGameStartTime(rx_string));

    time_t startDateTime = ParseDateTimeInputToTimeT(rx_string);
    delete(rx_string);
    return startDateTime;
}

bool Setup::ValidateUserInputGameStartTime(char* rx_string)
{
    return false;
}

bool Setup::ValidateGameStartDateTime(time_t startDateTime)
{
    return false;
}

double Setup::PromptForLatitude(bool final = false)
{
    char* rx_string = new char[12];
    if (final) {
        Serial.println(F("Enter the latitude value of the final unlock location"));
    }
    else {
        Serial.println(F("Enter the latitude value of the next hint reveal location"));
    }
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
    } while (!ValidateUserInputLatitude(rx_string));

    double latInput = atof(rx_string);
    delete(rx_string);
    return latInput;
}

bool Setup::ValidateUserInputLatitude(char* rx_string)
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

bool Setup::ValidateLatitude(double latitude)
{
    return unlockLatitude <= 90 && unlockLatitude >= -90;
}

double Setup::PromptForLongitude(bool final = false)
{
    char* rx_string = new char[13];
    if (final) {
        Serial.println(F("Enter the longitude value of the final unlock location"));
    }
    else {
        Serial.println(F("Enter the longitude value of the next hint reveal location"));
    }
    Serial.println(F("Formatting:"));
    Serial.println(F("    Must have a + or - prepended to it."));
    Serial.println(F("    Must be formatted with three digits prior to the decimal point."));
    Serial.println(F("    Must be formatted with seven digits following the decimal point."));
    Serial.println(F("    Leading and trailing zeros are permitted, however, it is strongly encouraged to have as high a degree of precision as possible."));
    Serial.println(F("Examples:"));
    Serial.println(F("    +102.1234567 <- Acceptable form and precision of positive."));
    Serial.println(F("    -010.9876543 <- Acceptable form and precision of negative."));
    Serial.println(F("    +002.1234500 <- Acceptable form of positive but unideal precision."));
    Serial.println(F("    -110.1234500 <- Acceptable form of negative but unideal precision."));
    bool validUserInput = false;
    do {
        Serial.print(F(": "));
        GetUserInput(rx_string, 12);
    } while (!ValidateUserInputLongitude(rx_string));

    double longInput = atof(rx_string);
    delete(rx_string);
    return longInput;
}

bool Setup::ValidateUserInputLongitude(char* rx_string)
{
    // Must be correct length.
    for (uint8_t i = 0; i < 12; i++) {
        if (rx_string[i] == '\0') {
            Serial.println(F("INVALID: Incorrect input length."));
            return false;
        }
    }
    if (rx_string[12] != '\0') {
        Serial.println(F("INVALID: Incorrect input length."));
        return false;
    }

    // Must start with + or -.
    if (rx_string[0] != '+' && rx_string[0] != '-') {
        Serial.println(F("INVALID: First character must be '+' or '-'."));
        return false;
    }

    // Next must be a decimal point.
    if (rx_string[4] != '.') {
        Serial.println(F("INVALID: Decimal point ommitted or incorrectly placed."));
        return false;
    }

    // Next must be three digits between 0 and 9.
    for (uint8_t i = 1; i < 4; i++) {
        if (rx_string[i] < '0' || rx_string[i] > '9') {
            Serial.println(F("INVALID: Invalid character found prior to decimal point."));
            return false;
        }
    }

    // Next must be seven digits between 0 and 9.
    for (uint8_t i = 5; i < 11; i++) {
        if (rx_string[i] < '0' || rx_string[i] > '9') {
            Serial.println(F("INVALID: Invalid character found following decimal point."));
            return false;
        }
    }

    return true;
}

bool Setup::ValidateLongitude(double longitude)
{
    return unlockLatitude <= 180 && unlockLatitude >= -180;
}

time_t Setup::PromptForNextPointDateTime(bool final = false)
{
    return time_t();
}

bool Setup::ValidateNextPointDateTime(time_t nextPointDateTime)
{
    return false;
}

time_t Setup::PromptForGracePeriodDuration(bool final = false)
{
    return time_t();
}

bool Setup::ValidateGracePeriodDuration(uint8_t durationInMinutes)
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
    uint8_t numberOfPoints = 0;
    do {
        numberOfPoints = PromptForNumberOfPoints();
    } while (!ValidateNumberOfPoints(numberOfPoints));
    sysConfig = new SystemConfiguration(numberOfPoints);
    ClearScreen();

    time_t gameStartDateTime = 0;
    do {
        gameStartDateTime = PromptForGameStartDateTime(); // Parameter will evaluate to true on the final loop.
    } while (!ValidateGameStartDateTime(gameStartDateTime));
    ClearScreen();
    sysConfig->SetGameStartDateTime(gameStartDateTime);

    // For each time/place as quantified above.
    for (uint8_t i = 0; i < numberOfPoints; i++) {
        double unlockLatitude = 0;
        do {
            unlockLatitude = PromptForLatitude(i = numberOfPoints-1); // Parameter will evaluate to true on the final loop.
        } while (!ValidateLatitude(unlockLatitude));
        ClearScreen();

        double unlockLongitude = 0;
        do {
            unlockLongitude = PromptForLongitude(i = numberOfPoints - 1); // Parameter will evaluate to true on the final loop.
        } while (!ValidateLongitude(unlockLongitude));
        ClearScreen();

        time_t unlockDateTime = 0;
        do {
            unlockDateTime = PromptForNextPointDateTime(i = numberOfPoints - 1); // Parameter will evaluate to true on the final loop.
        } while (!ValidateNextPointDateTime(unlockDateTime));
        ClearScreen();

        time_t gracePeriodEndTime = 0;
        do {
            gracePeriodEndTime = PromptForGracePeriodDuration(i = numberOfPoints - 1); // Parameter will evaluate to true on the final loop.
        } while (!ValidateGracePeriodDuration(gracePeriodEndTime));
        ClearScreen();

        sysConfig->getPoint(i)->SetUnlockLocation(unlockLatitude, unlockLongitude);
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

void SystemConfiguration::SetGameStartDateTime(time_t dateTime) {
    gameStartDateTime = dateTime;
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
