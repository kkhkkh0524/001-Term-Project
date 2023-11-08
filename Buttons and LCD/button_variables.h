const int buttons[] = {27, 29, 31, 33}; // 순서대로 1, 2, 3, 4번 버튼 

int current_state[] = {HIGH, HIGH, HIGH, HIGH};
int previous_state[] = {HIGH, HIGH, HIGH, HIGH}; 

// 아래 두 temp 값은 4번 버튼 (저장 버튼)이 눌러지기 전에 화면에 값을 표시하기 위한 용도로 사용
int temp_for_cycle;
int temp_for_amount;

bool is_setting = false; // 설정 모드의 진입 여부
bool is_amount_setting = false; // 급수량 설정 모드의 진입 여부
bool is_cycle_setting = false; // 급수주기 설정 모드의 진입 여부
