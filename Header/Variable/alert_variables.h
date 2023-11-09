const int LED_pin = 30;
const int trig_pin = 1;
const int echo_pin = 2;

const int crit_level = 25; // 실제 물의 양을 조절해가며 물보충이 필요하다고 판단되는 수위에서 센서의 값으로 정한다.
const int hr_interval = 1 * 60 * 1000; // 1분마다 수위 측정 

unsigned long hr_previous = 0;
unsigned long hr_current = 0;

int distance = 0;
