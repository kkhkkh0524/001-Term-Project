/*
Requirements for setup() :

void setup() {
    pinMode(pump_pin, OUTPUT);
}
*/

#include <pump_variables.h> // 펌프 작동 관련 변수 

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
