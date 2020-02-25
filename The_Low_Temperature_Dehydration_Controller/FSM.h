// FSM.h

#ifndef _FSM_h
#define _FSM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void FSM_Temperature();

void FSM_Humidity();

#endif

