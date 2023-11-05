const int Pump_Pin = 6;
 
void setup(){
    pinMode(Pump_Pin, OUTPUT);
}
 
void loop(){
    // 5초 간격으로 펌프 작동/정지 반복
    analogWrite(Pump_Pin, 0);
    delay(5000); 
    analogWrite(Pump_Pin, 255);
    delay(5000); 
}
