int a1 = 2;
int a2 = 3;
int a3;

void setup() {
  Serial.begin(115200);
  Serial.println();

  sum(a1, a2, a3);
  Serial.println(a3);
}

void loop() {

}

void sum(int a, int b, int& c) {
  c = a + b;
}
