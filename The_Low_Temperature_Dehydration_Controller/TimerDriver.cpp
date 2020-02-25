// 
// 
// 

#include "TimerDriver.h"
#include "PeripheralsDriver.h"
#define MAX_TASKS 10

uint16_t timeout_Heat = 0;


#define READ_TIME		50000		// timer 10ms
#define SCH_MAX_TASKS	10
#define LED_PIN			14
typedef struct data {
	void(*pTask)(void);
	uint16_t Delay;
	uint16_t Period;
	uint8_t RunMe;
} sTask;

sTask SCH_tasks_G[SCH_MAX_TASKS];
bool is_stopTimer = false;
volatile time_t internal_counter;


/*
	Registers a callback function be called after the specified interval
	(in microseconds, though actual wakeup resolution will depend on the timer resolution).
	Several registrations may be pending at any time. The return value is zero on failure,
	otherwise a unique identifier for this timeout. This identifier can be used to remove a timeout.
	After a timeout has occurred, or the timeout has been removed, the identifier may be reused.
*/
int SCH_Register_Timer(timercallback callback, uint32_t delay, uint32_t period) {
	int idx = 0;

	// First find a gap in the array (if there is one)
	while ((idx < SCH_MAX_TASKS) && (SCH_tasks_G[idx].pTask != 0)) {
		idx += 1;
	}

	if (idx == SCH_MAX_TASKS) { // Have we reached the end of the list?
		Serial.printf("Register %x failed.\n", callback);
		return -1;	// failed
	}

	// If we're here, there is a space in the task array
	SCH_tasks_G[idx].pTask = callback;
	SCH_tasks_G[idx].Delay = delay;
	if (period > 0) {
		SCH_tasks_G[idx].Period = period - 1;
	}
	else if (period == 0) {
		SCH_tasks_G[idx].Period = period;
	}
	SCH_tasks_G[idx].RunMe = 0;

	return idx;
}

void SCH_Update(void) {
	int idx;
	for (idx = 0; idx < SCH_MAX_TASKS; idx++) {
		if (SCH_tasks_G[idx].pTask) {
			if (SCH_tasks_G[idx].Delay == 0) {
				// The task is due to run
				SCH_tasks_G[idx].RunMe = 1;	// Incr the 'RunMe' flag
				if (SCH_tasks_G[idx].Period) {
					// Schedule periodic tasks to run again
					SCH_tasks_G[idx].Delay = SCH_tasks_G[idx].Period;
				}
			}
			else {
				SCH_tasks_G[idx].Delay -= 1;
			}
		}
	}
}

void SCH_Dispatch_Tasks(void) {
	int idx;
	// Dispatches (runs) the next task (if one is ready)
	for (idx = 0; idx < SCH_MAX_TASKS; idx++) {
		if (SCH_tasks_G[idx].RunMe > 0) {
			(*SCH_tasks_G[idx].pTask)();	// Run the task
			SCH_tasks_G[idx].RunMe = 0;	// Reset / Reduce RunMe flag
			// Periodic tasks will automatically run again
			// -if this is a 'one shot' task, remove it from the array
			if (SCH_tasks_G[idx].Period == 0) {
				SCH_Remove_Timer(idx);
			}
		}
	}
	SCH_Go_To_Sleep(); // The scheduler enters idle mode at this point
}

/*
	Remove a previously registered timer callback, using the unique identifier returned by register_timer.
*/
int SCH_Remove_Timer(int id) {
	int Return_code;
	if (SCH_tasks_G[id].pTask == 0) {
		Serial.println("ERROR_SCH_CANNOT_DELETE_TASK.");
		Return_code = -1; // RETURN_ERROR;
	}
	else {
		Return_code = 1;// RETURN_NORMAL;
	}
	Serial.printf("Delete task %d\n", SCH_tasks_G[id].pTask);
	SCH_tasks_G[id].pTask = 0x0000;
	SCH_tasks_G[id].Delay = 0;
	SCH_tasks_G[id].Period = 0;
	SCH_tasks_G[id].RunMe = 0;
	return Return_code;
}

void SCH_Go_To_Sleep(){
	// We do nothing here.
}