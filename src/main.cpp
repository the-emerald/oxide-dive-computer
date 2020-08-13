#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

const int BUTTON_PIN = 21;
const int LED_PIN = 13;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  u8g2.begin();
}

void loop() {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);

    int button = digitalRead(BUTTON_PIN);

    if (button == LOW) { // Not sure why this is LOW
      u8g2.drawStr(0,24,"Button pressed");
      digitalWrite(LED_PIN, HIGH);
    }
    else {
      u8g2.drawStr(0,24,"Hello, world!");
    }

  } while ( u8g2.nextPage() );
}