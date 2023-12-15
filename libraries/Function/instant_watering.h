// 코드 동작 테스트 필요

int b_1 = buttons[1], b_2 = buttons[2];

int cc_state[2] = {0, 0};
int pp_state[2] = {0, 0};


int check(int pin) {
    return cc_state[pin] == LOW && pp_state[pin] == HIGH; 
}

void instant_watering() {
    cc_state[0] = digitalRead(b_1);
    cc_state[1] = digitalRead(b_2);

    // 버튼 2개가 동시에 눌려졌고, 현재 펌프가 동작하지 않는 경우 
    if (check(0) && check(1) && !is_active) {
      is_active = 1;

      pp_state[0] = cc_state[0];
      pp_state[1] = cc_state[1];

      delay(30);
    }
    else {
      pp_state[0] = cc_state[0];
      pp_state[1] = cc_state[1];
    }
}