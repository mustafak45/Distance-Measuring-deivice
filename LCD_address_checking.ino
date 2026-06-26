#include <Wire.h>
void setup() {
  Wire.begin();
  Serial.begin(9600);
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C found at: 0x");
      Serial.println(addr, HEX);  // 0x27 ya 0x3F aayega
    }
  }
}
void loop() {}