#pragma once

#include <U8g2lib.h>

extern U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2;

extern void drawMainScreen();

extern void drawNDL();
extern void drawNextStopDepth();
extern void drawDepth();
extern void drawRuntime();
extern void drawGas();
extern void drawTTS();