// 
// 
// 
#include "DHTesp.h"
#include "PeripheralsDriver.h"

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

#define MAX_TEMPERATURE 29.0	// Celcius degree
#define MAX_HUMIDITY	40.0	// percentage
#define MAX_SPEED		1023	// This value is the max analog one of a pinout on Nodemcu.

#define HEATER_PIN		5		// Led 1 - pin D1 - 5
#define HEATPUMP_PIN	4		// Led 2 - pin D2 - 4
#define FAN1_PIN		12		// Led 3 - pin D6 - 12
#define FAN2_PIN		13		// Led 4 - pin D7 - 13
#define FAN3_PIN		15		// Led 5 - pin D8 - 15

const int DHT1_PIN = 0;			// pin D3 - 0
const int DHT2_PIN = 2;			// pin D4 - 2
const int DHT3_PIN = 14;		// pin D5 - 14

DHTesp dht1, dht2, dht3;

float volatile humidity, temperature, humidity_1, temperature_1, humidity_2, temperature_2, humidity_3, temperature_3;
float volatile DutyCycle = 0;
uint16_t volatile brightness = 0;
bool isSensorActive = false;
bool isReachMaxTemp = false;
bool isReachMaxHumid = false;

bool HeaterState = HIGH;
bool HeatpumpState = LOW;

bool volatile isHeaterRun = true;

// These devices are simulated by using LEDs
void Peripherals_Init() {
	pinMode(HEATER_PIN, OUTPUT);
	pinMode(HEATPUMP_PIN, OUTPUT);
	pinMode(FAN1_PIN, OUTPUT);
	pinMode(FAN2_PIN, OUTPUT);
	pinMode(FAN3_PIN, OUTPUT);

	digitalWrite(HEATER_PIN, HeaterState);
	digitalWrite(HEATPUMP_PIN, HeatpumpState);
	digitalWrite(FAN2_PIN, HeaterState);
	digitalWrite(FAN3_PIN, HeatpumpState);

	dht1.setup(DHT1_PIN, DHTesp::DHT11);
	dht2.setup(DHT2_PIN, DHTesp::DHT11);
	dht3.setup(DHT3_PIN, DHTesp::DHT11);
}


void Heater() {
	digitalWrite(HEATER_PIN, HeaterState);
}	

void HeatPump() {
	digitalWrite(HEATPUMP_PIN, HeatpumpState);
}

// This fan can change its speed within humidity.
void Fan1_Off() {
	analogWrite(FAN1_PIN, 0);
}

void Fan1_OnWithHumid() {
	//digitalWrite(FAN1_PIN, HIGH);
	//Serial.printf("Speed: %d\n", brightness);
	analogWrite(FAN1_PIN, 1023);
}

void Fan2() {
	digitalWrite(FAN2_PIN, HeaterState);
}

void Fan3() {
	digitalWrite(FAN3_PIN, HeatpumpState);
}

void RunHeatPeriodically() {
	//Serial.printf("isHeaterRun: %d\n", isHeaterRun);
	isHeaterRun = !isHeaterRun;
	if (isHeaterRun == true) {
		HeaterState = HIGH;
		HeatpumpState = LOW;
	}
	else if (isHeaterRun == false) {
		HeaterState = LOW;
		HeatpumpState = HIGH;
	}
}

void DHT1() {
	humidity_1 = dht1.getHumidity();
	temperature_1 = dht1.getTemperature();

	/*if (humidity_1 >= MAX_HUMIDITY) {
		isReachMaxHumid = true;
	}
	else {
		isReachMaxHumid = false;
	}

	if (temperature_1 >= MAX_TEMPERATURE) {
		isReachMaxTemp = true;
		HeaterState = LOW;
		HeatpumpState = LOW;
	}
	else {
		isReachMaxTemp = false;
	}*/
}

void DHT2() {
	humidity_2 = dht2.getHumidity();
	temperature_2 = dht2.getTemperature();

	/*if (humidity_2 >= MAX_HUMIDITY) {
		isReachMaxHumid = true;
	}
	else {
		isReachMaxHumid = false;
	}

	if (temperature_2 >= MAX_TEMPERATURE) {
		isReachMaxTemp = true;
		HeaterState = LOW;
		HeatpumpState = LOW;
	}
	else {
		isReachMaxTemp = false;
		if (isHeaterRun) {
			HeaterState = HIGH;
			HeatpumpState = LOW;
		}
		else {
			HeatpumpState = HIGH;
			HeaterState = LOW;
		}
	}*/
}

