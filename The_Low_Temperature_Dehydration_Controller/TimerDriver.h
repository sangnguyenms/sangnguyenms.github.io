// TimerDriver.h

#ifndef _TIMERDRIVER_h
#define _TIMERDRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern uint16_t timeout_Heat;

void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
int SCH_Register_Timer(timercallback callback, uint32_t delay, uint32_t period);
int SCH_Remove_Timer(int id);
void SCH_Go_To_Sleep();

#endif

