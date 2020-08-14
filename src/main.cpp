#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

const int BUTTON_PIN = 21;
const int LED_PIN = 13;

// Draw a demo screen (that has no moving parts)
void drawMainScreen() {
  // NDL
  {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 12, "NDL");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(0, 36, "999");

  }

    // Next stop depth
  {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(75, 12, "Stop");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(75, 36, "99");
  }

  // Depth
  {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 58, "Depth");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(0, 82, "99");
  }

  // Runtime
  {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(65, 58, "Run");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(65, 82, "999");
  }


  // Gas
  {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 104, "Gas");

    u8g2.setFont(u8g2_font_10x20_mn);
    u8g2.drawStr(0, 128, "99/99");
  }

  // Time to surface
  {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(65, 104, "TTS");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(65, 128, "999");
  }

  u8g2.sendBuffer();

}

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