#pragma once

const int BUTTON_CYCLE_PIN = 21;

enum Button {
    Cycle,
    Select
};

extern void updateCycleButtonState();
extern bool cycleButtonPressed();