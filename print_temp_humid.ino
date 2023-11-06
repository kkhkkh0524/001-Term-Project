#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int temperature;
int humidity;

void setup() {
	lcd.init();
	lcd.backlight();
}

void loop() {
	lcd.setCursor(0, 0);
	lcd.print("Temp: ");
	lcd.print(temperature);
	lcd.print("C");

	lcd.setCursor(0, 1);
	lcd.print("Humidity: ");
	lcd.print(humidity);
	lcd.print("%");
}
