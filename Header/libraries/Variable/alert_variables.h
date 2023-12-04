const int LED_pin = 30;
const int trig_pin = 1;
const int echo_pin = 2;

const int hr_interval = 1 * 60 * 1000; // 1분마다 수위 측정 

unsigned long hr_previous = 0;
unsigned long hr_current = 0;

int distance = 0;
