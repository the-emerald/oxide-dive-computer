#pragma once

#include <U8g2lib.h>
#include "menu.hpp"

extern U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2;

extern void drawScreen(DisplayState state);

extern void drawScreen1();
extern void drawScreen2();
extern void drawUnderwaterMenu();
// extern void drawToggleGF();
extern void drawSwitchGasMenu();
extern void drawSetGFMenu();
extern void drawSetGasUnderwaterMenu();
extern void drawSurfaceMenu();
extern void drawSystemSettings();
extern void drawDiveSettings();
extern void drawSetGasSurfaceMenu();
extern void drawAbout();
extern void drawWaterSalinity();
extern void drawPPO2Alarm();
extern void drawNDLAlarm();

extern void drawSalinityField();
extern void drawCNS();
extern void drawSI();
extern void drawMBar();
extern void drawDesat();
extern void drawGFSurface();
extern void drawNoFly();

extern void drawGasSelection(uint8_t selection);
extern void drawGFLSelection(uint8_t selection);
extern void drawNDLAlarmSelection();

void drawTemperature();
void drawBatteryVoltage();
void drawppO2();
void drawGF();
void drawTissuePressure();

void drawTime();
void drawNextStopDepth();
void drawDepth();
void drawRuntime();
void drawGas();
void drawTTS();

void populatePrettyGas(uintptr_t o2, uintptr_t he, char output[6]);