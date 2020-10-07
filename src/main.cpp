#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#include "display.hpp"
#include "button.hpp"
#include "menu.hpp"
#include "libcapra_core_xtensa.h"
#include "EEPROM.h"
#include "settings.hpp"

const int LED_PIN = 13;

ZHL16 deco;
CDiveSegment current = CDiveSegment {
  SegmentType::NoDeco, 0, 0, 999*1000, -20, 10 // Dummy ascent/descent rates
};

Gas air = Gas {
  21, 0, 79
};

bool update = false;

void setup() {
  Serial.begin(115200);

  EEPROM.begin(256);
  setSelectedGas(0);
  setSelectedGF(0);
  setNDLAlarm(0);

  pinMode(BUTTON_CYCLE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);

  pinMode(LED_PIN, OUTPUT);
  initialise(&deco);
  
  
  u8g2.begin(BUTTON_SELECT_PIN, BUTTON_CYCLE_PIN, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);
}

void loop() {

  // if (initialise() == 42069) {
  //   digitalWrite(LED_PIN, HIGH);
  // }


  if (cycleButtonPressed()) {
    current_state = nextDisplayState(current_state, Cycle);
    Serial.print("Cycle button pressed");
    // tick_segment(&deco, &air, 30, 60);
    // Serial.print("Tick complete");
  }
  if (selectButtonPressed()) {
    current_state = nextDisplayState(current_state, Select);
    Serial.print("Select button pressed");
    // digitalWrite(LED_PIN, HIGH);
    // CDiveSegment result = get_next_stop(&deco, &air, -10, 20);
    // digitalWrite(LED_PIN, LOW);

    // u8g2.clearBuffer();
    // u8g2.setFont(u8g2_font_t0_15_mr);

    // char tissue[256];
    // sprintf(tissue, "%f", deco.tissue.p_t[0]);   
    // u8g2.drawStr(0, 20, tissue);

    // char depth[256];
    // sprintf(depth, "%zd m", result.start_depth);   
    // u8g2.drawStr(0, 50, depth);

    // char time[256];
    // sprintf(time, "%llu s", result.time/1000);
    // u8g2.drawStr(0, 100, time);

    // u8g2.sendBuffer();
  }


  u8g2.clearBuffer();
  drawScreen(current_state);

  updateCycleButtonState();
  updateSelectButtonState();
}