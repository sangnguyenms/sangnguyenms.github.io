// 
// 
// 

#include "LCD_Print.h"
#include "FSM.h"
#include "readButtons.h"
#include <LiquidCrystal_I2C.h>


uint16_t counter1 = 0;		// count to run the stopwatch
uint16_t counter2 = 0;		// count to run the clock

bool flag_display = false;
bool flag_blink = false;
bool flag_stopwatch = false;
bool flag_displaySW = false;
bool flag_sec = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize the LCD in the Setup() function
void LCD_Setup() {
	lcd.init();
	lcd.backlight();
	lcd.begin(16, 2);
	lcd.print(" Digital Clock ");
	lcd.setCursor(4, 1);
	lcd.print("1712938");
	delay(3000);
	lcd.clear();
}

// Counter 
void Count_to_Blink() {
	
	counter2 += 1;		

	if (counter2 == 250) {
		flag_blink = true;
	}
	else if (counter2 > 499) {
		flag_display = true;
		flag_sec = true;
		
		FSM_Normal_Clock();
		counter2 = 0;
	}
	counter1 += 1;
	
	if (counter1 > 4) {
		counter1 = 0;
	}
	if (isSwRUN == 1 && counter1 == 0) {
		FSM_SwRUN();
	}
}
	

// Display normal clock
void Display_Normal_Clock() {
	lcd.setCursor(0, 0);
	lcd.print(" Digital Clock 1");
	if (hour < 10) {
		lcd.setCursor(4, 1);
		lcd.printf("0%d", hour);
	}
	else {
		lcd.setCursor(4, 1);
		lcd.print(hour);
	}
	lcd.setCursor(6, 1);
	lcd.print(":");
	if (minute < 10) {
		lcd.setCursor(7, 1);
		lcd.printf("0%d", minute);
	}
	else {
		lcd.setCursor(7, 1);
		lcd.print(minute);
	}
	lcd.setCursor(9, 1);
	lcd.print(":");
	if (second < 10) {
		lcd.setCursor(10, 1);
		lcd.printf("0%d", second);
	}
	else {
		lcd.setCursor(10, 1);
		lcd.print(second);
	}
	lcd.setCursor(12, 1);
	lcd.print("    ");
}

// Blink the Hour number in the Modifing Hour mode
void Blink_Hour() {
	lcd.setCursor(0, 0);
	lcd.print("  Modify Hour   ");
	if (flag_blink) {
		lcd.setCursor(4, 1);
		lcd.print("  ");
		
		lcd.setCursor(6, 1);
		lcd.print(":");
		if (minute < 10) {
			lcd.setCursor(7, 1);
			lcd.printf("0%d", minute);
		}
		else {
			lcd.setCursor(7, 1);
			lcd.print(minute);
		}
		lcd.setCursor(9, 1);
		lcd.print(":");
		if (second < 10) {
			lcd.setCursor(10, 1);
			lcd.printf("0%d", second);
		}
		else {
			lcd.setCursor(10, 1);
			lcd.print(second);
		}
		lcd.setCursor(12, 1);
		lcd.print("    ");
		
		flag_blink = false;
	}
	else if (flag_display) {
		if (hour < 10) {
			lcd.setCursor(4, 1);
			lcd.printf("0%d", hour);
		}
		else {
			lcd.setCursor(4, 1);
			lcd.print(hour);
		}
		lcd.setCursor(6, 1);
		lcd.print(":");
		if (minute < 10) {
			lcd.setCursor(7, 1);
			lcd.printf("0%d", minute);
		}
		else {
			lcd.setCursor(7, 1);
			lcd.print(minute);
		}
		lcd.setCursor(9, 1);
		lcd.print(":");
		if (second < 10) {
			lcd.setCursor(10, 1);
			lcd.printf("0%d", second);
		}
		else {
			lcd.setCursor(10, 1);
			lcd.print(second);
		}
		lcd.setCursor(12, 1);
		lcd.print("    ");

		flag_display = false;
	}
}

