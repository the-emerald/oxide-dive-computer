#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "display.hpp"
#include "logo.hpp"
#include "settings.hpp"

U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

const char* surfaceMenuTitle = "Menu";
const char* surfaceMenuSl = "Dive Settings\nSystem Settings\nSet Gas\nAbout\nDEBUG ComputerMode\nBack";

const char* underwaterMenuTitle = "Menu";
const char* underwaterMenuSl = "Switch Gas\nToggle GF\nSet GF\nSet Gas\nDEBUG ComputerMode\nBack";

const char* diveSettingsMenuTitle = "Dive Settings";
const char* diveSettingsMenuSl = "GF 1\nGF 2\nSalinity\nppO2 Alarm\nNDL Alarm\nBack"; 

const char* setGFMenuTitle = "Set GF";
const char* setGFMenuSl = "GF 1\nGF 2\nBack";

const char* systemSettingsMenuTitle = "System Settings";
const char* systemSettingsMenuSl = "Display\nBluetooth\nReset Tissues\nReset Settings\nBack";

const char* switchGasMenuTitle = "Switch gas";

const char* gasSurfaceMenuTitle = "Set Gas";
const char* gasSurfaceMenuSl = "Gas 1\nGas 2\nGas 3\nGas 4\nGas 5\nBack";  // 1..=5 is for gases

const char* waterSalinityMenuTitle = "Water Salinity";
const char* waterSalinityMenuSl = "Fresh\nEN13319\nSalt\nBack";

const char* ppO2AlarmMenuTitle = "ppO2 Alarm";
const char* ppO2AlarmMenuSl = "1.0\n1.1\n1.2\n1.3\n1.4\n1.5\n1.6\nOff\nBack";

const char* ndlAlarmMenuTitle = "NDL Alarm";
const char* ndlAlarmMenuSl = "On\nOff\nBack";

void drawScreen(DisplayState state) {
    u8g2.setFontRefHeightAll();
    switch (state) {
        case Screen1:
            drawScreen1();
            break;
        case Screen2:
            drawScreen2();
            break;
        case UnderwaterMenu:
            drawUnderwaterMenu();
            break;
        // case ToggleGF:
        //     drawToggleGF();
        //     break;
        case SetGF:
            drawSetGFMenu();
            break;
        case SwitchGas:
            drawSwitchGasMenu();
            break;
        case SetGasUnderwater:
            drawSetGasUnderwaterMenu();
            break;
        case SurfaceMenu:
            drawSurfaceMenu();
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
        case SetGasSurface:
            drawSetGasSurfaceMenu();
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

void drawSetGasUnderwaterMenu() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(gasSurfaceMenuTitle, 1, gasSurfaceMenuSl);

    current_state = fromSetGasUnderwaterMenu(menuReturn);
}

void drawSetGFMenu() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(setGFMenuTitle, 1, setGFMenuSl);

    current_state = fromSetGFMenu(menuReturn);
}

void drawUnderwaterMenu() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(underwaterMenuTitle, 1, underwaterMenuSl);

    current_state = fromUnderwaterMenu(menuReturn);
}

void drawSwitchGasMenu() {
    // Draw switch gas
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(switchGasMenuTitle, 1, gasSurfaceMenuSl);

    current_state = fromSwitchGasMenu(menuReturn);
}

void drawSwitchGasConfirmation(uint8_t selection) {
    selection -= 1; // Indexing
    u8g2.setFont(u8g2_font_profont22_mr);

    char id[5];
    sprintf(id, "%d", selection + 1);
    char confirmTitle[16] = "Switch ";
    strcat(confirmTitle, id);
    strcat(confirmTitle, "?\n");

    Gas gas = getGas(selection);
    char prettyGas[6] = "";
    populatePrettyGas(gas.o2, gas.he, prettyGas);

    if (u8g2.userInterfaceMessage(confirmTitle, prettyGas, "", "Ok\nCancel") == 1) {
        setSelectedGas(selection);
    }
}

