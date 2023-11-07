/*
디지털 핀 번호 값은 임시값
1번 버튼 (D27) : Setting 
2번 버튼 (D29) : +1 / +10
3번 버튼 (D31) : -1 / -10
4번 버튼 (D33) : Save setting 
*/

const int buttons[] = {27, 29, 31, 33};

bool isSetting = false;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {


if (isSetting) {
  // enable 2번
}


}
