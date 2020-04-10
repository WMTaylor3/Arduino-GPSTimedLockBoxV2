// 
// 
// 

#include "UserInput.h"

startupMode UserInput::getStartUpMode()
{
	switch (getCurrentButtons())
	{
	case(leftAndCenter):
		return calibrateClock;
		break;
	case(leftAndRight):
		return extraTime;
		break;
	case(centerAndRight):
		return configureUnit;
		break;
	case(all):
		return overrideUnlock;
		break;
	default:
		return normal;
		break;
	}
}

buttonState UserInput::getCurrentButtons()
{
	if ((digitalRead(buttonOne) == LOW) && (digitalRead(buttonTwo) == LOW) && (digitalRead(buttonThree) == LOW))
	{
		return none;
	}
	if ((digitalRead(buttonOne) == HIGH) && (digitalRead(buttonTwo) == LOW) && (digitalRead(buttonThree) == LOW))
	{
		return left;
	}
	if ((digitalRead(buttonOne) == LOW) && (digitalRead(buttonTwo) == HIGH) && (digitalRead(buttonThree) == LOW))
	{
		return center;
	}
	if ((digitalRead(buttonOne) == LOW) && (digitalRead(buttonTwo) == LOW) && (digitalRead(buttonThree) == HIGH))
	{
		return right;
	}
	if ((digitalRead(buttonOne) == HIGH) && (digitalRead(buttonTwo) == HIGH) && (digitalRead(buttonThree) == LOW))
	{
		return leftAndCenter;
	}
	if ((digitalRead(buttonOne) == HIGH) && (digitalRead(buttonTwo) == LOW) && (digitalRead(buttonThree) == HIGH))
	{
		return leftAndRight;
	}
	if ((digitalRead(buttonOne) == LOW) && (digitalRead(buttonTwo) == HIGH) && (digitalRead(buttonThree) == HIGH))
	{
		return centerAndRight;
	}
	if ((digitalRead(buttonOne) == HIGH) && (digitalRead(buttonTwo) == HIGH) && (digitalRead(buttonThree) == HIGH))
	{
		return all;
	}
}

bool UserInput::validateCode(char* expectedPin, uint8_t pinLength)
{
	return false;
}
