#include <Wire.h>                // I2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h> 	 // LCD 출력을 위한 라이브러리
#include <DHT.h>                 // 온습도 센서를 위한 라이브러리
#include <HCSR04.h>							 // 초음파 센서를 위한 라이브러리 

// 아래 3개의 전처리기는 순서를 따릅니다. (오브젝트 및 변수 선언)
#include <button_variables.h> 	  // 버튼 입력과 관련된 변수
#include <print_init_screen.h> 	  // 온습도 값 출력을 위한 함수 
#include <print_setting_screen.h> // 세팅화면 출력을 위한 함수  

#include <alert.h>                // 물 보충 알림을 위한 함수 
#include <pump.h>                 // 펌프 작동을 위한 함수 
#include <check_function.h>       // 버튼 입력 확인을 위한 함수
#include <setting_function.h>     // 세팅값 입력을 위한 함수 

void setup() {
  for (int i = 0; i < 4; i++) pinMode(buttons[i], INPUT_PULLUP); // 입력으로 사용할 4개의 버튼은 내장 풀업 저항을 사용
  pinMode(pump_pin, OUTPUT); // 펌프를 제어할 MOSFET
	pinMode(LED_pin, OUTPUT);  // 물 보충 알림에 필요한 LED
	
  // LCD 초기화
  lcd.init();
  lcd.backlight();
}

void loop() {   
	
 	// 설정 모드인 경우
	if (is_setting) {
		if (is_amount_setting) setting_for_amount(); // 급수량을 설정하는 경우 
		else if (is_cycle_setting) setting_for_cycle(); // 급수 주기를 설정하는 경우
	} 
		
 	// 설정 모드가 아닌 경우
	else {
    read_DHT_immediate(); // 온습도 측정 및 화면에 출력 

	  check_for_setting();  // 설정 버튼이 눌렸는지 검사
    check_for_pump();     // 펌프 제어

	  calculate_level();    // 물탱크 수위 측정 및 알림 
  }
}
