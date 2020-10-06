#pragma once

#include "button.hpp"
#include <cstdint>

enum DisplayState {
    DiveScreen1,
    DiveScreen2,
    DiveScreenSurface,
    Menu,
        DiveSettings,
            GF,
            WaterSalinity,
            PPO2Alarm,
            NDLAlarm,
        SystemSettings,
            Display,
            Bluetooth,
            ResetTissues,
            ResetSettings,
        SetGas,
            // No sub-menus here because they are handled differently
        About,
};

extern DisplayState current_state;

DisplayState fromMenu(uint8_t selection);

DisplayState fromDiveSettingsMenu(uint8_t selection);

DisplayState fromSystemSettingsMenu(uint8_t selection);

DisplayState fromSetGasMenu(uint8_t selection);

DisplayState fromWaterSalinityMenu(uint8_t selection);

DisplayState fromPPO2AlarmMenu(uint8_t selection);

DisplayState fromNDLAlarmMenu(uint8_t selection);

DisplayState nextDisplayState(DisplayState current_state, Button input);