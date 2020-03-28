/*
 Name:		ArduinoGPSTimedLockBox.ino
 Created:	3/28/2020 3:42:30 PM
 Author:	William Taylor
*/

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    configureUnit();
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}

void configureUnit() {
    printSplashScreen();
}

void printSplashScreen() {
    Serial.println("+-------------------------+");
    Serial.println("|                         |");
    Serial.println("|    Timed GPS Lockbox    |");
    Serial.println("|      Initial Setup      |");
    Serial.println("|                         |");
    Serial.println("+-------------------------+");
    Serial.println("To continue, press any key...");
    awaitUserInput();
    clearScreen();
}

void awaitUserInput() {
    while (!Serial.available()) {
    }
}

void clearScreen() {
    Serial.write(27);       // ESC command
    Serial.print("[2J");    // clear screen command
    Serial.write(27);
    Serial.print("[H");     // cursor to home command
}