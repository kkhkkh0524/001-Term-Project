/*
Mega 2560과 연결 시 SDA 핀은 디지털 20번, SCL 핀은 디지털 21번에 연결합니다.

Printed screen example :
-----------------------
Temp : 23 C
Humidity : 34 %
-----------------------
*/

#include <DHT_variables.h>

DHT dht(DHT_11_pin, DHT11); // 온습도 센서 객체 정의
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 객체 정의 

// 온도와 습도를 저장된 변수 (int temperature, humidity) 에서 불러와 LCD에 표시하는 함수
void print_init() {
	lcd.setCursor(0, 0); // setCursor(a, b) : 출력문자의 시작점을 a열 b행으로 설정
	lcd.print("Temp : ");
	lcd.print(temperature);
	lcd.print(" C");

	lcd.setCursor(0, 1);
	lcd.print("Humidity : ");
	lcd.print(humidity);
	lcd.print(" %");
}

// 설정한 주기에 따라서 센서에서 값을 읽고 변수에 저장만 하는 함수, 출력은 print_init()을 사용하여 화면에 출력한다.
void read_DHT() {
	DHT_current = millis();

	if (DHT_current - DHT_previous > read_interval) { // read_interval 주기로 센서 값 업데이트  
		
		DHT_previous = DHT_current;
		temperature = dht.readTemperature();
		humidity = dht.readHumidity();
	}
}

// 온습도 값을 즉시 읽고 화면에 출력하는 함수.
void read_DHT_immediate() {
	temperature = dht.readTemperature();
	humidity = dht.readHumidity();

	print_init();
}