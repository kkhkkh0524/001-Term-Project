/*
DHT-11 센서로 읽은 값을 LCD 디스플레이에 출력하는 예제 코드입니다. 이후 main 코드와 결합 시 적절한 수정이 필요합니다.
Mega 2560과 연결 시 SDA 핀은 디지털 20번, SCL 핀은 디지털 21번에 연결합니다.
*/

#include <Wire.h> 
#include "LiquidCrystal_I2C.h"
#include "DHT.h"
#define DHTTYPE DHT11

const int DHT_11_pin = 2;
DHT dht(DHT_11_pin, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

int temperature;
int humidity;

unsigned long DHT_current = 0;
unsigned long DHT_previous = 0;

const int read_interval = 1 * 60 * 1000; // 1분 마다 센서의 값을 읽고 LCD 업데이트 


void updateDisplay() {
	lcd.setCursor(0, 0);
	lcd.print("Temp: ");
	lcd.print(temperature);
	lcd.print("C");

	lcd.setCursor(0, 1);
	lcd.print("Humidity: ");
	lcd.print(humidity);
	lcd.print("%");
}


void setup() {
	lcd.init();
	lcd.backlight();
	DHT_previous = millis();
}

void loop() {
	// millis() 를 이용하여 센서로부터 값을 읽는 주기를 적절히 조정 필요
	DHT_current = millis();

	if (DHT_current - DHT_previous > read_interval) {
		DHT_previous = DHT_current;
		temperature = dht.readTemperature();
		humidity = dht.readHumidity();
		updateDisplay();
	}
}
