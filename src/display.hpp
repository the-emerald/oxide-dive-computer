#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

extern void drawMainScreen();

extern void drawNDL();
extern void drawNextStopDepth();
extern void drawDepth();
extern void drawRuntime();
extern void drawGas();
extern void drawTTS();