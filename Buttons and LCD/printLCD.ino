/*
각 모드에 해당하는 LCD 디스플레이를 출력하는 함수를 포함하는 파일입니다.

Requirements for setup() :

void setup() {
  lcd.init();
  lcd.backlight();
}

Printed screen example :
------------------
Amount : 120 mL
Cycle : 12 hours
------------------
*/

#include <Wire.h> 
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);


void print_setting_screen() {
  lcd.setCursor(0, 0);
  lcd.print("Amount : ");
  lcd.print(temp_for_amount);
  lcd.print(" mL");

  lcd.setCursor(0, 1);
  lcd.print("Cycle : ");
  lcd.print(temp_for_cycle);
  lcd.print(" hours");
}



