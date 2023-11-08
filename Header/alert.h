/*
이 작업은 우선순위가 가장 낮으므로 main 아무 곳에서 호출해도 무관하다.
Requirements for setup() :

void setup() {
    pinMode(LED_pin, OUTPUT);
}

*/
#include <alert_variables.h>

HCSR04 hc(trig_pin, echo_pin); // initialisation class HCSR04 (trig pin , echo pin)

void calculate_level() {
    hr_current = millis();

    if (hr_current - hr_previous > hr_interval) {
        hr_previous = hr_current;

        int distance = hc.dist(); 

        // 지정한 수위보다 더 낮으면 물보충이 필요함을 알린다.
        if (distance > crit_level) digitalWrite(LED_pin, HIGH); 
        else digitalWrite(LED_pin, LOW);
        
    }
}
