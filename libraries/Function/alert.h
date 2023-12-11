#include <alert_variables.h>

const int crit_level = 25; // 실제 물의 양을 조절해가며 물보충이 필요하다고 판단되는 distance 값을 센서의 값으로 정한다.

HCSR04 hc(trig_pin, echo_pin); 

/// @brief 설정한 주기에 따라서 수위 값을 측정하며 임계 수위보다 낮으면 LED를 점등한다.
void calculate_level() {
    hr_current = millis();

    if (hr_current - hr_previous > hr_interval) {
        hr_previous = hr_current;

        distance = hc.dist(); 

        // 지정한 수위보다 더 낮으면 물보충이 필요함을 알린다.
        if (distance > crit_level) digitalWrite(LED_pin, HIGH); 
        else digitalWrite(LED_pin, LOW);
    }
}