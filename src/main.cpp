#include <Arduino.h>
#define LED_PORT 13

void setup() {
  pinMode(LED_PORT, OUTPUT);
}

void loop() {
  digitalWrite(LED_PORT, HIGH);
  delay(1000);
  digitalWrite(LED_PORT, LOW);
  delay(1000);
}