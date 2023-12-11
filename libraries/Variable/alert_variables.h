const int LED_pin = 10;
const int trig_pin = 12;
const int echo_pin = 13;

const unsigned long hr_interval = 1 * 60 * 1000; // 1분마다 수위 측정 

unsigned long hr_previous = 0;
unsigned long hr_current = 0;

unsigned long distance = 0;