void drawToggleGF() {
    // TODO: Do you want a confirmation?
}

void drawNDLAlarm() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(ndlAlarmMenuTitle, 1, ndlAlarmMenuSl);
    current_state = fromNDLAlarmMenu(menuReturn);
}

void drawNDLAlarmSelection() {
    u8g2.setFont(u8g2_font_profont22_mr);

    uint8_t show_alarm = getNDLAlarm();
    if (show_alarm == ~0) {
        show_alarm = 0;
    }

    u8g2.userInterfaceInputValue("Set NDL\nalarm:\n", "", &show_alarm, 1, 10, 2, " min");

    char alarm[16];
    sprintf(alarm, "%d", show_alarm);
    strcat(alarm, " min");
    
    if (u8g2.userInterfaceMessage("Confirm?", alarm, "", "Ok\nCancel") == 1) {
        setNDLAlarm(show_alarm);
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

void drawSetGasSurfaceMenu() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(gasSurfaceMenuTitle, 1, gasSurfaceMenuSl);

    current_state = fromSetGasSurfaceMenu(menuReturn);
}

void drawPPO2Alarm() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(ppO2AlarmMenuTitle, 1, ppO2AlarmMenuSl);

    current_state = fromPPO2AlarmMenu(menuReturn);
}

extern void drawGFSelection(uint8_t selection) {
    selection -= 1;
    u8g2.setFont(u8g2_font_profont22_mr);

    uint8_t show_gfl = getGFL(selection);
    uint8_t show_gfh = getGFH(selection);

    char id[5];
    sprintf(id, "%d", selection + 1);

    char title[16] = "Set GF ";
    strcat(title, id);
    strcat(title, "\n");

    u8g2.userInterfaceInputValue(title, "Lo: ", &show_gfl, 0, 100, 3, "");
    u8g2.userInterfaceInputValue(title, "Hi: ", &show_gfh, 0, 100, 3, "");

    char confirmTitle[16] = "Confirm ";
    strcat(confirmTitle, id);
    strcat(confirmTitle, "?\n");

    char gf[6] = "";
    populatePrettyGF(show_gfl, show_gfh, gf);

    if (u8g2.userInterfaceMessage(confirmTitle, gf, "", "Ok\nCancel") == 1) {
        // Update the GFs
        setGFL(selection, show_gfl);
        setGFH(selection, show_gfh);
    }
}

extern void drawGasSelection(uint8_t selection) {
    selection -= 1;
    u8g2.setFont(u8g2_font_profont22_mr);

    char id[5];
    sprintf(id, "%d", selection + 1);

    char title[16] = "Set gas ";
    strcat(title, id);
    strcat(title, "\n");

    Gas gas_to_edit = getGas(selection);

    uint8_t show_o2 = gas_to_edit.o2;
    uint8_t show_he = gas_to_edit.he;

    u8g2.userInterfaceInputValue(title, "O2: ", &show_o2, 0, 100, 3, "");

    u8g2.userInterfaceInputValue(title, "He: ", &show_he, 0, 100-show_o2, 3, "");

    char confirmTitle[16] = "Confirm ";
    strcat(confirmTitle, id);
    strcat(confirmTitle, "?\n");

    char prettyGas[6] = "";
    populatePrettyGas(show_o2, show_he, prettyGas);

    if (u8g2.userInterfaceMessage(confirmTitle, prettyGas, "", "Ok\nCancel") == 1) {
        Gas new_gas = Gas {
            show_o2, show_he, 100 - show_he - show_o2
        };
        setGas(&new_gas, selection);
    }
}

void drawAbout() {
    u8g2.drawXBMP(32, 5, LOGO_WIDTH, LOGO_HEIGHT, logo_bits);

    u8g2.setFont(u8g2_font_profont12_mr);
    u8g2.drawStr(10, 80, "Oxide Dive Computer");
    u8g2.drawStr(30, 95, "[Prototype]");
    u8g2.drawStr(20, 110, "Powered by Capra");
}

