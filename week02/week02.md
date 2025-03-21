## 사물인터넷(아두이노 week 02)

미세먼지 센서를 이용하여 정보를 측정하고 InfluxDB에 데이터를 저장

## 아두이노 코드

- 변수설정
```
int Vo = A0;              // 센서 연결
int V_LED = 12;           // LED 연결

// 각 변수 설정
float Vo_value = 0;
float Voltage = 0;
float dustDensity = 0;
```

- 초기 설정 (setup)
```
void setup() {
  Serial.begin(9600);      // 시리얼 통신 
  pinMode(V_LED, OUTPUT);  // LED 핀 설정
  pinMode(Vo, INPUT);      // 센서 핀 설정
}
```

- loop 함수
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


## 파이썬 코드

- 라이브러리 import
```
import serial
from influxdb_client import InfluxDBClient
import time
```

- 기본 값 설정
```
serial_port = 'COM5'
baud_rate = 9600
timeout = 2
```

- influxDB 설정
```
influxdb_url = "http://localhost:8086"      // 서버 주소
influxdb_token = ""    // 토큰
influxdb_org = "test"
influxdb_bucket = "dust"  // 버킷 이름

client = InfluxDBClient(url=influxdb_url, token=influxdb_token, org=influxdb_org)  # InfluxDB 클라이언트 초기화
write_api = client.write_api()
```

- 코드#1
```
try:
    // 연결 성공시 연결 성공 문자 출력
    ser = serial.Serial(serial_port, baud_rate, timeout=timeout)
    print(f"Connected to {serial_port} at {baud_rate} baud")
except serial.SerialException as e:
    // 연결 실패시 오류 메시지 출력 후 프로그램 종료
    print(f"Failed to connect to serial port: {e}")
    exit()
```

- 코드#2
```
try:
    // 반복
    while True:
        // 데이터가 존재하는지 확인
        if ser.in_waiting > 0:
            // 로드 후 문자열로 변환
            line = ser.readline().decode('utf-8').strip()

            // 아두이노 출력시 (Serial.print("dust: ");) 이런식으로 출력되므로 : 형식 확인
            if ":" in line:
                // : 를 중심으로 분리
                key, value = line.split(":")
                try:
                    // 값을 숫자로 변환(float) 후 데이터 저장 형식을 지정하고 데이터를 influxDB에 저장
                    value = float(value)
                    data = f"sensor_data,device=arduino {key}={value}"
                    write_api.write(bucket=influxdb_bucket, record=data)
                    print(f"Data written to InfluxDB: {key}={value}")
                // 실패시 지정된 문자 출력
                except ValueError:
                    print("Invalid data format")

        // 1초 후 다시 실행
        time.sleep(1)
```

- 코드#3
```
except KeyboardInterrupt:
    print("프로그램이 종료되었습니다.")
finally:
    // 시리얼 포트 닫기
    ser.close()
```
