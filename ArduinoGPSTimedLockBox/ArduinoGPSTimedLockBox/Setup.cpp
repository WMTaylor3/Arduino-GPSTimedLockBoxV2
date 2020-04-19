#include "Setup.h"

uint8_t Setup::numberOfPoints;
uint8_t Setup::currentPointIndex;
time_t Setup::gameStartDateTime;
SinglePointConfiguration* Setup::singlePointConfigurationCollection[5];
bool Setup::timeExtended;

const char errorInvalidInputLength[33] = "INVALID: Incorrect input length.";
const char errorRequiredCharacterOmmitted[93] = "INVALID: Required character (possibly delimiter) ommitted or incorrectly placed. Character: ";
const char errorInvalidCharacterFoundInField[51] = "INVALID: Invalid character found in field. Field: ";

Setup::Setup()
{
    for (uint8_t i = 0; i < 5; i++)
    {
        singlePointConfigurationCollection[i] = new SinglePointConfiguration();
    }
}

//Setup::~Setup() {
//    delete [] singlePointConfigurationCollection; //Removed as we are now static, add this back if we make this class non-static.
//}

void Setup::AwaitUserInput()
{
    while (!Serial.available()) {}
    while (Serial.available()){ Serial.read(); } // Clear buffer
}

void Setup::GetUserInput(char* rx_string, uint8_t maxStringLength)
{
    while (Serial.available()) { Serial.read(); } // Clear buffer
    uint8_t i = 0;
    char rx_char = 0;
    uint8_t maxLengthIncludingTermination = maxStringLength + 1;

    while (true)
    {
        if (Serial.available())
        {
            rx_char = Serial.read();
            Serial.write(rx_char);
            // If they have submitted their string, append NUL and return.
            if (i < maxLengthIncludingTermination && rx_char == '\r')
            {
                rx_string[i] = '\0';
                Serial.println();
                break;
            }
            // Continue reading input till one less than the array size, leaving room for the NUL.
            else if (i < maxStringLength && rx_char != '\r')
            {
                rx_string[i] = rx_char;
                i++;
            }
            else
            {
                Serial.println();
                Serial.print(F("Entry too long. Maximum input length is "));
                Serial.print(maxStringLength);
                Serial.println(F(" characters."));
                Serial.print(F(": "));
                i = 0; // Reset to allow new input.
                rx_char = 0;
            }
        }
    }
}

bool Setup::ValidateUserInputDateTime(char* rx_string)
{
    // Must be correct length.
    for (uint8_t i = 0; i < 19; i++)
    {
        if (rx_string[i] == '\0')
        {
            Serial.println(errorInvalidInputLength);
            return false;
        }
    }
    if (rx_string[19] != '\0')
    {
        Serial.println(errorInvalidInputLength);
        return false;
    }

    // Year digits must be three digits between 0 and 9.
    for (uint8_t i = 0; i < 4; i++)
    {
        if (rx_string[i] < '0' || rx_string[i] > '9')
        {
            Serial.print(errorInvalidCharacterFoundInField);
            Serial.println("Year");
            return false;
        }
    }
    
    // Year must be greater than 1970. This is due to some processing later that will fail otherwise.
    // Further checking of the validity of the date itself will take place later.
    uint16_t year = (
        ((rx_string[0] - 48) * 1000) +
        ((rx_string[1] - 48) * 100) +
        ((rx_string[2] - 48) * 10) +
        (rx_string[3] - 48));
    if (year < 1970)
    {
        return false;
    }

                       
    // Validate first hypen delimiter.
    if (rx_string[4] != '-')
    {
        Serial.print(errorRequiredCharacterOmmitted);
        Serial.println("First hyphen");
        return false;
    }

    // Month digits must be three digits between 0 and 9.
    for (uint8_t i = 5; i < 7; i++)
    {
        if (rx_string[i] < '0' || rx_string[i] > '9')
        {
            Serial.print(errorInvalidCharacterFoundInField);
            Serial.println("Month");
            return false;
        }
    }

    // Validate second hypen delimiter.
    if (rx_string[7] != '-')
    {
        Serial.print(errorRequiredCharacterOmmitted);
        Serial.println("Second hyphen");
        return false;
    }

    // Day digits must be three digits between 0 and 9.
    for (uint8_t i = 8; i < 10; i++)
    {
        if (rx_string[i] < '0' || rx_string[i] > '9')
        {
            Serial.print(errorInvalidCharacterFoundInField);
            Serial.println("Day");
            return false;
        }
    }

    // Validate 'T' delimiter.
    if (rx_string[10] != 'T')
    {
        Serial.print(errorRequiredCharacterOmmitted);
        Serial.println("'T' delimiter");
        return false;
    }

    // Hour digits must be three digits between 0 and 9.
    for (uint8_t i = 11; i < 13; i++)
    {
        if (rx_string[i] < '0' || rx_string[i] > '9')
        {
            Serial.print(errorInvalidCharacterFoundInField);
            Serial.println("Hours");
            return false;
        }
    }

    // Validate first colon delimiter.
    if (rx_string[13] != ':')
    {
        Serial.print(errorRequiredCharacterOmmitted);
        Serial.println("First colon");
        return false;
    }

    // Minutes digits must be three digits between 0 and 9.
    for (uint8_t i = 14; i < 16; i++)
    {
        if (rx_string[i] < '0' || rx_string[i] > '9')
        {
            Serial.print(errorInvalidCharacterFoundInField);
            Serial.println("Minutes");
            return false;
        }
    }

    // Validate second colon delimiter.
    if (rx_string[16] != ':')
    {
        Serial.print(errorRequiredCharacterOmmitted);
        Serial.println("Second colon");
        return false;
    }

    // Seconds digits must be three digits between 0 and 9.
    for (uint8_t i = 17; i < 19; i++)
    {
        if (rx_string[i] < '0' || rx_string[i] > '9')
        {
            Serial.print(errorInvalidCharacterFoundInField);
            Serial.println("Seconds");
            return false;
        }
    }

    return true;
}