// Blink the Minute number in the Modifing Minute mode
void Blink_Minute() {
	lcd.setCursor(0, 0);
	lcd.print(" Modify Minute  ");
	if (flag_blink) {
		if (hour < 10) {
			lcd.setCursor(4, 1);
			lcd.printf("0%d", hour);
		}
		else {
			lcd.setCursor(4, 1);
			lcd.print(hour);
		}
		lcd.setCursor(6, 1);
		lcd.print(":");
		
		lcd.setCursor(7, 1);
		lcd.print("  ");
		
		lcd.setCursor(9, 1);
		lcd.print(":");
		if (second < 10) {
			lcd.setCursor(10, 1);
			lcd.printf("0%d", second);
		}
		else {
			lcd.setCursor(10, 1);
			lcd.print(second);
		}
		lcd.setCursor(12, 1);
		lcd.print("    ");

		flag_blink = false;
	}
	else if (flag_display) {
		if (hour < 10) {
			lcd.setCursor(4, 1);
			lcd.printf("0%d", hour);
		}
		else {
			lcd.setCursor(4, 1);
			lcd.print(hour);
		}
		lcd.setCursor(6, 1);
		lcd.print(":");
		if (minute < 10) {
			lcd.setCursor(7, 1);
			lcd.printf("0%d", minute);
		}
		else {
			lcd.setCursor(7, 1);
			lcd.print(minute);
		}
		lcd.setCursor(9, 1);
		lcd.print(":");
		if (second < 10) {
			lcd.setCursor(10, 1);
			lcd.printf("0%d", second);
		}
		else {
			lcd.setCursor(10, 1);
			lcd.print(second);
		}
		lcd.setCursor(12, 1);
		lcd.print("    ");

		flag_display = false;
	}
}

// Blink the Second number in the Modifing Second mode
void Blink_Second() {
	lcd.setCursor(0, 0);
	lcd.print(" Modify Second  ");
	if (flag_blink) {
		if (hour < 10) {
			lcd.setCursor(4, 1);
			lcd.printf("0%d", hour);
		}
		else {
			lcd.setCursor(4, 1);
			lcd.print(hour);
		}
		lcd.setCursor(6, 1);
		lcd.print(":");
		if (minute < 10) {
			lcd.setCursor(7, 1);
			lcd.printf("0%d", minute);
		}
		else {
			lcd.setCursor(7, 1);
			lcd.print(minute);
		}
		lcd.setCursor(9, 1);
		lcd.print(":");
		
		lcd.setCursor(10, 1);
		lcd.print("  ");
		
		lcd.setCursor(12, 1);
		lcd.print("    ");

		flag_blink = false;
	}
	else if (flag_display) {
		if (hour < 10) {
			lcd.setCursor(4, 1);
			lcd.printf("0%d", hour);
		}
		else {
			lcd.setCursor(4, 1);
			lcd.print(hour);
		}
		lcd.setCursor(6, 1);
		lcd.print(":");
		if (minute < 10) {
			lcd.setCursor(7, 1);
			lcd.printf("0%d", minute);
		}
		else {
			lcd.setCursor(7, 1);
			lcd.print(minute);
		}
		lcd.setCursor(9, 1);
		lcd.print(":");
		if (second < 10) {
			lcd.setCursor(10, 1);
			lcd.printf("0%d", second);
		}
		else {
			lcd.setCursor(10, 1);
			lcd.print(second);
		}
		lcd.setCursor(12, 1);
		lcd.print("    ");

		flag_display = false;
	}
}

// Display the Stopwatch
void Display_StopWatch() {
	lcd.setCursor(0, 0);
	lcd.print("   Stopwatch    ");
	if (sw_minute < 10) {
		lcd.setCursor(4, 1);
		lcd.printf("0%d", sw_minute);
	}
	else {
		lcd.setCursor(4, 1);
		lcd.print(sw_minute);
	}
	lcd.setCursor(6, 1);
	lcd.print(":");
	if (sw_second < 10) {
		lcd.setCursor(7, 1);
		lcd.printf("0%d", sw_second);
	}
	else {
		lcd.setCursor(7, 1);
		lcd.print(sw_second);
	}
	lcd.setCursor(9, 1);
	lcd.print(":");
	if (sw_one_hundredth < 10) {
		lcd.setCursor(10, 1);
		lcd.printf("0%d", sw_one_hundredth);
	}
	else {
		lcd.setCursor(10, 1);
		lcd.print(sw_one_hundredth);
	}
	lcd.setCursor(12, 1);
	lcd.print("    ");
}
