// 
// 
// 

#include "FSM.h"
#include "readButtons.h"
#include "LCD_Print.h"

/* The states of Mode button */
enum {
	STATE1, STATE2
}eModeButton;

/* The states of Modifying Button */
enum {
	STATE3, STATE4, STATE5
}eModifyingButton;

/* The modes of the digital clock */
enum {
	DEFAULT_MODE, MODIFY_HOUR, MODIFY_MINUTE, MODIFY_SECOND, STOPWATCH
}eMode;

/* The states of Stopwatch button (Button 2) */
enum {
	PRESSED, RELEASED
}eSwButton;

/* The states of Stopwatch */
enum {
	RUN, STOP, RESET
}eStopwatch;

/* The parameters of the Digital Clock */
uint8_t numMode = 0;	/* 0 - Defautl mode, 1 - Modifying Hour mode, 2 - Modifying Minute mode, 3 - Modifying Second mode, 4 - Stopwatch mode */
uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;

/* The parameters of the Stopwatch */
uint8_t numSwState = 0;		/* 0 - RESET,	1 - RUN,	2 - STOP */
uint8_t sw_minute = 0;
uint8_t sw_second = 0;
uint8_t sw_one_hundredth = 0;
bool	isSwRUN = false;

// f1Button
void FSM_ModeButton() {
	switch (eModeButton)
	{
	case STATE1:
		
		if (f1Button == 1) {
			numMode += 1;
			if (numMode > 4)
				numMode = 0;
			FSM_ModesExchange();
			eModeButton = STATE2;
		}
		break;
	case STATE2:
		if (f1Button == 0)
			eModeButton = STATE1;
		break;
	default:
		break;
	}
}

void FSM_ModesExchange() {
	switch (eMode)
	{
	case DEFAULT_MODE:
		if (numMode == 1) {
			eMode = MODIFY_HOUR;
		}
		// Display the normal clock
		FSM_Normal_Clock();
		Display_Normal_Clock();
		break;
	case MODIFY_HOUR:
		if (numMode == 2) {
			eMode = MODIFY_MINUTE;
		}
		FSM_Modify_Hour();
		/* When the adjusting button is pressed, the hour number stops blinking temporarily
		so that it is displayed smoothly as it is modified. */
		if (f2Button) {
			Display_Normal_Clock();
		}
		else {
			Blink_Hour();
		}
		break;
	case MODIFY_MINUTE:
		if (numMode == 3) {
			eMode = MODIFY_SECOND;
		}
		//Serial.printf("numMode : %d\n", numMode);
		FSM_Modify_Minute();
		if (f2Button) {
			Display_Normal_Clock();
		}
		else {
			Blink_Minute();
		}
		break;
	case MODIFY_SECOND:
		if (numMode == 4) {
			eMode = STOPWATCH;
		}
		//Serial.printf("numMode : %d\n", numMode);
		FSM_Modify_Second();
		if (f2Button) {
			Display_Normal_Clock();
		}
		else {
			Blink_Second();
		}
		break;
	case STOPWATCH:
		if (numMode == 0) {
			eMode = DEFAULT_MODE;
		}
		// Run stopwatch
		Display_StopWatch();
		FSM_SwButton();
		break;
	default:
		break;
	}
}

void FSM_Normal_Clock() {
	second += 1;
	if (second > 59) {
		second = 0;
		minute += 1;
		if (minute > 59) {
			minute = 0;
			hour += 1;
			if (hour > 23) {
				hour = 0;
			}
				
		}
			
	}
}

// f2Button and f2Button1s
void FSM_Modify_Hour() {
	switch (eModifyingButton)
	{
	case STATE3:

		if (f2Button) {
			if (hour >= 23) {
				hour = 0;
			}
			else hour += 1;
			
			eModifyingButton = STATE4;
		}
		break;
	case STATE4:
		if (f2Button == 0)
			eModifyingButton = STATE3;
		if (f2Button1s)
			eModifyingButton = STATE5;

		break;
	case STATE5:
		if (flag1s) {
			if (hour >= 23) {
				hour = 0;
			}
			else hour += 1;
			
			flag1s = 0;
		}
		if (f2Button == 0) eModifyingButton = STATE3;
		break;
	default:
		break;
	}
}

void FSM_Modify_Minute() {
	switch (eModifyingButton)
	{
	case STATE3:

		if (f2Button) {
			if (minute >= 59) {
				minute = 0;
			}
			else minute += 1;
			//Serial.printf("minute = %d\n", minute);
			eModifyingButton = STATE4;
		}
		break;
	case STATE4:
		if (f2Button == 0)
			eModifyingButton = STATE3;
		if (f2Button1s)
			eModifyingButton = STATE5;

		break;
	case STATE5:
		if (flag1s) {
			if (minute >= 59) {
				minute = 0;
			}
			else minute += 1;
			//Serial.printf("minute = %d\n", minute);
			flag1s = 0;
		}
		if (f2Button == 0) eModifyingButton = STATE3;
		break;
	default:
		break;
	}
}

void FSM_Modify_Second() {
	switch (eModifyingButton)
	{
	case STATE3:

		if (f2Button) {
			if (second >= 59) {
				second = 0;
			}
			else second += 1;
			eModifyingButton = STATE4;
		}
		break;
	case STATE4:
		if (f2Button == 0)
			eModifyingButton = STATE3;
		if (f2Button1s)
			eModifyingButton = STATE5;

		break;
	case STATE5:
		if (flag1s) {
			if (second >= 59) {
				second = 0;
			}
			else second += 1;
			flag1s = 0;
		}
		if (f2Button == 0) eModifyingButton = STATE3;
		break;
	default:
		break;
	}
}

void FSM_SwButton() {
	switch (eSwButton)
	{
	case RELEASED:
		if (f2Button) {
			numSwState += 1;
			if (numSwState > 2) {
				numSwState = 0;
			}
			if (numSwState == 0) {
				isSwRUN = false;
				sw_minute = 0;
				sw_second = 0;
				sw_one_hundredth = 0;
				
			}
			else if (numSwState == 1) {
				isSwRUN = true;
			}
			else if (numSwState == 2) {
				isSwRUN = false;				
			}
			eSwButton = PRESSED;
		}	
		break;
	case PRESSED:
		if (f2Button == 0)
			eSwButton = RELEASED;
		break;
	default:
		break;
	}
}

void FSM_SwRUN() {
	sw_one_hundredth += 1;
	if (sw_one_hundredth > 99) {
		sw_one_hundredth = 0;
		sw_second += 1;
		if (sw_second > 59) {
			sw_second = 0;
			sw_minute += 1;
			if (sw_minute > 59) {
				sw_minute = 0;
			}
		}
	}
}
