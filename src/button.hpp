#pragma once

const int BUTTON_CYCLE_PIN = 21;
const int BUTTON_SELECT_PIN = 4;

enum Button {
    Cycle,
    Select
};

extern void updateCycleButtonState();
extern bool cycleButtonPressed();

extern void updateSelectButtonState();
extern bool selectButtonPressed();