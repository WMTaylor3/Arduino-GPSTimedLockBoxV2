// 
// 
// 

#include "UserInput.h"

startupMode UserInput::GetStartUpMode()
{
	switch (GetCurrentButtons())
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

buttonState UserInput::GetCurrentButtons()
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

bool UserInput::ValidateCodeForStartupMode(startupMode modeToAuthenticate)
{
	char expectedCode[10];
	uint8_t codeLength = 0;
	bool isValid = true;

	switch (modeToAuthenticate)
	{
	case(calibrateClock):
		strlcpy(expectedCode, codeCalibrate, 10);
		codeLength = 7;
		break;
	case(extraTime):
		strlcpy(expectedCode, codeExtraTime, 10);
		codeLength = 7;
		break;
	case(configureUnit):
		strlcpy(expectedCode, codeConfigure, 10);
		codeLength = 7;
		break;
	case(overrideUnlock):
		strlcpy(expectedCode, codeOverride, 10);
		codeLength = 10;
		break;
	default:
		return false;
		break;
	}

	display.WriteEnterPasscode();
	delay(1000);
	uint8_t i = 0;
	while (i < codeLength)
	{
		int8_t inputValue = (int)GetCurrentButtons(); // Method returns enum which can be cast to an int for its value, in this case 1, 2 or 3 (L, C, R) are valid.
		if (inputValue > 0 && inputValue < 4)
		{
			if (inputValue != expectedCode[i])
			{
				isValid = false;
			}
			display.CharTyped(i);
			i++;
			delay(300);
		}
	}
	return isValid;
}

uint32_t UserInput::GetExtraTimeValue()
{
	display.WriteTimeExtensionValues(0, 0);
	return 0;
}