time_t Setup::ParseDateTimeInputToTimeT(char* dateTimeString)
{
    uint8_t builtYear = (
        ((dateTimeString[0] - 48) * 1000) +
        ((dateTimeString[1] - 48) * 100) +
        ((dateTimeString[2] - 48) * 10) +
        (dateTimeString[3] - 48)) - 1970; // Offset from 1970. Required by TimeLib.h to store in a byte.

    uint8_t builtMonth = (
        ((dateTimeString[5] - 48) * 10) +
        (dateTimeString[6] - 48));

    uint8_t builtDay = (
        ((dateTimeString[8] - 48) * 10) +
        (dateTimeString[9] - 48));

    uint8_t builtHour = (
        ((dateTimeString[11] - 48) * 10) +
        (dateTimeString[12] - 48));

    uint8_t builtMinute = (
        ((dateTimeString[14] - 48) * 10) +
        (dateTimeString[15] - 48));

    uint8_t builtSecond = (
        ((dateTimeString[17] - 48) * 10) +
        (dateTimeString[18] - 48));

    tmElements_t inputTimeInElements;
    inputTimeInElements.Year = builtYear;
    inputTimeInElements.Month = builtMonth;
    inputTimeInElements.Day = builtDay;
    inputTimeInElements.Hour = builtHour;
    inputTimeInElements.Minute = builtMinute;
    inputTimeInElements.Second = builtSecond;

    return makeTime(inputTimeInElements);
}

uint16_t Setup::ParseMinutesStringToSeconds(char* durationString)
{
    return ((durationString[0] - 48) * 600) + ((durationString[1] - 48) * 60);
}

int32_t Setup::ParseLatLongStringToInt32(char* locationString, latOrLong latOrLong)
{
    uint8_t decimalPosition = 0;
    uint8_t stringLength = 0;
    if (latOrLong == latitude)
    {
        decimalPosition = 3;
        stringLength = 12;
    }
    else if(latOrLong == longitude)
    {
        decimalPosition = 4;
        stringLength = 13;
    }
    else
    {
        return 0;
    }

    Serial.println(locationString);
    // Remove '.'
    for (uint8_t i = decimalPosition; i < stringLength - 1; i++) // Minus 1 so we don't try override the original '\0' with something from out of the array bounds.
    {
        locationString[i] = locationString[i + 1];
    }

    Serial.println(locationString);
    // Remove +/-
    char absoluteValAsString[13];
    strncpy(absoluteValAsString, locationString + 1, stringLength - 2); // Copy from just after the +/- through to (and including the '\0'. Minus 2 accounts for the missing +/- and the missing '.'.

    Serial.println(absoluteValAsString);
    int32_t absoluteVal = atol(absoluteValAsString);
    Serial.println(absoluteVal);
    if (locationString[0] == '-') // Return with +/- added back.
    {
        return -absoluteVal;
    }
    return absoluteVal;
}

