const int DHT_11_pin = 2; // 온습도센서가 연결된 디지털 핀 번호
 
int temperature = 0;
int humidity = 0;

unsigned long DHT_current = 0;
unsigned long DHT_previous = 0;

const int read_interval = 1 * 60 * 1000; // 1분 마다 센서의 값을 읽고 LCD 업데이트 
