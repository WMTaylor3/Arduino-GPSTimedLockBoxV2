# Arduino Timed GPS Lockbox

##### TODOs/Gripes
* Migrate GPS library from TinyGPS++ to NeoGPS in order to take advantage of higher precision. (No longer using doubles.) This should allow us to remove or mitigate the use of the "Within radius" functionality and get a more accurate destination.
* Sort out "Backspace is read as an input character" issue when configuring via terminal window (Serial).