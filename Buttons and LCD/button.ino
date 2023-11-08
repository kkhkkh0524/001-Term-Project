/*
이 코드는 버튼 상호작용만을 고려하여 쓰인 코드이며, 실제 인터페이스와 상호작용하는 코드는 "main.ino" 입니다.

1번 버튼 (D27) : Enter value-setting mode  
2번 버튼 (D29) : Change target value +1 / +10
3번 버튼 (D31) : change target value -1 / -10
4번 버튼 (D33) : Save changed value 

아두이노 내부 풀업 저항을 사용하여 각 디지털 핀에 버튼이 눌러졌을 때 LOW 출력이 되도록 설정 
*/

const int buttons[] = {27, 29, 31, 33}; // 순서대로 1, 2, 3, 4번 버튼 

// 이 전역변수의 값은 펌프 제어 함수와 공유합니다.
int watering_cycle = 8;
int watering_amount = 100;

int current_state[] = {HIGH, HIGH, HIGH, HIGH};
int previous_state[] = {HIGH, HIGH, HIGH, HIGH}; 

// 아래 temp 값은 4번 버튼 (저장 버튼)이 눌러지기 전에 화면에 값을 표시하기 위한 용도로 사용
int temp_for_cycle;
int temp_for_amount;

bool is_setting = false; // 설정 모드의 진입 여부

bool is_amount_setting = false; // 급수량 설정 모드의 진입 여부
bool is_cycle_setting = false; // 급수주기 설정 모드의 진입 여부

void setup() {
  for (int i = 0; i < 4; i++) pinMode(buttons[i], INPUT_PULLUP);
}

/* 
1번 버튼이 눌러졌는지 검사한다. 이 함수는 기본 모드(온습도 표시 화면)일 때만 호출한다. 세팅 모드로 진입하면 이 함수는 호출되지 않는다.)
*/
void check_for_setting() {
  current_state[0] = digitalRead(buttons[0]);

  if (current_state[0] == LOW && previous_state[0] == HIGH) { // 버튼이 눌러지면

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

  check_for_save(); // 세팅 모드에서 저장 버튼이 눌려졌는지는 항상 검사해야한다. 
  
  for (int i = 1; i < 3; i++) { // for문을 이용하여 2번 3번 버튼의 상태를 같이 읽는다.
    current_state[i] = digitalRead(buttons[i]);

    if (current_state[i] == LOW && previous_state[i] == HIGH) { // 버튼이 눌러지면
      
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

/*
급수 주기를 조절하는 모드, 2번 버튼과 3번 버튼의 입력을 같이 검사하여 임시 급수주기 값을 바꾼다.
*/
void setting_for_cycle() {

  check_for_save(); // 세팅 모드에서 저장 버튼이 눌려졌는지는 항상 검사해야한다. 
  
  for (int i = 1; i < 3; i++) { // for문을 이용하여 2번 3번 버튼의 상태를 같이 읽는다.
    current_state[i] = digitalRead(buttons[i]);

    if (current_state[i] == LOW && previous_state[i] == HIGH) { // 버튼이 눌러지면
      
      if (i == 1) { // 2번 버튼 (값 증가) 
        temp_for_cycle += 1;
        
      } else if (i == 2) { // 3번 버튼 (값 감소)
        if (temp_for_cycle - 1 >= 1) temp_for_cycle -= 1; // 값이 음수로 갈 수 없도록 예외처리
      }

      previous_state[i] = current_state[i];
      delay(30);
      
    } else if (current_state[i] == HIGH) {
      previous_state[i] = current_state[i];
    }  
  }
}

/*
4번 버튼 (저장 버튼)이 눌러졌는지 검사한다. 버튼이 눌러지면 전역변수 temp_for_amount 또는 temp_for_cycle 에 저장된 값을 실제 동작에 관여하는
전역변수 watering_amount 또는 watering_cycle 에 저장한다.
*/
void check_for_save() {
  // print_setting_screen.ino 파일의 print_setting_screen()를 이 줄에서 호출하면 된다.
  
  current_state[3] = digitalRead(buttons[3]);

  if (current_state[3] == LOW && previous_state[3] == HIGH) { // 버튼이 눌러지면 

    // 급수량 세팅 모드에서 저장 버튼이 눌리면 임시값에 저장된 값을 실제값으로 바꾸고, 급수주기 세팅 모드로 들어간다.    
    if (is_amount_setting) {
      watering_amount = temp_for_amount;
      is_amount_setting = false;
      is_cycle_setting = true;
    }
  
    // 급수주기 세팅 모드에서 저장 버튼이 눌리면 임시값에 저장된 값을 실제값으로 바꾸고, 세팅 모드를 종료한다. 
    if (is_cycle_setting) {
      watering_cycle = temp_for_cycle;
      is_cycle_setting = false;
      is_setting = false;

      // 초기 화면 (온습도 표시) 을 표시하는 LCD를 출력하는 코드, print_init_screen.ino 참조 (이 코드는 무조건 작성해야 한다.)
      // print_init_screen();
    }

    previous_state[3] = current_state[3];
    delay(30);
    
    } else if (current_state[3] == HIGH) { 
      previous_state[3] = current_state[3];
    }
}

void loop() {

  // 세팅 모드가 아닐 때만 세팅 버튼의 입력을 검사할 수 있도록 처리 (급수량 또는 급수주기를 설정하고 있을 때는 설정 버튼이 비활성화된다.) 
  if (!is_setting) check_for_setting();
  else {
    
    // 두 세팅 모드가 동시에 동작할 수 없도록 처리
    if (is_amount_setting) setting_for_amount();
    else if (is_cycle_setting) setting_for_cycle();
  }
}