void drawSurfaceMenu() {
    u8g2.setFont(u8g2_font_7x13B_mr);
    uint8_t menuReturn = u8g2.userInterfaceSelectionList(surfaceMenuTitle, 1, surfaceMenuSl);

    current_state = fromSurfaceMenu(menuReturn);
}

void drawScreen2() {
    if (computer_mode == ComputerMode::Underwater) {
        drawTemperature();
        drawppO2();
        drawGF();
        drawBatteryVoltage();
    }
    else {
        drawTemperature();      // Same location as mode 1
        drawSalinityField();
        drawCNS();
        drawBatteryVoltage();   // Same location as mode 1
    }

    u8g2.drawVLine(62, 0, 87);
    u8g2.drawHLine(0, 41, 128);
    u8g2.drawHLine(0, 87, 128);

    drawTissuePressure();
}

void drawSalinityField() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 12, "Water");

    u8g2.setFont(u8g2_font_profont22_mf);
    u8g2.drawStr(70, 36, "FRESH");
}

void drawCNS() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 58, "CNS");

    u8g2.setFont(u8g2_font_inb16_mr);
    u8g2.drawStr(0, 82, "122%");
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

    uint8_t cur_gfl = getGFL(getSelectedGF());
    uint8_t cur_gfh = getGFH(getSelectedGF());

    char gf[6] = "";
    populatePrettyGF(cur_gfl, cur_gfh, gf);

    u8g2.setFont(u8g2_font_10x20_mn);
    u8g2.drawStr(0, 82, gf);
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

void drawScreen1() {
    if (computer_mode == ComputerMode::Underwater) {
        drawTime();
        drawNextStopDepth();

        drawDepth();
        drawRuntime();

        drawGas();
        drawTTS();
    }
    else {
        drawSI();
        drawNoFly();

        drawMBar();
        drawDesat();

        drawGas();      // Same location as mode 1
        drawGFSurface();

    }

    u8g2.drawVLine(62, 0, 128);
    u8g2.drawHLine(0, 41, 128);
    u8g2.drawHLine(0, 87, 128);
}

void drawGFSurface() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 104, "GF");

    uint8_t cur_gfl = getGFL(getSelectedGF());
    uint8_t cur_gfh = getGFH(getSelectedGF());

    char gf[6] = "";
    populatePrettyGF(cur_gfl, cur_gfh, gf);

    u8g2.setFont(u8g2_font_10x20_mn);
    u8g2.drawStr(70, 128, gf);
}

void drawSI() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 12, "SI");

    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(0, 36, "9d");
}

void drawNoFly() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 12, "No Fly");

    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(70, 36, "23h");
}

void drawMBar() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(0, 58, "mBar");

    u8g2.setFont(u8g2_font_inb16_mn);
    u8g2.drawStr(0, 82, "1015");
}

void drawDesat() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 58, "Desat");

    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(70, 82, "48h");
}

void drawTime() {
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

    Gas current_gas = getGas(getSelectedGas());

    char prettyGas[6] = "";
    populatePrettyGas(current_gas.o2, current_gas.he, prettyGas);

    u8g2.drawStr(0, 128, prettyGas);
}

void drawTTS() {
    u8g2.setFont(u8g2_font_9x15B_mr);
    u8g2.drawStr(70, 104, "TTS");

    u8g2.setFont(u8g2_font_inb21_mn);
    u8g2.drawStr(70, 128, "15");
}

void populatePrettyGas(uintptr_t o2, uintptr_t he, char output[6]) {
    char _o2[4];
    sprintf(_o2, "%d", o2);

    char _he[4];
    sprintf(_he, "%d", he);

    strcat(output, _o2);
    strcat(output, "/");
    strcat(output, _he);
}

void populatePrettyGF(uint8_t lo, uint8_t hi, char output[6]) {
    char _lo[4];
    sprintf(_lo, "%d", lo);

    char _hi[4];
    sprintf(_hi, "%d", hi);

    strcat(output, _lo);
    strcat(output, "/");
    strcat(output, _hi);
}