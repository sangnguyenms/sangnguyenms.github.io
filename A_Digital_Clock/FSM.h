// FSM.h

#ifndef _FSM_h
#define _FSM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern uint8_t numMode;
extern uint8_t hour;
extern uint8_t minute;
extern uint8_t second;

extern uint8_t sw_minute;
extern uint8_t sw_second;
extern uint8_t sw_one_hundredth;
extern bool	isSwRUN;

void FSM_ModeButton();
void FSM_ModesExchange();
void FSM_Normal_Clock();
void FSM_Modify_Hour();
void FSM_Modify_Minute();
void FSM_Modify_Second();
void FSM_SwButton();
void FSM_SwRUN();

#endif