void DHT3() {
	humidity_3 = dht3.getHumidity();
	temperature_3 = dht3.getTemperature();

	/*if (humidity_3 >= MAX_HUMIDITY) {
		isReachMaxHumid = true;
	}
	else {
		isReachMaxHumid = false;
	}

	if (temperature_3 >= MAX_TEMPERATURE) {
		isReachMaxTemp = true;
		HeaterState = LOW;
		HeatpumpState = LOW;
	}
	else {
		isReachMaxTemp = false;
		if (isHeaterRun) {
			HeaterState = HIGH;
			HeatpumpState = LOW;
		}
		else {
			HeatpumpState = HIGH;
			HeaterState = LOW;
		}
	}*/
}

void Choose_DHT() {
	DHT1();
	DHT2();
	DHT3();
	if (isnan(humidity_1) == false || isnan(temperature_1) == false) {
		if (isnan(humidity_2) == false || isnan(temperature_2) == false) {
			if (isnan(humidity_3) == false || isnan(temperature_3) == false) {
				isSensorActive = true;
				humidity = (humidity_1 + humidity_2 + humidity_3) / 3;
				temperature = (temperature_1 + temperature_2 + temperature_3) / 3;
				Serial.printf("DHT_1_2_3:\thumid: %f\ttemp: %f\tisReachHumid: %d\tisReachTemp: %d\n", humidity, temperature, isReachMaxHumid, isReachMaxTemp);
			}
			else {
				isSensorActive = true;
				humidity = (humidity_1 + humidity_2) / 2;
				temperature = (temperature_1 + temperature_2) / 2;
				Serial.printf("DHT_1_2:\thumid: %f\ttemp: %f\tisReachHumid: %d\tisReachTemp: %d\n", humidity, temperature, isReachMaxHumid, isReachMaxTemp);
			}
		}
		else if (isnan(humidity_3) == false || isnan(temperature_3) == false) {
			isSensorActive = true;
			humidity = (humidity_1 + humidity_3) / 2;
			temperature = (temperature_1 + temperature_3) / 2;
			Serial.printf("DHT_1_3:\thumid: %f\ttemp: %f\tisReachHumid: %d\tisReachTemp: %d\n", humidity, temperature, isReachMaxHumid, isReachMaxTemp);
		}
		else {
			isSensorActive = true;
			humidity = humidity_1;
			temperature = temperature_1;
			Serial.printf("DHT_1:\thumid: %f\ttemp: %f\tisReachHumid: %d\tisReachTemp: %d\n", humidity, temperature, isReachMaxHumid, isReachMaxTemp);
		}
	}
	else if (isnan(humidity_2) == false || isnan(temperature_2) == false) {
		if (isnan(humidity_3) == false || isnan(temperature_3) == false) {
			isSensorActive = true;
			humidity = (humidity_2 + humidity_3) / 2;
			temperature = (temperature_2 + temperature_3) / 2;
			Serial.printf("DHT_2_3:\thumid: %f\ttemp: %f\tisReachHumid: %d\tisReachTemp: %d\n", humidity, temperature, isReachMaxHumid, isReachMaxTemp);
		}
		else {
			isSensorActive = true;
			humidity = humidity_2;
			temperature = temperature_2;
			Serial.printf("DHT_2:\thumid: %f\ttemp: %f\tisReachHumid: %d\tisReachTemp: %d\n", humidity, temperature, isReachMaxHumid, isReachMaxTemp);
		}
	}
	else if (isnan(humidity_3) == false || isnan(temperature_3) == false) {
		isSensorActive = true;
		humidity = humidity_3;
		temperature = temperature_3;
		Serial.printf("DHT_3:\thumid: %f\ttemp: %f\tisReachHumid: %d\tisReachTemp: %d\n", humidity, temperature, isReachMaxHumid, isReachMaxTemp);
	}
	else {
		isSensorActive = false;
		Serial.println("Three sensors are not working properly.");
	}

	if (isSensorActive) {
		if (humidity >= MAX_HUMIDITY) {
			isReachMaxHumid = true;
		}
		else {
			isReachMaxHumid = false;
		}

		if (temperature >= MAX_TEMPERATURE) {
			isReachMaxTemp = true;
			HeaterState = LOW;
			HeatpumpState = LOW;
		}
		else {
			isReachMaxTemp = false;
			if (isHeaterRun) {
				HeaterState = HIGH;
				HeatpumpState = LOW;
			}
			else {
				HeatpumpState = HIGH;
				HeaterState = LOW;
			}
		}
	}
	else {
		isReachMaxHumid = false;
		HeaterState = LOW;
		HeatpumpState = LOW;
	}
}