void setup() {
  Serial.begin(9600);
  Serial.println("123456...");
  delay(500);

}

void loop() {
  if(Serial.available()){
    Serial.println(String((char)Serial.read()));
    
  }

}
