/*
이 코드는 개별 동작을 가정하고 쓰인 코드이므로 이후 main 코드와 결합 시 적절한 수정이 필요합니다. 
해당 코드를 사용하기 위해선 DHT11 라이브러리가 필요합니다.
*/

#include "DHT.h"
#define DHTTYPE DHT11

const int temp_humid_pin = 2;

DHT dht(temp_humid_pin, DHTTYPE);

void setup() {
}

void loop() {
  delay(2000);

  int h = dht.readHumidity(); // (단위 : %)
  int t = dht.readTemperature(); // (단위 : 섭씨)
}
