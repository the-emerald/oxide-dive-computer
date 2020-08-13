#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SH1107_SEEED_128X128_2_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

const int BUTTON_PIN = 21;
const int LED_PIN = 13;

// Draw a demo screen (that has no moving parts)
void drawMainScreen() {
  // NDL
  {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 12, "NDL");

    u8g2.setFont(u8g2_font_inr38_mn);
    u8g2.drawStr(0, 53, "999");

  }

  // Depth
  {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 70, "Depth");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(0, 95, "99");
  }

  // Next stop depth
  {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 70, "Stop");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(70, 95, "99");
  }


}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  u8g2.begin();
}

void loop() {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_15b_mr);

    int button = digitalRead(BUTTON_PIN);

    if (button == LOW) {
      // For now, just say button pressed
      u8g2.drawStr(0, 24, "Button pressed");
      digitalWrite(LED_PIN, HIGH);
    }
    else {
      // Draw a demo screen
      drawMainScreen();
      digitalWrite(LED_PIN, LOW);
    }

  } while ( u8g2.nextPage() );
}