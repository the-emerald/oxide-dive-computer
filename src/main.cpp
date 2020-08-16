#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#include "display.hpp"
#include "button.hpp"
#include "menu.hpp"

const int LED_PIN = 13;

void setup() {
  pinMode(BUTTON_CYCLE_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  u8g2.begin();
}

void loop() {
  int button = digitalRead(BUTTON_CYCLE_PIN);

  if (button == LOW) {
    // For now, just say button pressed
    u8g2.clearBuffer();
    drawDiveScreen2();

    digitalWrite(LED_PIN, HIGH);
  }
  else {
    // Draw a demo screen
    u8g2.clearBuffer();
    drawScreen(current_state);

    digitalWrite(LED_PIN, LOW);
  }
}