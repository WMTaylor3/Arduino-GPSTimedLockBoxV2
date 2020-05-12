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
	char expectedCode[11];
	bool isValid = true;

	switch (modeToAuthenticate)
	{
	case(calibrateClock):
		strlcpy(expectedCode, codeCalibrate, 11);
		break;
	case(extraTime):
		strlcpy(expectedCode, codeExtraTime, 11);
		break;
	case(configureUnit):
		strlcpy(expectedCode, codeConfigure, 11);
		break;
	case(overrideUnlock):
		strlcpy(expectedCode, codeOverride, 11);
		break;
	default:
		return false;
		break;
	}

	display.WriteEnterPasscode();
	uint32_t start = millis();
	while (millis() - start < 1000) // Ensures a period of 1 second where no buttons are pressed.
	{
		if (GetCurrentButtons() != none) {
			start = millis();
		}
	}
	uint8_t i = 0;
	while (i < 10)
	{
		int8_t inputValue = (int)GetCurrentButtons(); // Method returns enum which can be cast to an int for its value, in this case 1, 2 or 3 (L, C, R) are valid.
		if (inputValue > 0 && inputValue < 4)
		{
			if ((inputValue + 48) != expectedCode[i])
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
	uint8_t hours = 0;
	uint8_t minutes = 0;
	display.WriteTimeExtensionValues(hours, minutes);
	while (true) {
		buttonState input = GetCurrentButtons();
		if (input == center) {
			return (hours * 3600) + (minutes * 60);
		}
		if (input == left) {
			uint32_t timeAtStart = millis();
			while (GetCurrentButtons() == left) {
				if (millis() - timeAtStart > 200)
				{
					if (hours == 60)
					{
						hours = 0;
					}
					else
					{
						hours += 1;
					}
					display.WriteTimeExtensionValues(hours, minutes);
					break;
				}
			};
		}
		if (input == right) {
			uint32_t timeAtStart = millis();
			while (GetCurrentButtons() == right) {
				if (millis() - timeAtStart > 200)
				{
					if (minutes == 60)
					{
						minutes = 0;
					}
					else 
					{
						minutes += 1;
					}
					display.WriteTimeExtensionValues(hours, minutes);
					break;
				}
			};
		}
	}

	return 0;
}

void UserInput::AwaitKeyLock()
{
	while (!IsKeyStateUnlocked()) {}
	delay(300);
	while (IsKeyStateUnlocked()) {}
	delay(300);
	return;
}

bool UserInput::IsKeyStateUnlocked()
{
	return (digitalRead(key) == HIGH);
}
