#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "display.hpp"
#include "logo.hpp"
#include "settings.hpp"

U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

const char* menuTitle = "Menu";
const char* menuSl = "Dive Settings\nSystem Settings\nGas\nAbout\nBack";

const char* diveSettingsMenuTitle = "Dive Settings";
const char* diveSettingsMenuSl = "GF 1\nGF 2\nSalinity\nppO2 Alarm\nNDL Alarm\nBack";

const char* systemSettingsMenuTitle = "System Settings";
const char* systemSettingsMenuSl = "Display\nBluetooth\nReset Tissues\nReset Settings\nBack";

const char* gasMenuTitle = "Gas";
const char* gasMenuSl = "Gas 1\nGas 2\nGas 3\nGas 4\nGas 5\nGas 6\nGas 7\nGas 8\nGas 9\nGas 10\nBack";  // 1..=10 is for gases

const char* waterSalinityMenuTitle = "Water Salinity";
const char* waterSalinityMenuSl = "Fresh\nEN13319\nSalt\nBack";

const char* ppO2AlarmMenuTitle = "ppO2 Alarm";
const char* ppO2AlarmMenuSl = "1.0\n1.1\n1.2\n1.3\n1.4\n1.5\n1.6\nOff\nBack";

const char* ndlAlarmMenuTitle = "NDL Alarm";
const char* ndlAlarmMenuSl = "On\nOff\nBack";

void drawScreen(DisplayState state) {
    u8g2.setFontRefHeightAll();
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
        case DiveSettings:
            drawSystemSettings();
            break;
        case SystemSettings:
            drawDiveSettings();
            break;
        case WaterSalinity:
            drawWaterSalinity();
            break;
        case PPO2Alarm:
            drawPPO2Alarm();
            break;
        case NDLAlarm:
            drawNDLAlarm();
            break;
        case Gases:
            drawGasMenu();
            break;
        case About:
            drawAbout();
            break;
        // TODO: Fill in rest of cases
        default:
            break;
    }
    u8g2.sendBuffer();
}

void drawNDLAlarm() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(ndlAlarmMenuTitle, 1, ndlAlarmMenuSl);
    current_state = fromNDLAlarmMenu(menuReturn);
}

void drawNDLAlarmSelection() {
    u8g2.setFont(u8g2_font_profont22_mr);

    // TODO: Fix dummy NDL alarm values
    uint8_t show_alarm = ndl_alarm;

    u8g2.userInterfaceInputValue("Set NDL\nalarm:\n", "", &show_alarm, 1, 10, 2, " min");

    char alarm[16];
    sprintf(alarm, "%d", show_alarm);
    strcat(alarm, " min");
    
    if (u8g2.userInterfaceMessage("Confirm?", alarm, "", "Ok\nCancel") == 1) {
        ndl_alarm = show_alarm;
    }
}

void drawWaterSalinity() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(waterSalinityMenuTitle, 1, waterSalinityMenuSl);

    current_state = fromWaterSalinityMenu(menuReturn);
}

void drawDiveSettings() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(systemSettingsMenuTitle, 1, systemSettingsMenuSl);

    current_state = fromSystemSettingsMenu(menuReturn);
}

void drawSystemSettings() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(diveSettingsMenuTitle, 1, diveSettingsMenuSl);

    current_state = fromDiveSettingsMenu(menuReturn);
}

void drawGasMenu() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(gasMenuTitle, 1, gasMenuSl);

    current_state = fromGasMenu(menuReturn);
}

void drawPPO2Alarm() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(ppO2AlarmMenuTitle, 1, ppO2AlarmMenuSl);

    current_state = fromPPO2AlarmMenu(menuReturn);
}

extern void drawGFLSelection(uint8_t selection) {
    u8g2.setFont(u8g2_font_profont22_mr);

    uint8_t show_gfl = gfls[selection-1];
    uint8_t show_gfh = gfhs[selection-1];

    char id[5];
    sprintf(id, "%d", selection);

    char title[16] = "Set GF ";
    strcat(title, id);
    strcat(title, "\n");

    u8g2.userInterfaceInputValue(title, "Lo: ", &show_gfl, 0, 100, 3, "");
    u8g2.userInterfaceInputValue(title, "Hi: ", &show_gfh, 0, 100, 3, "");

    char confirmTitle[16] = "Confirm ";
    strcat(confirmTitle, id);
    strcat(confirmTitle, "?\n");

    // TODO: Refactor GF pretty-printing
    char gfl[4];
    sprintf(gfl, "%d", show_gfl);

    char gfh[4];
    sprintf(gfh, "%d", show_gfh);

    char gf[6] = "";
    strcat(gf, gfl);
    strcat(gf, "/");
    strcat(gf, gfh);

    if (u8g2.userInterfaceMessage(confirmTitle, gf, "", "Ok\nCancel") == 1) {
        // Update the GFs
        gfls[selection-1] = show_gfl;
        gfhs[selection-1] = show_gfh;
    }
}

extern void drawGasSelection(uint8_t selection) {
    u8g2.setFont(u8g2_font_profont22_mr);

    char id[5];
    sprintf(id, "%d", selection);

    char title[16] = "Set gas ";
    strcat(title, id);
    strcat(title, "\n");

    uint8_t show_o2 = gases[selection - 1].o2;
    uint8_t show_he = gases[selection - 1].he;

    u8g2.userInterfaceInputValue(title, "O2: ", &show_o2, 0, 100, 3, "");

    u8g2.userInterfaceInputValue(title, "He: ", &show_he, 0, 100-show_o2, 3, "");

    char confirmTitle[16] = "Confirm ";
    strcat(confirmTitle, id);
    strcat(confirmTitle, "?\n");

    // TODO: Refactor gas pretty-printing
    char o2[4];
    sprintf(o2, "%d", show_o2);

    char he[4];
    sprintf(he, "%d", show_he);

    char prettyGas[6] = "";
    strcat(prettyGas, o2);
    strcat(prettyGas, "/");
    strcat(prettyGas, he);

    if (u8g2.userInterfaceMessage(confirmTitle, prettyGas, "", "Ok\nCancel") == 1) {
        gases[selection-1] = Gas {
            show_o2, show_he, 100 - show_o2 - show_he
        };
    }
}

void drawAbout() {
    u8g2.drawXBMP(32, 5, LOGO_WIDTH, LOGO_HEIGHT, logo_bits);

    u8g2.setFont(u8g2_font_profont12_mr);
    u8g2.drawStr(10, 80, "Oxide Dive Computer");
    u8g2.drawStr(30, 95, "[Prototype]");
    u8g2.drawStr(20, 110, "Powered by Capra");
}

void drawMenu() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(menuTitle, 1, menuSl);

    current_state = fromMenu(menuReturn);
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

    char o2[4];
    sprintf(o2, "%d", gases[current_gas].o2);

    char he[4];
    sprintf(he, "%d", gases[current_gas].he);

    char prettyGas[6] = "";
    strcat(prettyGas, o2);
    strcat(prettyGas, "/");
    strcat(prettyGas, he);

    u8g2.drawStr(0, 128, prettyGas);
}

void drawTTS() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 104, "TTS");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(70, 128, "15");
}