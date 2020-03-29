// 
// 
// 

#include "UserInput.h"

UserInput::UserInput()
{
}

void UserInput::AwaitUserInput() {
    while (!Serial.available()) {}
    while (Serial.available()) { Serial.read(); } // Clear buffer
}

// Prompts user for input on serial terminal.
// Param rx_string: char* to char[] in which to store the string, must be 1 more than max expected string length.
// Param maxStringLength: uint8_t containing maximum expected string length not including null termination.
void UserInput::GetUserInput(char* rx_string, uint8_t maxStringLength) {
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

uint8_t UserInput::ConfigureNumberOf4DPoints()
{
    char charInput = '0';
    char* rx_string = NULL;
    while (charInput < '1' || charInput > '5') {
        Serial.print(F("How many 4D points do you wish to configure? (Between 1 and 5): "));
        rx_string = new char[2];
        GetUserInput(rx_string, 1);
        charInput = rx_string[0];
        delete(rx_string);
        rx_string = NULL;
    }
    return charInput - 48; // Convert to integer.
}

void UserInput::InitialConfiguration()
{
    ClearScreen();
    PrintSplashScreen();
    AwaitUserInput();
    ClearScreen();
    ConfigureNumberOf4DPoints();
}