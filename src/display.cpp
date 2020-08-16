#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "display.hpp"

U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);


void drawScreen(DisplayState state) {
    switch (state) {
        case DiveScreen1:
            drawMainScreen();
            break;
        case DiveScreen2:
            // TODO
            break;
        // TODO: Fill in rest of cases
        default:
            break;
    }
}

void drawMainScreen() {
    u8g2.drawVLine(62, 0, 128);
    drawNDL();
    drawNextStopDepth();
    u8g2.drawHLine(0, 41, 128);
    drawDepth();
    drawRuntime();
    u8g2.drawHLine(0, 87, 128);
    drawGas();
    drawTTS();
    u8g2.sendBuffer();
}

void drawNDL() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 12, "Time");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(0, 36, "4");
}

void drawNextStopDepth() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 12, "Stop");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(70, 36, "6");
}

void drawDepth() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 58, "Depth");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(0, 82, "25");
}

void drawRuntime() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 58, "Run");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(70, 82, "42");
}

void drawGas() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 104, "Gas");

    u8g2.setFont(u8g2_font_10x20_mn);
    u8g2.drawStr(0, 128, "21/0");
}

void drawTTS() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 104, "TTS");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(70, 128, "15");
}