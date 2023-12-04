/*
Printed screen example :
------------------
Amount : 120 mL
Cycle : 12 hours
------------------
*/


/// @brief 설정 모드에서 화면에 현재 설정 중인 값의 변화를 볼 수 있도록 임시 값을 화면에 출력하는 함수
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