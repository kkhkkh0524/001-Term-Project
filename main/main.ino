#include <Wire.h>                
#include <LiquidCrystal_I2C.h> 	 
#include <DHT.h>            
#include <HCSR04.h>							

#include <button_variables.h> 	 
#include <print_init_screen.h> 	 
#include <print_setting_screen.h> 

#include <pump_variables.h>     
#include <alert.h>             
#include <pump.h>                
#include <check_function.h>      
#include <setting_function.h>     
#include <rem_function.h>
#include <instant_watering.h>

void setup() {
  for (int i = 0; i < 4; i++) pinMode(buttons[i], INPUT_PULLUP);
  pinMode(pump_pin, OUTPUT);
	pinMode(LED_pin, OUTPUT); 
	
  lcd.init();
  lcd.backlight();

  // 디버깅 환경 : 5초 주기로 1초 동안 펌프 작동
  // interval = 1000 * 5; 
  // pump_duration = 1000; 
}

void loop() {
  if (is_active) check_for_pump();

  else if (is_setting && is_amount_setting) setting_for_amount();
  else if (is_setting && is_cycle_setting) setting_for_cycle();

  else {
      instant_watering();
      check_for_remaining(); 
      read_DHT_immediate(); 
      check_for_setting();  
      check_for_pump();    
      // calculate_level();   
    }
}