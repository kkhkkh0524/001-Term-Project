/*
1번 버튼 (D27) : Enter value-setting mode  
2번 버튼 (D29) : Change target value +1 / +10
3번 버튼 (D31) : change target value -1 / -10
4번 버튼 (D33) : Save changed value 

아두이노 내부 풀업 저항을 사용하여 각 디지털 핀에 버튼이 눌러졌을 때 LOW 출력이 되도록 설정 
4번 버튼이 눌러지기 전까지 변경된 값은 실제로 적용되지 않음

1번 > 4번 : 급수량 변경값 저장 후 급수주기 변경 모드
1번 > 4번 > 4번: 급수주기 변경값 저장 후 온습도 표시 (기본 모드)
*/

const int buttons[] = {27, 29, 31, 33}; // 순서대로 1, 2, 3, 4번 버튼 

// default value
int watering_cycle = 8;
int watering_amount = 100;

int current_state[] = {HIGH, HIGH, HIGH, HIGH};
int previous_state[] = {HIGH, HIGH, HIGH, HIGH}; 

// 아래 temp 값은 4번이 눌러지기 전 (최종 저장) 전에 화면에 값을 표시하기 위한 용도로 사용
int temp_for_cycle;
int temp_for_amount;

bool is_setting = false; // 설정 모드의 진입 여부

bool is_amount_setting = false;
bool is_cycle_setting = false;

void setup() {
  for (int i = 0; i < 4; i++) pinMode(buttons[i], INPUT_PULLUP);
}

/* 
1번 버튼이 눌러졌는지 검사한다. 이 함수는 다른 버튼의 입력과 무관하게 상시 호출 가능
버튼이 눌러지면 4번이 눌러지기 이전의 모든 값들은 초기화되며 바로 급수량 설정 모드로 진입
*/
void check_for_setting() {
  current_state[0] = digitalRead(buttons[0]);

  if (current_state[0] == LOW && previous_state[0] == HIGH) {
    temp_for_cycle = watering_cycle; 
    temp_for_amount = watering_amount;

    is_setting = true;
    is_amount_setting = true;
    is_cycle_setting = false;

    previous_state[0] = current_state[0];
    delay(30);
    
    } else if (current_state[0] == HIGH) { 
      previous_state[0] = current_state[0];
    }
}

/*
급수량을 조절하는 모드, 2번 버튼과 3번 버튼의 입력을 같이 검사하여 임시 급수량 값을 바꾼다.
*/

void setting_for_amount() {
  for (int i = 1; i < 3; i++) { // for문을 이용하여 2번 3번 버튼의 상태를 같이 읽는다.
    current_state[i] = digitalRead(buttons[i]);

    if (current_state[i] == LOW && previous_state[i] == HIGH) {
      
      if (i == 1) { // 2번 버튼 (값 증가) 
        temp_for_amount += 20;
        
      } else if (i == 2) { // 3번 버튼 (값 감소)
        if (temp_for_amount - 20 >= 0) temp_for_amount -= 20; // 값이 음수로 갈 수 없도록 예외처리
      }

      previous_state[i] = current_state[i];
      delay(30);
      
    } else if (current_state[i] == HIGH) {
      previous_state[i] = current_state[i];
    }  
  }
}

void setting_for_cycle() {
  
}

void loop() {

  // 세팅 모드가 아닐때만 세팅 버튼의 입력을 검사할 수 있도록 처리 
  if (!is_setting) check_for_setting();
  else {
    
    // 두 세팅 모드가 동시에 동작할 수 없도록 처리
    if (is_amount_setting) setting_for_amount();
    else if (is_cycle_setting) setting_for_cycle();
  }
}
