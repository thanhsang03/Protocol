#include <Wire.h>

void setup() {
  Wire.begin();

}

void loop() {
  Wire.beginTransmission(0x55);
  Wire.write(0x0F);
  Wire.endTransmission();
  delay(100);

}
