#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	lcd.begin();
	lcd.backlight();
	lcd.print("Hello, world!");
}

void loop()
{
  
}

출처: https://kgu0724.tistory.com/133 [병아리 개발자의 이야기:티스토리]
