/*
DHT-11 센서로 읽은 값을 LCD 디스플레이에 출력하는 예제 코드입니다. 이후 main 코드와 결합 시 적절한 수정이 필요합니다.
Mega 2560과 연결 시 SDA 핀은 디지털 20번, SCL 핀은 디지털 21번에 연결합니다.

Printed init screen example :
-----------------------
Temp : 23 C
Humidity : 34 %
-----------------------
*/

const int DHT_11_pin = 2; // 온습도센서가 연결된 디지털 핀 번호

int temperature = 0;
int humidity = 0;

unsigned long DHT_current = 0;
unsigned long DHT_previous = 0;

const int read_interval = 1 * 60 * 1000; // 1분 마다 센서의 값을 읽고 LCD 업데이트 

// 온도와 습도를 저장된 변수에서 불러와 LCD에 표시하는 함수
void print_init() {
	lcd.setCursor(0, 0); // setCursor(a, b) : 출력문자의 시작점을 a열 b행으로 설정
	lcd.print("Temp : ");
	lcd.print(temperature);
	lcd.print(" C");

	lcd.setCursor(0, 1);
	lcd.print("Humidity : ");
	lcd.print(humidity);
	lcd.print(" %");
}

// 설정한 주기에 따라서 센서에서 값을 읽고 변수에 저장만 하는 함수 
void read_DHT() {
	DHT_current = millis();

	if (DHT_current - DHT_previous > read_interval) { // read_interval 주기로 센서 값 업데이트  
		
		DHT_previous = DHT_current;
		temperature = dht.readTemperature();
		humidity = dht.readHumidity();
	}
}
