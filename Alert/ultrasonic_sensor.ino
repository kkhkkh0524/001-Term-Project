/*
이 코드는 개별 동작을 가정하고 쓰인 코드이므로 이후 main 코드와 결합 시 적절한 수정이 필요합니다. 
실제 남은 양을 계산하기 위해 실측값을 통한 추정이 필요합니다. 
*/

#include "HCSR04.h"

const int LED_pin = 30;

const int trig_pin = 16;
const int echo_pin = 14;
HCSR04 hc(trig_pin, echo_pin); // initialisation class HCSR04 (trig pin , echo pin)

void setup() {
    pinMode(LED_pin, OUTPUT);
}

void loop() {
    int distance = hc.dist(); 
    
    if (distance > ...) digitalWrite(LED_pin, HIGH); 
    else digitalWrite(LED_pin, LOW);
        
    delay(60); // 다른 시스템 동작을 위해 이후 millis()로 변경 필요  
}
