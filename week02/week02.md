## 사물인터넷(아두이노 week 02)

미세먼지 센서를 이용하여 정보를 측정하고 InfluxDB에 데이터를 저장

- 변수설정
```
int Vo = A0;              // 센서 연결
int V_LED = 12;           // LED 연결

// 각 변수 설정
float Vo_value = 0;
float Voltage = 0;
float dustDensity = 0;
```

-- 초기 설정 (setup)
```
void setup() {
  Serial.begin(9600);      // 시리얼 통신 
  pinMode(V_LED, OUTPUT);  // LED 핀 설정
  pinMode(Vo, INPUT);      // 센서 핀 설정
}
```

-- loop 함수
```
void loop() {
  digitalWrite(V_LED, LOW);                  // LED를 LOW로
  delayMicroseconds(280);                    // 280 마이크로 초
  Vo_value = analogRead(Vo);                 // LED를 HIGH로
  delayMicroseconds(40);                     // 40 마이크로 초
  digitalWrite(V_LED, HIGH);                 // LED를 LOW로
  delayMicroseconds(9680);                   // 9680 마이크로 초

  Voltage = Vo_value * 5.0 / 1023.0;
  dustDensity = (Voltage - 0.5) / 0.005;     // 먼지 농도 계산

  // 각 정보 출력
  Serial.print("dust: ");
  Serial.println(dustDensity);

  delay(1000);                               // 1초 후 다시 실행
}
```
