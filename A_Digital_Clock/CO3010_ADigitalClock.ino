/*
 Name:		CO3010_ADigitalClock.ino
 Created:	10/7/2019 8:49:16 PM
 Author:	Nguyen Phuoc Sang
 ID:		1712938
*/

#include "LCD_Print.h"
#include "FSM.h"
#include "readButtons.h"

#define SCL_PIN			5		// pin D1 
#define SDA_PIN			4		// pin D2
#define READ_TIME		160000	// timer : 2ms

const uint8_t Button1 = 14;		// pin D5 - 14 MODE Button			|| pin D7 - 13
const uint8_t Button2 = 12;		// pin D6 - 12 Adjusting Button		|| pin D8 - 15

void ICACHE_RAM_ATTR TimerISR() {
	Count_to_Blink();
	readModeButton(Button1);
	readAdjustmentButton(Button2);
	timer1_write(READ_TIME);
}

// the setup function runs once when you press reset or power the board again.
void setup() {
	Serial.begin(115200);
	Serial.println("");
	
	LCD_Setup();

	pinMode(Button1, INPUT);
	pinMode(Button2, INPUT);
	
	timer1_attachInterrupt(TimerISR);
	timer1_enable(TIM_DIV1, TIM_EDGE, TIM_SINGLE);
	timer1_write(READ_TIME);
}

// the loop function runs over and over again until power down or reset
void loop() {
	FSM_ModeButton();
	FSM_ModesExchange();
}
