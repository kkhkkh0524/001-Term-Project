/*
이 작업은 우선순위가 가장 낮으므로 main 아무 곳에서 호출해도 무관하다.
Requirements for setup() :

void setup() {
    pinMode(LED_pin, OUTPUT);
}

*/

const int LED_pin = 30;
const int trig_pin = 1;
const int echo_pin = 2;
const int crit_level = 25; // 실제 물의 양을 조절해가며 물보충이 필요하다고 판단되는 수위에서 센서의 값으로 정한다.

HCSR04 hc(trig_pin, echo_pin); // initialisation class HCSR04 (trig pin , echo pin)



// 이 함수가 호출되는 주기를 millis()를 통해 적절하게 조정해야한다.
void calculate_level() {
    int distance = hc.dist(); 

    // 지정한 수위보다 더 낮으면 물보충이 필요함을 알린다.
    if (distance > crit_level) digitalWrite(LED_pin, HIGH); 
    else digitalWrite(LED_pin, LOW);
}
