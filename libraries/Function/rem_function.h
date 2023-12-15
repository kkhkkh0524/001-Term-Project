int b_pin = buttons[3];
int c_state = 0, p_state = 0;

/// @brief 다음 펌프 작동까지 남은 시간을 LCD에 표시한다.
void print_remaining() {
    lcd.setCursor(0, 0);
    lcd.print("Time remaining");

    lcd.setCursor(0, 1);

    current = millis();
    pump_current = millis();
    unsigned long rem = (interval / 1000) -  ((current - previous) / 1000);

    unsigned long rem_h = rem / 3600;
    unsigned long rem_m = (rem % 3600) / 60;
    unsigned long rem_s = (rem % 3600) % 60;

    lcd.print(String(rem_h) + "h " + String(rem_m) + "m " + String(rem_s) + "s");
}

void init_screen() {
    lcd.setCursor(0, 0);
    lcd.print("                            ");
        
    lcd.setCursor(0, 1);
    lcd.print("                            ");
}

/// @brief 평상 시 저장 버튼을 누르고 있는 동안 다음 펌프 작동까지 남은 시간을 LCD에 표시한다.
void check_for_remaining() {
    c_state = digitalRead(b_pin);

    if (c_state == LOW && p_state == HIGH) {
        init_screen();
        
        while (digitalRead(b_pin) == LOW) print_remaining();
        
        init_screen();

        p_state = c_state;
        delay(30);
    }

    else if (c_state == HIGH) {
        p_state = c_state;
    }
}

