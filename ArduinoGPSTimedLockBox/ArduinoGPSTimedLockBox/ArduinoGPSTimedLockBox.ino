/*
 Name:		ArduinoGPSTimedLockBox.ino
 Created:	3/28/2020 3:42:30 PM
 Author:	William Taylor
*/

void setup() {
    Serial.begin(9600);
    configureUnit();
}

void loop() {
  
}

void configureUnit() {
    printSplashScreen();
    awaitUserInput();
    clearScreen();
    promptForNumberOf4DPoints();
    promptForNumberOf4DPoints();
}

void awaitUserInput() {
    while (!Serial.available()) {}
    Serial.read();
}

char* getUserInput() {
    byte rx_byte = 0;
    char rx_string[13];
    uint8_t i = 0;

    while (true) {
        if (Serial.available()) {
            rx_byte = Serial.read();
            Serial.write(rx_byte);
            // If they have submitted their string, append NUL and return.
            if (i < 13 && rx_byte == '\n' || rx_byte == '\r') {
                rx_string[i] = '\0';
                Serial.println();
                return rx_string;
            }
            // Continue reading input till one less than the array size, leaving room for the NUL.
            else if (i < 12 && rx_byte != '\n' && rx_byte != '\r') {
                rx_string[i] = rx_byte;
                i++;
            }
            else
            {
                Serial.println();
                Serial.print("Entry too long. Enter input with less than 13 characters: ");
                i = 0;
                rx_byte = 0;
            }
        }
    }
}

void clearScreen() {
    Serial.write(27);       // ESC command
    Serial.print("[2J");    // clear screen command
    Serial.write(27);
    Serial.print("[H");     // cursor to home command
}

void printSplashScreen() {
    Serial.println("+-------------------------+");
    Serial.println("|                         |");
    Serial.println("|    Timed GPS Lockbox    |");
    Serial.println("|      Initial Setup      |");
    Serial.println("|                         |");
    Serial.println("+-------------------------+");
    Serial.println("To continue, press any key...");
}

void promptForNumberOf4DPoints()
{
    Serial.print("How many 4D points do you wish to configure? (1-5): ");
    getUserInput();
}