// 
// 
// 

#include "UserInput.h"

UserInput::UserInput()
{
}

void UserInput::AwaitUserInput() {
    while (!Serial.available()) {}
    Serial.read();
}

char* UserInput::GetUserInput(uint8_t maxStringLength = 12) {
    static byte i = 0;
    char* rx_string = new char[13];
    char rx_char;
    uint8_t maxLengthIncludingTermination = maxStringLength + 1;

    while (true) {
        if (Serial.available()) {
            rx_char = Serial.read();
            Serial.write(rx_char);
            // If they have submitted their string, append NUL and return.
            if (i < maxLengthIncludingTermination && rx_char == '\r') {
                rx_string[i] = '\0';
                Serial.println();
                return rx_string;
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
                i = 0;
                rx_char = 0;
            }
        }
    }
}

void UserInput::ClearScreen() {
    Serial.write(27);       // ESC command
    Serial.print("[2J");    // clear screen command
    Serial.write(27);
    Serial.print("[H");     // cursor to home command
}

void UserInput::PrintSplashScreen() {
    Serial.println(F("+-------------------------+"));
    Serial.println(F("|                         |"));
    Serial.println(F("|    Timed GPS Lockbox    |"));
    Serial.println(F("|      Initial Setup      |"));
    Serial.println(F("|                         |"));
    Serial.println(F("+-------------------------+"));
    Serial.println(F("To continue, press any key..."));
}

void UserInput::PromptForNumberOf4DPoints()
{
    Serial.print(F("How many 4D points do you wish to configure? (1-5): "));
    Serial.print(GetUserInput()[0]);
    // Free string memory once converted to an int.
}

void UserInput::InitialConfiguration()
{
    ClearScreen();
    PrintSplashScreen();
    AwaitUserInput();
    ClearScreen();
    PromptForNumberOf4DPoints();
}