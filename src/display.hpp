#pragma once

#include <U8g2lib.h>
#include "menu.hpp"

extern U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2;

extern void drawScreen(DisplayState state);

extern void drawDiveScreen1();
extern void drawDiveScreen2();
extern void drawMenu();
extern void drawSystemSettings();
extern void drawDiveSettings();
extern void drawGasMenu();
extern void drawAbout();

extern void drawGasSelection(uint8_t selection);

void drawTemperature();
void drawBatteryVoltage();
void drawppO2();
void drawGF();
void drawTissuePressure();

void drawNDL();
void drawNextStopDepth();
void drawDepth();
void drawRuntime();
void drawGas();
void drawTTS();