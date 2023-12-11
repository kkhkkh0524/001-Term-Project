// index 순서대로 1, 2, 3, 4번 버튼으로 사용한다.
const int buttons[] = {3, 4, 5, 6};

// 각 index에 해당하는 버튼들의 현재 상태를 저장한다.
int current_state[] = {HIGH, HIGH, HIGH, HIGH};

// 각 index에 해당하는 버튼들의 이전 상태를 저장한다.
int previous_state[] = {HIGH, HIGH, HIGH, HIGH}; 

// 아래 두 temp 값은 4번 버튼 (저장 버튼)이 눌러지기 전에 화면에 값을 표시하기 위한 용도로 사용한다.
int temp_for_cycle;
int temp_for_amount;

bool is_setting = false; // 설정 모드의 진입 여부, 기본값 false 
bool is_amount_setting = false; // 급수량 설정 모드의 진입 여부, 기본값 false 이며 설정 모드로 진입 시 true 로 같이 변경된다.
bool is_cycle_setting = false; // 급수주기 설정 모드의 진입 여부, 기본값 false 이며 급수량 설정모드에서 저장 버튼을 누를 시 true 로 같이 변경된다.
