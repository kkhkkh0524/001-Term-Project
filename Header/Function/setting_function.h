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
