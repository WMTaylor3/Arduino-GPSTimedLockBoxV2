# Arduino Timed GPS Lockbox

##### TODOs/Gripes
* Migrate GPS library from TinyGPS++ to NeoGPS in order to take advantage of higher precision. (No longer using doubles.) This should allow us to remove or mitigate the use of the "Within radius" functionality and get a more accurate destination.
* Sort out "Backspace is read as an input character" issue when configuring via terminal window (Serial).
* Implement SinglePointConfigurationClass.
* Fix calibration issue with RTC.
* Implement Startup controls.
    * Three Buttons: Override unlock. (Long Password)
    * Two Outside: Once off add extra time. (5 digit password)
    * Left & Center: Calibrate RTC from GPS. (5 digit password)
    * Right & Center: Serial Routine. (5 digit password)
* Implement actual game logic.