#define TRIG 13
#define ECHO 12

int led_g = 7;
int led_r = 8;

void setup() {
  Serial.begin(9600);
  pinMode(led_g, OUTPUT);
  pinMode(led_r, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  long duration, distance;
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  duration = pulseIn(ECHO, HIGH);
  distance = duration / 58.2;
  
  if (distance >= 100) {
    digitalWrite(led_r, HIGH);
    digitalWrite(led_g, LOW);
  } else {
    digitalWrite(led_r, LOW);
    digitalWrite(led_g, HIGH);
  }
  
  Serial.println(duration);
  Serial.print("\nDistance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(1000);
}
