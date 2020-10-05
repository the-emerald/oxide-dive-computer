#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#include "display.hpp"
#include "button.hpp"
#include "menu.hpp"
#include "libcapra_core_xtensa.h"

const int LED_PIN = 13;

void setup() {
  pinMode(BUTTON_CYCLE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);

  pinMode(LED_PIN, OUTPUT);
  initialise();
  
  u8g2.begin(BUTTON_SELECT_PIN, BUTTON_CYCLE_PIN, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);
}

void loop() {

  if (cycleButtonPressed()) {
    current_state = nextDisplayState(current_state, Cycle);
  }
  if (selectButtonPressed()) {
    current_state = nextDisplayState(current_state, Select);
  }

  u8g2.clearBuffer();
  drawScreen(current_state);

  updateCycleButtonState();
  updateSelectButtonState();
}