/*
사용자 입력 인터페이스에서 적절한 값을 얻어서 watering_cycle, watering_amount에 사용하며, 설정된 값은 임시로 지정한 값입니다.

Requirements for setup() :

void setup() {
    pinMode(pump_pin, OUTPUT);
}
*/

// 아래 두 값은 버튼 입력에서 받아와서 사용해야한다.

// int watering_cycle = 12;  // 펌프 작동 주기 (hour)
// int watering_amount = 100; // 급수량 (mL) 

const int pump_pin = 11; // MOSFET과 연결된 디지털 핀 번호
const int pass_time = 300; // 물이 펌프로부터 출수구까지 도달하는데 걸리는 시간, 해당값은 예측 값이며 실측 후 값 수정 필요 (ms)  

int pump_duration = (watering_amount * 36.1) + pass_time; // 펌프 작동 지속시간 (ms)
unsigned long interval = watering_cycle * 3600 * 1000; // 펌프 작동 주기 (ms)

unsigned long previous = 0, pump_previous = 0;
unsigned long current, pump_current;

bool is_active = false;

void check_for_pump() { // 이 함수는 main에서 항상 호출이 되어야한다.
    current = millis();
    pump_current = millis();

    // 펌프가 작동될 때 작동 시간만큼 지나면 펌프를 끈다.
    if (is_active) {
        if (pump_current - pump_previous > pump_duration) {
            digitalWrite(pump_pin, LOW);
            is_active = false;
        }
    }

    // 작동 주기만큼 지나면 펌프를 작동시킨다.
    if (current - previous > interval) {
        previous = current;
        
        if (!is_active) {
            pump_previous = millis();
            digitalWrite(pump_pin, HIGH);
            is_active = true;
        } 
    }
}
