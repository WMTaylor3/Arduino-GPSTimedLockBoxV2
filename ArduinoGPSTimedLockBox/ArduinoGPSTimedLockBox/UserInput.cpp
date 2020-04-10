// 
// 
// 

#include "UserInput.h"

startupMode UserInput::getStartUpMode()
{
	if ((digitalRead(buttonOne) == LOW) && (digitalRead(buttonTwo) == LOW) && (digitalRead(buttonThree) == LOW))
	{
		return normal;
	}
	if ((digitalRead(buttonOne) == HIGH) && (digitalRead(buttonTwo) == HIGH) && (digitalRead(buttonThree) == LOW))
	{
		return calibrateClock;
	}
	if ((digitalRead(buttonOne) == LOW) && (digitalRead(buttonTwo) == HIGH) && (digitalRead(buttonThree) == HIGH))
	{
		return configureUnit;
	}
	if ((digitalRead(buttonOne) == HIGH) && (digitalRead(buttonTwo) == LOW) && (digitalRead(buttonThree) == HIGH))
	{
		return extraTime;
	}
	if ((digitalRead(buttonOne) == HIGH) && (digitalRead(buttonTwo) == HIGH) && (digitalRead(buttonThree) == HIGH))
	{
		return overrideUnlock;
	}
}
