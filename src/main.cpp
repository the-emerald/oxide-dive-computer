#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "display.hpp"

const int BUTTON_PIN = 21;
const int LED_PIN = 13;

U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  u8g2.begin();
}

void loop() {
  int button = digitalRead(BUTTON_PIN);

  if (button == LOW) {
    // For now, just say button pressed
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_t0_15b_mr);
    u8g2.drawStr(0, 24, "Button pressed");
    u8g2.sendBuffer();

    digitalWrite(LED_PIN, HIGH);
  }
  else {
    // Draw a demo screen
    u8g2.clearBuffer();
    drawMainScreen();

    digitalWrite(LED_PIN, LOW);
  }
}