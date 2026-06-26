#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C address (usually 0x27 ya 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// HC-SR04 pins
#define TRIG_PIN 9
#define ECHO_PIN 10

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Distance Meter");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
  
  Serial.begin(9600);
}

void loop() {
  float distance = measureDistance();
  
  lcd.setCursor(0, 0);
  lcd.print("Distance:       ");
  
  lcd.setCursor(0, 1);
  if (distance < 0 || distance > 400) {
    lcd.print("Out of Range!   ");
  } else {
    lcd.print(distance, 1);   // 1 decimal place
    lcd.print(" cm     ");
  }
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(300);  // 300ms refresh
}

float measureDistance() {
  // Trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Echo time measure karo
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  
  if (duration == 0) return -1;  // No echo
  
  // Distance formula: (duration * speed of sound) / 2
  float distance = (duration * 0.0343) / 2.0;
  return distance;
}