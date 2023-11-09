// Mega 2560 1개로 모든 시스템을 제어할 때 쓰일 스케치

#include <Wire.h>                // I2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h> 	 // LCD 출력을 위한 라이브러리
#include <DHT.h>                 // 온습도 센서를 위한 라이브러리
#include <HCSR04.h>							 // 초음파 센서를 위한 라이브러리 

// 아래 3개의 전처리기는 ordered 입니다. (센서 및 LCD 오브젝트 중복선언 방지)
#include <button_variables.h> 	  // 버튼 입력과 관련된 변수
#include <print_init_screen.h> 	  // 온습도 값 출력을 위한 함수 
#include <print_setting_screen.h> // 세팅화면 출력을 위한 함수  

#include <alert.h>                // 물 보충 알림을 위한 함수 
#include <pump.h>                 // 펌프 작동을 위한 함수 
#include <check_function.h>       // 버튼 입력 확인을 위한 함수
#include <setting_function.h>     // 세팅값 입력을 위한 함수 

void setup() {
  // 버튼과 연결되는 핀을 내장 풀업 저항을 사용하도록 설정  
  for (int i = 0; i < 4; i++) pinMode(buttons[i], INPUT_PULLUP);

  // LCD 초기화
  lcd.init();
  lcd.backlight();

  // 최초 실행시에 기본화면 (온습도 표시)를 표시하기 위해 온습도를 읽고 초기화면 출력 함수를 호출
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  print_init();

  // 펌프와 LED를 제어할 핀 선택 
  pinMode(pump_pin, OUTPUT);
	pinMode(LED_pin, OUTPUT);
}


void loop() {
  // 세팅 모드가 아닐 때만 세팅 버튼의 입력을 검사할 수 있도록 처리 (급수량 또는 급수주기를 설정하고 있을 때는 1번 버튼으로 상호작용 불가) 
  if (!is_setting) {
	  check_for_setting();

		// 세팅 모드가 아닐 때만 주기를 갖고 동작하는 부품들을 제어하는 함수를 호출한다.
		read_DHT(); // 온습도 측정
	  check_for_pump(); // 펌프 동작
	  calculate_level(); // 물탱크 수위 측정 
  }
  else {
    // 두 세팅 모드가 동시에 동작할 수 없도록 처리
    if (is_amount_setting) setting_for_amount();
    else if (is_cycle_setting) setting_for_cycle();
  }
}
