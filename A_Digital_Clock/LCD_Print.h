// LCD_Print.h

#ifndef _LCD_PRINT_h
#define _LCD_PRINT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern uint16_t counter1;
extern uint16_t counter2;

extern bool flag_display;
extern bool flag_blink;
extern bool flag_stopwatch;
extern bool flag_displaySW;
extern bool flag_sec;

void LCD_Setup();
void Count_to_Blink();
void Display_Normal_Clock();
void Blink_Hour();
void Blink_Minute();
void Blink_Second();
void Display_StopWatch();

#endif

