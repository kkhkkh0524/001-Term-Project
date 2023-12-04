/// @brief 1번 버튼 (설정 버튼)이 눌러졌는지 검사한다. 이 함수는 기본 모드(온습도 표시 화면)일 때만 호출되며 설정 모드로 진입하면 이 함수는 호출되지 않는다.
void check_for_setting() {
  current_state[0] = digitalRead(buttons[0]);

  // 버튼이 눌러진 경우
  if (current_state[0] == LOW && previous_state[0] == HIGH) { 
    temp_for_cycle = watering_cycle; 
    temp_for_amount = watering_amount; 

    is_setting = true;
    is_amount_setting = true;
    is_cycle_setting = false;

    print_setting();

    previous_state[0] = current_state[0];
    delay(30);
  } 
  else if (current_state[0] == HIGH) previous_state[0] = current_state[0];
}

/// @brief 4번 버튼 (저장 버튼)이 눌러졌는지 검사하며 입력이 확인되면 임시 값을 실제 값으로 바꾼다.
void check_for_save() {
  current_state[3] = digitalRead(buttons[3]);
	
  // 버튼이 눌러진 경우
  if (current_state[3] == LOW && previous_state[3] == HIGH) { 
		
    // 급수량 설정 모드에서 저장 버튼이 놀리면 임시값에 저장된 값을 실제값으로 바꾸고, 급수주기 설정 모드로 들어간다.    
    if (is_amount_setting) {
      watering_amount = temp_for_amount;
      is_amount_setting = false;
      is_cycle_setting = true;
    }
	
    // 급수주기 설정 모드에서 저장 버튼이 눌리면 임시값에 저장된 값을 실제값으로 바꾸고, 설정 모드를 종료한다. 
    else if (is_cycle_setting) {
      watering_cycle = temp_for_cycle;
      is_cycle_setting = false;
      is_setting = false;
    }

    previous_state[3] = current_state[3];
    delay(30);
  } 
  else if (current_state[3] == HIGH) previous_state[3] = current_state[3];  
}