void Setup::ClearScreen()
{
    Serial.write(27);       // ESC command
    Serial.print("[2J");    // clear screen command
    Serial.write(27);
    Serial.print("[H");     // cursor to home command
}

void Setup::PrintSplashScreen()
{
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
    Serial.println(F("How many 4D points do you wish to configure? (Between 1 and 5)."));
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
    if (rx_string[0] < '1' || rx_string[0] > '5')
    {
        Serial.println(F("INVALID: Number must be between 1 and 5 (inclusive)."));
        return false;
    }
    return true;
}

bool Setup::ValidateNumberOfPoints(uint8_t numberOfPoints)
{
    if (numberOfPoints < 1 || numberOfPoints > 5)
    {
        Serial.println("Value entered is logically invalid. Try again.");
        Serial.println("Value must be between 1 and 5.");
        Serial.println();
        return false;
    }
    return true;
}

time_t Setup::PromptForGameStartDateTime()
{
    //ISO 8601 format without the timezone offset
    char* rx_string = new char[20];
    Serial.println(F("UTC TIME UTC TIME UTC TIME UTC TIME UTC TIME UTC TIME UTC TIME UTC TIME"));
    Serial.println(F("Enter the UTC date/time value for when you wish the game to start."));
    Serial.println(F("At this date and time the first location hint will be revealed to the user."));
    Serial.println(F("Formatting:"));
    Serial.println(F("    Must be of format YYYY-MM-DDTHH:MM:SS."));
    Serial.println(F("    Time must be in 24 hour format."));
    Serial.println(F("    The hyphens, colons and 'T' characters are required"));
    Serial.println(F("    Leading and trailing zeros are permitted and must be used in single digit days, months and times."));
    Serial.println(F("Examples:"));
    Serial.println(F("    2020-04-03T23:53:26 <- 3rd March 2020 at 11:53PM and 26 seconds UTC."));
    Serial.println(F("    2021-12-25T02:00:00 <- 25th Decemeber 2021 at 2:00AM UTC."));
    bool validUserInput = false;
    do {
        Serial.print(F(": "));
        GetUserInput(rx_string, 19);
    } while (!ValidateUserInputDateTime(rx_string));

    time_t startDateTime = ParseDateTimeInputToTimeT(rx_string);
    delete(rx_string);
    return startDateTime;
}

bool Setup::ValidateGameStartDateTime(time_t startDateTime)
{
    DS1307RTC* clock = new DS1307RTC();
    time_t currentTime = clock->get();
    delete(clock);
    if (startDateTime < currentTime)
    {
        Serial.println("Value entered is logically invalid. Try again.");
        Serial.println("Value must be later than the current date/time.");
        Serial.println();
        return false;
    }
    return true;
}

