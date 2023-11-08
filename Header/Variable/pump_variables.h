const int pump_pin = 11; // MOSFET과 연결된 디지털 핀 번호
const int pass_time = 300; // 물이 펌프로부터 출수구까지 도달하는데 걸리는 시간, 해당값은 예측 값이며 실측 후 값 수정 필요 (ms)  

int watering_amount, watering_cycle; // 아래 변수를 정의하기 위해 자료형만 선언, 기본값 할당은 main.ino 컴파일 시 진행

int pump_duration = (watering_amount * 36.1) + pass_time; // 펌프 작동 지속시간 (ms)
unsigned long interval = watering_cycle * 3600 * 1000; // 펌프 작동 주기 (ms)

unsigned long previous = 0, pump_previous = 0;
unsigned long current, pump_current;

bool is_active = false;
