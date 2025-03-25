#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int Vo = A0;
int V_LED = 12;

float Vo_value = 0;
float Voltage = 0;
float dustDensity = 0;

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight(); 
  lcd.print("Dust Sensor");
  delay(2000);
  lcd.clear();
  
  pinMode(V_LED, OUTPUT);
  pinMode(Vo, INPUT);
}

void loop() {
  digitalWrite(V_LED, LOW);
  delayMicroseconds(280);
  Vo_value = analogRead(Vo);
  delayMicroseconds(40);
  digitalWrite(V_LED, HIGH);
  delayMicroseconds(9680);

  Voltage = Vo_value * 5.0 / 1023.0;
  dustDensity = (Voltage - 0.5) / 0.005;

  lcd.setCursor(0, 1);
  lcd.print("Dust: ");
  lcd.print(dustDensity);

  delay(1000);
}
