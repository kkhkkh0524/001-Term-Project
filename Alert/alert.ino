/*
Requirements for setup() :

void setup() {
    pinMode(LED_pin, OUTPUT);
}

*/

#include <HCSR04.h>

const int LED_pin = 30;
const int trig_pin = 16;
const int echo_pin = 14;

HCSR04 hc(trig_pin, echo_pin); // initialisation class HCSR04 (trig pin , echo pin)

const int crit_level = 25; // 실제 물의 양을 조절해가며 물보충이 필요하다고 판단되는 수위에서 센서의 값으로 정한다.

void setup() {
    pinMode(LED_pin, OUTPUT);
}


// 이 함수가 호출되는 주기를 millis()를 통해 적절하게 조정해야한다.
void calculate_level() {
    int distance = hc.dist(); 

    // 지정한 수위보다 더 낮으면 물보충이 필요함을 알린다.
    if (distance > crit_level) digitalWrite(LED_pin, HIGH); 
    else digitalWrite(LED_pin, LOW);
}
