# Arduino Timed GPS Lockbox

##### TODOs/Gripes
* Sort out "Backspace is read as an input character" issue when configuring via terminal window (Serial).

##### Validated and working
* Lock/Unlock values for the slider mechanisim.
* Lock() method.
* Override of lock via 10 digit code.
* Configuration of game based on single point via serial input.
* Delay time prior to game start.
* Obtaining GPS fix once game has started.
* Distance to location (still not totally accurate. +/- 15-20 meters).
* Delay between arrival at location and window opening.
* Promting for both keys to be inserted at unlock location.
* Window permitting unlock for a certain time.
* Unlocking at final destination.
* Unit locks after cycling key at end of setup routine.

##### Still need to test
* Calibration of RTC from GPS.
* Multi-point game.
* Adding time via extend time method.
* Adding time to multi-point game and verifying that all times are boosted.

##### Noted as not functioning correctly
* Adding time via extend time method. Doesn't seem to extend window.


2020-06-05T12:45:00

-35.3880590

+174.3436400

2020-06-05T12:50:00


StartDateTime
1591359600
Window Start Time
1591360800
Window End Time
1591362000
CurrentDateTime
1591359364
1591359364

StartDateTime
0
Window Start Time
0
Window End Time
0
3660
1
1
