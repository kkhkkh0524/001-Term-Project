/// @brief 급수 주기를 설정하는 함수이다. 2, 3번 버튼의 입력을 검사하며, 2, 3번 버튼의 입력이 확인되면 임시 값을 바꾸고 화면을 업데이트한다.
void setting_for_cycle() {

  // 가장 먼저 저장 버튼이 눌러졌는지 검사한다.
  check_for_save(); 
  
  // 2, 3번 버튼의 상태를 같이 읽는다.
  for (int i = 1; i < 3; i++) { 
    current_state[i] = digitalRead(buttons[i]);

    // 버튼이 눌러진 경우
    if (current_state[i] == LOW && previous_state[i] == HIGH) { 
      
      // 2번 버튼 (값 증가)
      if (i == 1) temp_for_cycle += 1;
      
      // 3번 버튼 (값 감소), 0보다 작거나 같은 값은 가질 수 없다.
      else if (i == 2 && (temp_for_cycle - 1) >= 1) temp_for_cycle -= 1; 
      
      print_setting();
      
      previous_state[i] = current_state[i];
      delay(30);
    } 
    else if (current_state[i] == HIGH) previous_state[i] = current_state[i];
  }
}

/// @brief 급수량을 설정하는 함수이다. 2, 3번 버튼의 입력을 검사하며, 2, 3번 버튼의 입력이 확인되면 임시 값을 바꾸고 화면을 업데이트한다.
void setting_for_amount() {

  // 가장 먼저 저장 버튼이 눌러졌는지 검사한다.
  check_for_save(); 
  
  // 2, 3번 버튼의 상태를 같이 읽는다.
  for (int i = 1; i < 3; i++) { 
    current_state[i] = digitalRead(buttons[i]);

    // 버튼이 눌러진 경우
    if (current_state[i] == LOW && previous_state[i] == HIGH) { 
      
      // 2번 버튼 (값 증가)
      if (i == 1) temp_for_amount += 20; 
      
      // 3번 버튼 (값 감소), 음수 값은 가질 수 없다.  
      else if (i == 2 && (temp_for_amount - 20) >= 0) temp_for_amount -= 20; 

      print_setting();

      previous_state[i] = current_state[i];
      delay(30);
    } 
    else if (current_state[i] == HIGH) previous_state[i] = current_state[i];
  }
}
