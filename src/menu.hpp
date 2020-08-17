#pragma once

#include "button.hpp"
#include <cstdint>

enum DisplayState {
    DiveScreen1,
    DiveScreen2,
    DiveScreenSurface,
    Menu,
        DiveSettings,
            GFL1,
            GFL2,
            WaterType,
            PPO2Alarm,
            NDLAlarm,
        SystemSettings,
            Display,
            Bluetooth,
            ResetTissues,
            ResetSettings,
        Gas,
        About,
};

extern DisplayState current_state;

DisplayState fromMenu(uint8_t selection);

DisplayState fromDiveSettingsMenu(uint8_t selection);

DisplayState nextDisplayState(DisplayState current_state, Button input);