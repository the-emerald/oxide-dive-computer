#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "display.hpp"

U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void drawMainScreen() {
    drawNDL();
    drawNextStopDepth();
    drawDepth();
    drawRuntime();
    drawGas();
    drawTTS();

    u8g2.sendBuffer();
}

void drawNDL() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 12, "NDL");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(0, 36, "999");
}

void drawNextStopDepth() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(75, 12, "Stop");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(75, 36, "99");
}

void drawDepth() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 58, "Depth");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(0, 82, "99");
}

void drawRuntime() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(65, 58, "Run");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(65, 82, "999");
}

void drawGas() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 104, "Gas");

    u8g2.setFont(u8g2_font_10x20_mn);
    u8g2.drawStr(0, 128, "99/99");
}

void drawTTS() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(65, 104, "TTS");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(65, 128, "999");
}