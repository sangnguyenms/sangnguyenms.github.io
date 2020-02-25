/*
 Name:		CO3010_TheLTDController.ino
 Created:	11/11/2019 10:04:06 PM
 Author:	Nguyen Phuoc Sang
 ID:		1712938
*/

/*
	An LTD controller operation
	1. At the beginning, the heater will be turned on to warm the dry room. 
	When the temperature inside the dry	room reaches a user-defined maximum
	temperature value, the heater will be stopped.
	2. When the heater is on, the fan2 will be on as well to make the temperature
	of the air be evenly distributed in the dry room.
	3. If the humidity inside the dry room is greater than a user-defined maximum
	humidity, the fan1 will be turned on to transfer the humidity air from the dry
	room to the outside. We can control the speed of the fan1. For example,
	when the humidity is about 90% or more, the fan1 will run in full speed. 
	When 80%, the fan will run at 80% of the full speed and so on.
	4. When the heat pump is on, the fan 3 is also on to help the heat pump work
	better.
	5. Please note that when the heater is on, the heat pump is off and vice versa.
	6. The user can set the timer so that the heater and heat pump can be turned 
	on periodically.
	7. The controller should add time out for each operation.
	8. The controller should have at least three humidity sensors and three 
	temperature sensors for reliability	operations.

	Your tasks in this lab are to build an LTD controller including
	1. Writing a proposal to describe your solution as detailed as possible.
	2. Writing the code for the LTD controller.

	Please note that you can simulate the heater, heat pump, and fans using LEDs.
*/

// the setup function runs once when you press reset or power the board

#include "PeripheralsDriver.h"
#include "FSM.h"
#include "TimerDriver.h"

#define READ_TIME 50000		// Timer 10ms

void Add_Task();

void ICACHE_RAM_ATTR TimerISR() {
	SCH_Update();
	//RunHeatPeriodically();
	timer1_write(READ_TIME);
}

void setup() {
	Add_Task();
	Peripherals_Init();

	noInterrupts();
	timer1_attachInterrupt(TimerISR);
	timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
	timer1_write(READ_TIME);
	interrupts();
}

// the loop function runs over and over again until power down or reset
void loop() {
	SCH_Dispatch_Tasks();
	FSM_Temperature();
	FSM_Humidity();
}

void Add_Task() {
	SCH_Register_Timer(RunHeatPeriodically, 0, 1000);
	SCH_Register_Timer(Choose_DHT, 0, 200);
}
