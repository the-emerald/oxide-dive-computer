#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "display.hpp"
#include "logo.hpp"

U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

const char* menuTitle = "Menu";
const char* menuSl = "Settings\nGases\nAbout\nBack";

const char* settingsMenuTitle = "Settings";
const char* settingsMenuSl = "GF 1\nGF 2\nBacklight\nBluetooth\nBack";


void drawScreen(DisplayState state) {
    switch (state) {
        case DiveScreen1:
            drawDiveScreen1();
            break;
        case DiveScreen2:
            drawDiveScreen2();
            break;
        case Menu:
            drawMenu();
            break;
        // Sub-menus
        case Settings:
            drawSettings();
            break;
        case Gas:
            drawGasMenu();
            break;
        case About:
            drawAbout();
            break;
        // TODO: Fill in rest of cases
        default:
            break;
    }
}

void drawSettings() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(settingsMenuTitle, 1, settingsMenuSl);

    current_state = fromSettingsMenu(menuReturn);
    u8g2.sendBuffer();
}

void drawGasMenu() {
    // TODO: Make gas menu
}

void drawAbout() {
    u8g2.drawXBMP(32, 5, LOGO_WIDTH, LOGO_HEIGHT, logo_bits);

    u8g2.setFont(u8g2_font_profont12_mr);
    u8g2.drawStr(10, 80, "Oxide Dive Computer");
    u8g2.drawStr(30, 95, "[Prototype]");
    u8g2.drawStr(20, 110, "Powered by Capra");

    u8g2.sendBuffer();
}

void drawMenu() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(menuTitle, 1, menuSl);

    current_state = fromMenu(menuReturn);
    u8g2.sendBuffer();
}

void drawDiveScreen2() {
    u8g2.drawVLine(62, 0, 87);

    drawTemperature();
    drawppO2();
    u8g2.drawHLine(0, 41, 128);

    drawGF();
    drawBatteryVoltage();
    u8g2.drawHLine(0, 87, 128);

    drawTissuePressure();

    u8g2.sendBuffer();
}

void drawTemperature() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 12, "Temp");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(0, 36, "18");
}

void drawppO2() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 12, "ppO2");

    u8g2.setFont(u8g2_font_10x20_mn);
    u8g2.drawStr(70, 36, "1.42");
}

void drawGF() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 58, "GF");

    u8g2.setFont(u8g2_font_10x20_mn);
    u8g2.drawStr(0, 82, "30/70");
}

void drawBatteryVoltage() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 58, "Batt");

    u8g2.setFont(u8g2_font_10x20_mn);
    u8g2.drawStr(70, 82, "3.7");
}

void drawTissuePressure() {
    // TODO: Draw tissue pressures
}

void drawDiveScreen1() {
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