// readButtons.h

#ifndef _READBUTTONS_h
#define _READBUTTONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern uint8_t f1Button;
extern uint8_t f2Button, f2Button1s;
extern uint32_t count;
extern uint8_t count1s;

extern bool flag1s;

void readModeButton(uint8_t Button1);
void readAdjustmentButton(uint8_t Button2);

#endif

