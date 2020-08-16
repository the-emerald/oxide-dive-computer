#pragma once

#include "button.hpp"
#include <cstdint>

enum DisplayState {
    DiveScreen1,
    DiveScreen2,
    DiveScreenSurface,
    Menu,
        Settings,
            GFL1,
            GFL2,
            Backlight,
            Bluetooth,
        Gas,
        About,
};

extern DisplayState current_state;

DisplayState fromMenu(uint8_t selection);

DisplayState fromSettingsMenu(uint8_t selection);

DisplayState nextDisplayState(DisplayState current_state, Button input);