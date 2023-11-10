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
  for (int i = 0; i < 4; i++) pinMode(buttons[i], INPUT_PULLUP); // 버튼 
  pinMode(pump_pin, OUTPUT); // 펌프 
	pinMode(LED_pin, OUTPUT); // LED
	
  // LCD 초기화
  lcd.init();
  lcd.backlight();

  // 최초 실행시에 기본화면 (온습도 표시)를 표시하기 위해 온습도를 읽고 초기화면 출력 함수를 호출
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  print_init();


}

void loop() {
  if (is_setting) {
		if (is_amount_setting) setting_for_amount();
  	else if (is_cycle_setting) setting_for_cycle();
	}	
  else {
	  check_for_setting(); // 설정 버튼 눌렸는지 검사
		read_DHT(); // 온습도 측정 후 출력까지
	  check_for_pump(); // 펌프 동작
	  calculate_level(); // 물탱크 수위 측정 후 알림까지  
  }
}
