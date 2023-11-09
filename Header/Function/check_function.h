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
    else if (is_cycle_setting) {
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
