/*
각 모드에 해당하는 LCD 디스플레이를 출력하는 함수를 포함하는 파일입니다.

Requirements for setup() :

void setup() {
  lcd.init();
  lcd.backlight();
}

*/

#include <Wire.h> 
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void print_amount() {
  lcd.setCursor(0, 0);
  lcd.print("Amount :");
  lcd.print(temp_for_amount);
  lcd.print(" mL");
}

void print_amount() {
  lcd.setCursor(0, 0);
  lcd.print("Cycle :");
  lcd.print(temp_for_cycle);
  lcd.print(" hour");
}

