/*
Requirements for setup() :

void setup() {
  lcd.init();
  lcd.backlight();
}

Requirements for header files :
<Wire.h>
<LiquidCrystal_I2C.h>

Printed screen example :
------------------
Amount : 120 mL
Cycle : 12 hours
------------------
*/

void print_setting() {
  lcd.setCursor(0, 0);
  lcd.print("Amount : ");
  lcd.print(temp_for_amount);
  lcd.print(" mL");

  lcd.setCursor(0, 1);
  lcd.print("Cycle : ");
  lcd.print(temp_for_cycle);
  lcd.print(" hours");
}



