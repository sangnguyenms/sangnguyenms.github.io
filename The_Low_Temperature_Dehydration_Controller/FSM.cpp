// 
// 
// 

#include "FSM.h"
#include "TimerDriver.h"
#include "PeripheralsDriver.h"
enum { HEAT_ON, HEAT_OFF }HeatState;
enum { FAN1_OFF, FAN1_ON }Fan1State;

void FSM_Temperature() {
	switch (HeatState)
	{
	case HEAT_ON:
		if (isReachMaxTemp == true) {
			HeatState = HEAT_OFF;
		}
		HeatPump();
		Fan3();
		Heater();
		Fan2();
		break;
	case HEAT_OFF:
		if (isReachMaxTemp == false) {
			HeatState = HEAT_ON;
		}
		Heater();
		Fan2();
		HeatPump();
		Fan3();
		break;
	default:
		break;
	}
}

void FSM_Humidity() {
	switch (Fan1State)
	{
	case FAN1_OFF:
		if (isReachMaxHumid) {
			Fan1State = FAN1_ON;
		}
		Fan1_Off();
		break;
	case FAN1_ON:
		if (isReachMaxHumid == false) {
			Fan1State = FAN1_OFF;
		}
		Fan1_OnWithHumid();
		break;
	default:
		break;
	}
}

