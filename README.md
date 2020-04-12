# Arduino Timed GPS Lockbox

##### TODOs/Gripes
* Sort out "Backspace is read as an input character" issue when configuring via terminal window (Serial).
* Implement actual game logic.
* Implement read and write of settings to EEPROM.
	* Store at end of setup routine in main ino file.
	* Store after add time method.
	* Read at beginning of normal boot method.
* Look into only 6 digit precision (how much will we lose? Can the library handle 7 digits anyway?).
* Our grace period windows are showing up as empty on EEPROM read. Validate these are reading and saving correctly.
* Action dates seem to be getting mutilated when stored in EEPROM. Check conversion and check storage locations aren't overlapping.
* Validate add time method.