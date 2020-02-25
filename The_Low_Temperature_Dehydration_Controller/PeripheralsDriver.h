// PeripheralsDriver.h

#ifndef _PERIPHERALSDRIVER_h
#define _PERIPHERALSDRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

extern bool isReachMaxTemp;
extern bool isReachMaxHumid;
extern bool HeaterState;
extern bool HeatpumpState;
extern bool volatile isHeaterRun;
extern uint16_t volatile brightness;
void Peripherals_Init();

void Heater();				// Led 1 - pin D1 - 5
void HeatPump();			// Led 2 - pin D2 - 4
void Fan1_Off();			// Led 3 - pin D6 - 12
void Fan1_OnWithHumid();
void Fan2();				// Led 4 - pin D7 - 13
void Fan3();				// Led 5 - pin D8 - 15

void RunHeatPeriodically();
void DHT1();				// Pin D3 - 0
void DHT2();				// Pin D4 - 2
void DHT3();				// Pin D5 - 14
void Choose_DHT();

#endif
