# Arduino Timed GPS Lockbox

##### TODOs/Gripes
* Sort out "Backspace is read as an input character" issue when configuring via terminal window (Serial).
* Implement actual game logic.
* Implement read and write of settings to EEPROM.
	* Store at end of setup routine in main ino file.
	* Store after add time method.
	* Read at beginning of normal boot method.
* Implement "Add Time" functionality.
	* Updates settings object and calls save-to-EEPROM method.
	* Flips "once only" boolean in configuration.