/*
이 코드는 개별 동작을 가정하고 쓰인 코드이므로 이후 main 코드와 결합 시 적절한 수정이 필요합니다. 
실제 남은 양을 계산하기 위해 실측값을 통한 추정이 필요합니다. 
*/

#include <HCSR04.h>

const int trig_pin = 16;
const int echo_pin = 14;
HCSR04 hc(trig_pin, echo_pin); // initialisation class HCSR04 (trig pin , echo pin)

void setup() {
}

void loop()
{
    int distance = hc.dist(); 
    
    delay(60);                 // we suggest to use over 60ms measurement cycle, in order to prevent trigger signal to the echo signal.
}
