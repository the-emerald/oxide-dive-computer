#include "button.hpp"
#include <Arduino.h>

int cycleButtonState = 0;
int cycleLastButtonState = 0;

void updateCycleButtonState() {
    cycleLastButtonState = cycleButtonState;
}

bool cycleButtonPressed() {
    cycleButtonState = digitalRead(BUTTON_CYCLE_PIN);
    return (cycleButtonState != cycleLastButtonState) && (cycleButtonState == LOW);
}

int selectButtonState = 0;
int selectLastButtonState = 0;

void updateSelectButtonState() {
    selectLastButtonState = selectButtonState;
}

bool selectButtonPressed() {
    selectButtonState = digitalRead(BUTTON_SELECT_PIN);
    return (selectButtonState != selectLastButtonState) && (selectButtonState == LOW);
}