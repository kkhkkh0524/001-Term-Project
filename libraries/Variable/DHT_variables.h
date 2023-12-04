const int DHT_11_pin = 2; // 온습도센서가 연결된 핀 번호

// 실제 온습도 표시 화면을 출력하는데 쓰이는 변수
int temperature = 0;

// 실제 온습도 표시 화면을 출력하는데 쓰이는 변수
int humidity = 0;

unsigned long DHT_current = 0;
unsigned long DHT_previous = 0;

const int read_interval = 1 * 60 * 1000; // 1분 마다 센서의 값을 읽고 LCD 업데이트 
