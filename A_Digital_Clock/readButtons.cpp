// 
// 
// 

#include "readButtons.h"

#define COUNT_1S		500		// 
#define CHANGE_1S		100		//

uint8_t f1Button; 
uint8_t f2Button, f2Button1s;
uint32_t count = 0;
uint8_t count1s = 0;

bool flag1s = 0;

unsigned char But1_read1, But1_read2, But2_read1, But2_read2;

/*	The first button is used to change modes. 
	There are five modes in this project. 
	The description of the modes is in the FiniteStateMachines.cpp file. */
void readModeButton(uint8_t Button1) {
	But1_read1 = But1_read2;
	But1_read2 = digitalRead(Button1);
	if (But1_read1 == But1_read2 && But2_read2 == But2_read1 && But2_read1 == 1) {
		if (But1_read1 == 0) {
			f1Button = 1;
		}
		else {
			f1Button = 0;
		}
	}
}

/*	The second button is to modify the value of the parameters of a digital clock and a stopwatch as well. 
	Those parameters are hour, minute, second and one hundredth of a second. 
	When adjusting the digital clock, if we press this button in more than 1s, the value will increase 5 times per second automatically. */
void readAdjustmentButton(uint8_t Button2) {
	But2_read1 = But2_read2;
	But2_read2 = digitalRead(Button2);
	if (But2_read1 == But2_read2 && But1_read2 == But1_read1 && But1_read1 == 1) {
		if (But2_read1 == 0) {
			f2Button = 1;
			count++;
			if (count >= COUNT_1S) {
				f2Button1s = 1;
				count1s++;
				if (count1s >= CHANGE_1S) {
					flag1s = 1;
					count1s = 0;
				}
			}
		}
		else {
			f2Button = 0;
			f2Button1s = 0;
			count = 0;
			count1s = 1;
			flag1s = 0;
		}
	}
}

