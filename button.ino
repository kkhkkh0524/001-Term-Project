/*
1번 버튼 (D27) : Setting 
2번 버튼 (D29) : +1 / +10
3번 버튼 (D31) : -1 / -10
4번 버튼 (D33) : Save setting 
*/

const int buttons[] = {27, 29, 31, 33};

int buttonStates[] = {HIGH, HIGH, HIGH, HIGH};
int lastButtonStates[] = {HIGH, HIGH, HIGH, HIGH};

bool isSetting = false;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void settingCheck() {
  buttonStates[0] = digitalRead(buttons[0]);

  if (buttonStates[0] == LOW && lastButtonStates[0] == HIGH) {
    isSetting = true;

    lastButtonStates[0] = buttonStates[0];
    delay(50);
    
    } else if (buttonStates[0] == HIGH) {
      lastButtonStates[0] = buttonStates[0];
  }
}

void loop() {
  settingCheck();

}