int32_t Setup::PromptForLatitude(bool final = false)
{
    char* rx_string = new char[12];
    if (final)
    {
        Serial.println(F("Enter the latitude value of the final unlock location"));
    }
    else
    {
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

    int32_t latInt = ParseLatLongStringToInt32(rx_string, latitude);
    delete(rx_string);
    return latInt;
}

bool Setup::ValidateUserInputLatitude(char* rx_string)
{
    // Must be correct length.
    for (uint8_t i = 0; i < 11; i++)
    {
        if (rx_string[i] == '\0') {
            Serial.println(errorInvalidInputLength);
            return false;
        }
    }
    if (rx_string[11] != '\0')
    {
        Serial.println(errorInvalidInputLength);
        return false;
    }

    // Must start with + or -.
    if (rx_string[0] != '+' && rx_string[0] != '-')
    {
        Serial.println(F("INVALID: First character must be '+' or '-'."));
        return false;
    }

    // Next must be a decimal point.
    if (rx_string[3] != '.')
    {
        Serial.println(F("INVALID: Decimal point ommitted or incorrectly placed."));
        return false;
    }

    // Next must be two digits between 0 and 9.
    for (uint8_t i = 1; i < 3; i++)
    {
        if (rx_string[i] < '0' || rx_string[i] > '9')
        {
            Serial.println(F("INVALID: Invalid character found prior to decimal point."));
            return false;
        }
    }

    // Next must be seven digits between 0 and 9.
    for (uint8_t i = 4; i < 11; i++)
    {
        if (rx_string[i] < '0' || rx_string[i] > '9')
        {
            Serial.println(F("INVALID: Invalid character found following decimal point."));
            return false;
        }
    }

    return true;
}

bool Setup::ValidateLatitude(int32_t latitude)
{
    if (latitude > 900000000 || latitude < -900000000)
    {
        Serial.println("Value entered is logically invalid. Try again.");
        Serial.println("Value must be between -90 and +90.");
        Serial.println();
        return false;
    }
    return true;
}

int32_t Setup::PromptForLongitude(bool final = false)
{
    char* rx_string = new char[13];
    if (final)
    {
        Serial.println(F("Enter the longitude value of the final unlock location"));
    }
    else
    {
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

    int32_t longInt = ParseLatLongStringToInt32(rx_string, longitude);

    delete(rx_string);
    return longInt;
}

bool Setup::ValidateUserInputLongitude(char* rx_string)
{
    // Must be correct length.
    for (uint8_t i = 0; i < 12; i++)
    {
        if (rx_string[i] == '\0') {
            Serial.println(errorInvalidInputLength);
            return false;
        }
    }
    if (rx_string[12] != '\0')
    {
        Serial.println(errorInvalidInputLength);
        return false;
    }

    // Must start with + or -.
    if (rx_string[0] != '+' && rx_string[0] != '-')
    {
        Serial.println(F("INVALID: First character must be '+' or '-'."));
        return false;
    }

    // Next must be a decimal point.
    if (rx_string[4] != '.')
    {
        Serial.println(F("INVALID: Decimal point ommitted or incorrectly placed."));
        return false;
    }

    // Next must be three digits between 0 and 9.
    for (uint8_t i = 1; i < 4; i++)
    {
        if (rx_string[i] < '0' || rx_string[i] > '9')
        {
            Serial.println(F("INVALID: Invalid character found prior to decimal point."));
            return false;
        }
    }

    // Next must be seven digits between 0 and 9.
    for (uint8_t i = 5; i < 11; i++)
    {
        if (rx_string[i] < '0' || rx_string[i] > '9')
        {
            Serial.println(F("INVALID: Invalid character found following decimal point."));
            return false;
        }
    }

    return true;
}

bool Setup::ValidateLongitude(int32_t longitude)
{
    if (longitude > 1800000000 || longitude < -1800000000)
    {
        Serial.println("Value entered is logically invalid. Try again.");
        Serial.println("Value must be between -180 and +180.");
        Serial.println();
        return false;
    }
    return true;
}

time_t Setup::PromptForNextPointDateTime(bool final = false)
{
    //ISO 8601 format without the timezone offset
    char* rx_string = new char[20];
    Serial.println(F("UTC TIME UTC TIME UTC TIME UTC TIME UTC TIME UTC TIME UTC TIME UTC TIME"));
    if (final)
    {
        Serial.println(F("Enter the UTC date/time value for when you wish the unit to unlock."));
    }
    else
    {
        Serial.println(F("Enter the UTC date/time value of the next hint reveal."));
    }
    Serial.println(F("Formatting:"));
    Serial.println(F("    Must be of format YYYY-MM-DDTHH:MM:SS."));
    Serial.println(F("    Time must be in 24 hour format."));
    Serial.println(F("    The hyphens, colons and 'T' characters are required"));
    Serial.println(F("    Leading and trailing zeros are permitted and must be used in single digit days, months and times."));
    Serial.println(F("Examples:"));
    Serial.println(F("    2020-04-03T23:53:26 <- 3rd March 2020 at 11:53PM and 26 seconds UTC."));
    Serial.println(F("    2021-12-25T02:00:00 <- 25th Decemeber 2021 at 2:00AM UTC."));
    bool validUserInput = false;
    do {
        Serial.print(F(": "));
        GetUserInput(rx_string, 19);
    } while (!ValidateUserInputDateTime(rx_string));

    time_t nextDateTime = ParseDateTimeInputToTimeT(rx_string);
    delete(rx_string);
    return nextDateTime;
}

bool Setup::ValidateNextPointDateTime(time_t nextPointDateTime)
{
    return true; // Not much validation here other than ensuring it is after the previous one but frankly I can't be bothered implementing that.
}

// Returns as absolute number of seconds.
uint16_t Setup::PromptForGracePeriodDuration()
{
    //ISO 8601 format without the timezone offset
    char* rx_string = new char[3];
    Serial.println(F("Enter the value (in minutes) for how long you wish the grace window to last."));
    Serial.println(F("This is the length of time after the next hint is revealed/unlock time is reached that the unit will be accessible."));
    Serial.println(F("It's purpose it to allow for a margin of error in arriving at the location late and still being able to continue."));
    Serial.println(F("The value must be between 1 and 60 (1 minute to an hour)."));
    Serial.println(F("Formatting:"));
    Serial.println(F("    Must be of format MM."));
    Serial.println(F("    Leading and trailing zeros are permitted and must be used for cases like '01' and '30'."));
    Serial.println(F("Examples:"));
    Serial.println(F("    01 <- 1 Minute."));
    Serial.println(F("    15 <- 15 Minutes."));
    bool validUserInput = false;
    do {
        Serial.print(F(": "));
        GetUserInput(rx_string, 2);
    } while (!ValidateUserInputGracePeriod(rx_string));

    uint16_t graceWindowDuration = ParseMinutesStringToSeconds(rx_string);
    delete(rx_string);
    return graceWindowDuration;
}

bool Setup::ValidateUserInputGracePeriod(char* rx_string)
{
    // Must be correct length.
    for (uint8_t i = 0; i < 2; i++)
    {
        if (rx_string[i] == '\0')
        {
            Serial.println(errorInvalidInputLength);
            return false;
        }
    }
    if (rx_string[2] != '\0')
    {
        Serial.println(errorInvalidInputLength);
        return false;
    }

    // Digits must be three digits between 0 and 9.
    for (uint8_t i = 0; i < 2; i++)
    {
        if (rx_string[i] < '0' || rx_string[i] > '9')
        {
            Serial.println(F("INVALID: Invalid character found in grace period value."));
            return false;
        }
    }

    return true;
}

bool Setup::ValidateGracePeriodDuration(uint16_t durationInSeconds)
{
    if (durationInSeconds > 3600 || durationInSeconds < 60)
    {
        Serial.println("Value entered is logically invalid. Try again.");
        Serial.println("Value must be between 1 and 60 minutes.");
        Serial.println();
        return false;
    }
    return true;
}

void Setup::Initialize()
{
    ZeroConfigAndEEPROM();

    ClearScreen();
    PrintSplashScreen();
    AwaitUserInput();
    ClearScreen();

    timeExtended = false;
    currentPointIndex = 0;
    
    // Total number of times/places to be included in the hunt.
    uint8_t pointCount = 0;
    do {
        pointCount = PromptForNumberOfPoints();
    } while (!ValidateNumberOfPoints(pointCount));
    numberOfPoints = pointCount;

    ClearScreen();

    time_t gameStart = 0;
    do {
        gameStart = PromptForGameStartDateTime(); // Parameter will evaluate to true on the final loop.
    } while (!ValidateGameStartDateTime(gameStart));
    gameStartDateTime = gameStart;

    ClearScreen();

    // For each time/place as quantified above.
    for (uint8_t i = 0; i < pointCount; i++)
    {
        double unlockLatitude = 0;
        do {
            unlockLatitude = PromptForLatitude(i == pointCount -1); // Parameter will evaluate to true on the final loop.
        } while (!ValidateLatitude(unlockLatitude));
        ClearScreen();

        double unlockLongitude = 0;
        do {
            unlockLongitude = PromptForLongitude(i == pointCount - 1); // Parameter will evaluate to true on the final loop.
        } while (!ValidateLongitude(unlockLongitude));
        ClearScreen();

        time_t unlockDateTime = 0;
        do {
            unlockDateTime = PromptForNextPointDateTime(i == pointCount - 1); // Parameter will evaluate to true on the final loop.
        } while (!ValidateNextPointDateTime(unlockDateTime));
        ClearScreen();

        uint16_t gracePeriodInSeconds = 0;
        do {
            gracePeriodInSeconds = PromptForGracePeriodDuration();
        } while (!ValidateGracePeriodDuration(gracePeriodInSeconds));
        time_t gracePeriodEndDateTime = unlockDateTime + gracePeriodInSeconds;
        ClearScreen();

        singlePointConfigurationCollection[i]->SetLocation(unlockLatitude, unlockLongitude);
        singlePointConfigurationCollection[i]->SetDateTime(unlockDateTime);
        singlePointConfigurationCollection[i]->SetGracePeriodEndDateTime(gracePeriodEndDateTime);
    }

    SaveConfigToEEPROM();
}

time_t Setup::GetGameStartDateTime()
{
    return gameStartDateTime;
}

latLongLocation Setup::GetCurrentPointLocation()
{
    return singlePointConfigurationCollection[currentPointIndex]->GetLocation();
}

time_t Setup::GetCurrentPointWindowOpenTime()
{
    return singlePointConfigurationCollection[currentPointIndex]->GetDateTime();
}

time_t Setup::GetCurrentPointGracePeriodEndTime()
{
    return singlePointConfigurationCollection[currentPointIndex]->GetGracePeriodEndDateTime();
}

uint8_t Setup::GetCurrentPointNumber()
{
    return currentPointIndex + 1;
}

uint8_t Setup::GetTotalPointCount()
{
    return numberOfPoints;
}

void Setup::ProgressToNextPoint()
{
    if (currentPointIndex < numberOfPoints - 1) {
        currentPointIndex++;
        EEPROM.update(1, currentPointIndex);
    }
}

bool Setup::IsFinalPoint()
{
    return currentPointIndex == (numberOfPoints - 1);
}

void Setup::ExtendTime(uint32_t duration, bool isInWindow)
{
    if (timeExtended) { return; }
    for (uint8_t i = currentPointIndex; i < numberOfPoints - 1; i++)
    {
        if (!isInWindow)
        {
            singlePointConfigurationCollection[i]->SetDateTime(singlePointConfigurationCollection[i]->GetDateTime() + duration);
        }
        singlePointConfigurationCollection[i]->SetGracePeriodEndDateTime(singlePointConfigurationCollection[i]->GetGracePeriodEndDateTime() + duration);
    }
    timeExtended = true;
    SaveConfigToEEPROM();
}


// EEPROM
void Setup::LoadConfigFromEEPROM()
{
    numberOfPoints = EEPROM.read(0);
    currentPointIndex = EEPROM.read(1);
    timeExtended = EEPROM.read(2);
    gameStartDateTime = ReadUnsignedInt32AsBytesFromEEPROM(3);

    uint8_t storageAddress = 7;
    for (uint8_t i = 0; i < numberOfPoints; i++)
    {
        int32_t lat = ReadSignedInt32AsBytesFromEEPROM(storageAddress);
        storageAddress += 4;
        int32_t lng = ReadSignedInt32AsBytesFromEEPROM(storageAddress);
        storageAddress += 4;
        time_t dt = ReadUnsignedInt32AsBytesFromEEPROM(storageAddress);
        storageAddress += 4;
        time_t gp = ReadUnsignedInt32AsBytesFromEEPROM(storageAddress);
        storageAddress += 4;

        singlePointConfigurationCollection[i]->SetLocation(lat, lng);
        singlePointConfigurationCollection[i]->SetDateTime(dt);
        singlePointConfigurationCollection[i]->SetGracePeriodEndDateTime(gp);
    }
}

void Setup::SaveConfigToEEPROM()
{
    EEPROM.update(0, numberOfPoints);
    EEPROM.update(1, currentPointIndex);
    EEPROM.update(2, timeExtended);
    StoreUnsignedInt32AsBytesInEEPROM(gameStartDateTime, 3);

    uint8_t storageAddress = 7;
    for (uint8_t i = 0; i < numberOfPoints; i++)
    {
        StoreSignedInt32AsBytesInEEPROM(singlePointConfigurationCollection[i]->GetLocation().latitude, storageAddress);
        storageAddress += 4;
        StoreSignedInt32AsBytesInEEPROM(singlePointConfigurationCollection[i]->GetLocation().longitude, storageAddress);
        storageAddress += 4;
        StoreUnsignedInt32AsBytesInEEPROM(singlePointConfigurationCollection[i]->GetDateTime(), storageAddress);
        storageAddress += 4;
        StoreUnsignedInt32AsBytesInEEPROM(singlePointConfigurationCollection[i]->GetGracePeriodEndDateTime(), storageAddress);
        storageAddress += 4;
    }
}

void Setup::StoreUnsignedInt32AsBytesInEEPROM(uint32_t data, uint8_t startIndex)
{
    union convertUnsignedInt32_t {
        uint32_t uint32;
        byte byteArray[4];
    } unsignedInt32Union;

    unsignedInt32Union.uint32 = data;

    EEPROM.update(startIndex, unsignedInt32Union.byteArray[0]);
    startIndex++;
    EEPROM.update(startIndex, unsignedInt32Union.byteArray[1]);
    startIndex++;
    EEPROM.update(startIndex, unsignedInt32Union.byteArray[2]);
    startIndex++;
    EEPROM.update(startIndex, unsignedInt32Union.byteArray[3]);
}

void Setup::StoreSignedInt32AsBytesInEEPROM(int32_t data, uint8_t startIndex)
{
    union convertSignedInt32_t {
        int32_t int32;
        byte byteArray[4];
    } signedInt32Union;

    signedInt32Union.int32 = data;

    EEPROM.update(startIndex, signedInt32Union.byteArray[0]);
    startIndex++;
    EEPROM.update(startIndex, signedInt32Union.byteArray[1]);
    startIndex++;
    EEPROM.update(startIndex, signedInt32Union.byteArray[2]);
    startIndex++;
    EEPROM.update(startIndex, signedInt32Union.byteArray[3]);
}

uint32_t Setup::ReadUnsignedInt32AsBytesFromEEPROM(uint8_t startIndex)
{
    union convertUnsignedInt32_t {
        uint32_t uint32;
        byte byteArray[4];
    } unsignedInt32Union;

    unsignedInt32Union.byteArray[0] = EEPROM.read(startIndex);
    startIndex++;
    unsignedInt32Union.byteArray[1] = EEPROM.read(startIndex);
    startIndex++;
    unsignedInt32Union.byteArray[2] = EEPROM.read(startIndex);
    startIndex++;
    unsignedInt32Union.byteArray[3] = EEPROM.read(startIndex);

    return unsignedInt32Union.uint32;
}

int32_t Setup::ReadSignedInt32AsBytesFromEEPROM(uint8_t startIndex)
{
    union convertSignedInt32_t {
        int32_t int32;
        byte byteArray[4];
    } signedInt32Union;

    signedInt32Union.byteArray[0] = EEPROM.read(startIndex);
    startIndex++;
    signedInt32Union.byteArray[1] = EEPROM.read(startIndex);
    startIndex++;
    signedInt32Union.byteArray[2] = EEPROM.read(startIndex);
    startIndex++;
    signedInt32Union.byteArray[3] = EEPROM.read(startIndex);

    return signedInt32Union.int32;
}

void Setup::ZeroConfigAndEEPROM() {

    numberOfPoints = 5;
    currentPointIndex = 0;
    timeExtended = false;
    gameStartDateTime = 0;

    singlePointConfigurationCollection[0]->SetLocation(0, 0);
    singlePointConfigurationCollection[0]->SetDateTime(0);
    singlePointConfigurationCollection[0]->SetGracePeriodEndDateTime(0);

    singlePointConfigurationCollection[1]->SetLocation(0, 0);
    singlePointConfigurationCollection[1]->SetDateTime(0);
    singlePointConfigurationCollection[1]->SetGracePeriodEndDateTime(0);

    singlePointConfigurationCollection[2]->SetLocation(0, 0);
    singlePointConfigurationCollection[2]->SetDateTime(0);
    singlePointConfigurationCollection[2]->SetGracePeriodEndDateTime(0);

    singlePointConfigurationCollection[3]->SetLocation(0, 0);
    singlePointConfigurationCollection[3]->SetDateTime(0);
    singlePointConfigurationCollection[3]->SetGracePeriodEndDateTime(0);

    singlePointConfigurationCollection[4]->SetLocation(0, 0);
    singlePointConfigurationCollection[4]->SetDateTime(0);
    singlePointConfigurationCollection[4]->SetGracePeriodEndDateTime(0);

    SaveConfigToEEPROM();
}