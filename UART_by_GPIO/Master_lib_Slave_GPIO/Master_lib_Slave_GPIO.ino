// master lib, slave GPIO
void setup() {
  Serial.begin(9600);
  delay(100);

}

char x='a';
void loop() {
  Serial.print(x);
  x++;
  delay(1000);

}
