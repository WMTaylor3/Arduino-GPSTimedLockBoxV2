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

char* UserInput::GetUserInput(uint8_t maxStringLength = 12) {
    while (Serial.available()) { Serial.read(); } // Clear buffer
    static byte i = 0;
    char* rx_string = new char[13];
    char rx_char = 0;;
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

uint8_t UserInput::ConfigureNumberOf4DPoints()
{
    char charInput = '0';
    while (charInput < '1' || charInput > '5') {
        Serial.print("Entry: ");
        Serial.println(charInput);
        Serial.print(F("How many 4D points do you wish to configure? (1-5): "));
        char* input = GetUserInput(1);
        Serial.println(input);
        Serial.write(input);
        charInput = input[0];
        delete(input);
        input = NULL;
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
    Serial.println("End");
}