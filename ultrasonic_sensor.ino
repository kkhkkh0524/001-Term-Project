/*
실제 환경에서 출력값 테스트 필요
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
