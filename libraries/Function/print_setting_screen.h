/// @brief 설정 모드에서 화면에 현재 설정 중인 값의 변화를 볼 수 있도록 임시 값을 화면에 출력하는 함수
void print_setting() {
  lcd.setCursor(0, 0);
  lcd.print("                              ");

  lcd.setCursor(0, 0);
  lcd.print("Amount : " + String(temp_for_amount) + " mL");

  lcd.setCursor(0, 1);
  lcd.print("                            ");

  lcd.setCursor(0, 1);
  lcd.print("Cycle : " + String(temp_for_cycle) + " hours");
}