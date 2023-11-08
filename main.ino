/*
하나 마이크로컨트롤러로 모든 시스템을 제어한다고 가정할 때 사용할 스케치입니다.
*/

#include <Wire.h>		             // I2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h> 	 // LCD 출력을 위한 라이브러리
#include <DHT.h> 		             // 온습도 센서를 위한 라이브러리

// 아래 3개의 전처리기는 ordered 입니다. (센서 및 LCD 오브젝트 중복선언 방지)
#include <button_variables.h> 	  // 버튼 입력과 관련된 변수
#include <print_init_screen.h> 	  // 온습도 값 출력을 위한 함수 
#include <print_setting_screen.h> // 세팅화면 출력을 위한 함수  
#include <pump.h>                 // 펌프 작동을 위한 함수 

// 아래 두 변수는 컴파일 시 최초로 초기화되는 값이며 별도의 값 세팅이 없을 경우 이 값을 기본값으로 사용하여 펌프가 작동됩니다.
int watering_cycle = 8;
int watering_amount = 100;

void setup() {
  // 버튼과 연결되는 핀을 내장 풀업 저항을 사용하도록 설정  
  for (int i = 0; i < 4; i++) pinMode(buttons[i], INPUT_PULLUP);

  // LCD 초기화
  lcd.init();
  lcd.backlight();

  // 최초 실행시 온습도를 읽고 초기화면에 출력
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  print_init();

  // 펌프를 제어할 핀 설정
  pinMode(pump_pin, OUTPUT);
}


// 1번 버튼이 눌러졌는지 검사한다. 이 함수는 기본 모드(온습도 표시 화면)일 때만 호출한다. 세팅 모드로 진입하면 이 함수는 호출되지 않는다.)
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

// 급수량을 조절하는 모드, 2번 버튼과 3번 버튼의 입력을 같이 검사하여 임시 급수량 값을 바꾼다.
void setting_for_amount() {
  check_for_save(); // 세팅 모드에서 저장 버튼이 눌려졌는지는 항상 검사해야한다. 
  
  for (int i = 1; i < 3; i++) { // for문을 이용하여 2번 3번 버튼의 상태를 같이 읽는다.
    current_state[i] = digitalRead(buttons[i]);

    if (current_state[i] == LOW && previous_state[i] == HIGH) { // 버튼이 눌러지면
      
      if (i == 1) { // 2번 버튼 (값 증가) 
        temp_for_amount += 20;
        
      } else if (i == 2) { // 3번 버튼 (값 감소)
        if (temp_for_amount - 20 >= 0) temp_for_amount -= 20; // 예외처리
      }

      previous_state[i] = current_state[i];
      delay(30);
      
    } else if (current_state[i] == HIGH) {
      previous_state[i] = current_state[i];
    }  
  }
}


// 급수 주기를 조절하는 모드, 2번 버튼과 3번 버튼의 입력을 같이 검사하여 임시 급수주기 값을 바꾼다.
void setting_for_cycle() {
  check_for_save(); // 세팅 모드에서 저장 버튼이 눌려졌는지는 항상 검사해야한다. 
  
  for (int i = 1; i < 3; i++) { // for문을 이용하여 2번 3번 버튼의 상태를 같이 읽는다.
    current_state[i] = digitalRead(buttons[i]);

    if (current_state[i] == LOW && previous_state[i] == HIGH) { // 버튼이 눌러지면
      
      if (i == 1) { // 2번 버튼 (값 증가) 
        temp_for_cycle += 1;
        
      } else if (i == 2) { // 3번 버튼 (값 감소)
        if (temp_for_cycle - 1 >= 1) temp_for_cycle -= 1; // 예외처리
      }

      previous_state[i] = current_state[i];
      delay(30);
      
    } else if (current_state[i] == HIGH) {
      previous_state[i] = current_state[i];
    }  
  }
}


// 4번 버튼 (저장 버튼)이 눌러졌는지 검사한다. 버튼이 눌러지면 전역변수 temp_for_amount 또는 temp_for_cycle 에 저장된 값을 실제 동작에 관여하는 전역변수 watering_amount 또는 watering_cycle 에 저장한다.
void check_for_save() {
	print_setting(); // check_for_save 는 세팅 과정에서 항상 호출되므로 실시간으로 현재 설정된 값을 볼 수 있도록 LCD를 출력한다. 
	
  current_state[3] = digitalRead(buttons[3]);
	
  if (current_state[3] == LOW && previous_state[3] == HIGH) { // 버튼이 눌러지면 

		
    // 급수량 세팅 모드에서 저장 버튼이 놀리면 임시값에 저장된 값을 실제값으로 바꾸고, 급수주기 세팅 모드로 들어간다.    
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

      print_init();
    }

    previous_state[3] = current_state[3];
    delay(30);
    
    } else if (current_state[3] == HIGH) { 
      previous_state[3] = current_state[3];
    }
}

void loop() {

  // 세팅 모드가 아닐 때만 세팅 버튼의 입력을 검사할 수 있도록 처리 (급수량 또는 급수주기를 설정하고 있을 때는 설정 버튼으로 상호작용 불가) 
  if (!is_setting) check_for_setting();
  else {
    // 두 세팅 모드가 동시에 동작할 수 없도록 처리
    if (is_amount_setting) setting_for_amount();
    else if (is_cycle_setting) setting_for_cycle();
  }

	// 펌프의 작동 이후 시간을 계산하여 주기에 맞게 펌프를 작동시키는 함수 
	check_for_pump();
}
