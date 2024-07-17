#include <Wire.h>

void setup() {
  Wire.begin(0x55);
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
}

void loop() {
  delay(100);

}

void receiveEvent(int howMany)
{
  while(1 < Wire.available())
  {
    char c = Wire.read();
    Serial.print(c);

  }
  char x = Wire.read();
  Serial.println(x);
}