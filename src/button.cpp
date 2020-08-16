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