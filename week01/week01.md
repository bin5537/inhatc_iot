## 사물인터넷(아두이노 week 01)

초음파 센서를 이용하여 LED를 켜거나 끄는 아두이노 코드


- 초음파 센서 핀 번호 설정
```
#define TRIG 13
#define ECHO 12
```

- LED 핀 번호 설정
```
int led_g = 7;
int led_r = 8;
```

- 초기 설정 (setup)
```
void setup() {
  Serial.begin(9600);      // 시리얼 통신 
  pinMode(led_g, OUTPUT);  // LED(초록색) 설정
  pinMode(led_r, OUTPUT);  // LED(빨간색) 설정
  pinMode(TRIG, OUTPUT);   // 초음파 송신 설정
  pinMode(ECHO, INPUT);    // 초음파 수신 설정
}
```

- loop 함수
```
void loop() {
  long duration, distance;            // 변수 선언

  
  digitalWrite(TRIG, LOW);            // TRIG를 LOW로 설정
  delayMicroseconds(2);               // 2마이크로 초 대기
  digitalWrite(TRIG, HIGH);           // TRIG를 HIGH로 설정
  delayMicroseconds(10);              // 10마이크로 초 대기
  digitalWrite(TRIG, LOW);            // TRIG를 LOW로 설정
  
  duration = pulseIn(ECHO, HIGH);
  distance = duration / 58.2;

  // 거리가 100 이상인 경우 빨간 LED ON/초록 LED OFF, 아닌경우 이 반대
  if (distance >= 100) {
    digitalWrite(led_r, HIGH);
    digitalWrite(led_g, LOW);
  } else {
    digitalWrite(led_r, LOW);
    digitalWrite(led_g, HIGH);
  }

  // 시간 및 거리를 시리얼모니터에 출력
  Serial.println(duration);
  Serial.print("\nDistance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(1000);    // 1초 후 다시 측
}
```
