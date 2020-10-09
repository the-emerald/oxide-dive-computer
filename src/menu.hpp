#pragma once

#include "button.hpp"
#include <cstdint>

enum DisplayState {
    Screen1,
    Screen2,
    DiveScreenSurface,
    UnderwaterMenu,
        // ToggleGF, // No ToggleGF because business logic is handled directly by fromUWM
        SwitchGas,
            // No sub-menus here because they are handled differently
        SetGF,
        SetGasUnderwater,
            // No sub-menus here because they are handled differently
    SurfaceMenu,
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
        SetGasSurface,
            // No sub-menus here because they are handled differently
        About,
};

extern DisplayState current_state;

DisplayState fromUnderwaterMenu(uint8_t selection);

DisplayState fromSwitchGasMenu(uint8_t selection);

DisplayState fromSetGFMenu(uint8_t selection);

DisplayState fromSurfaceMenu(uint8_t selection);

DisplayState fromDiveSettingsMenu(uint8_t selection);

DisplayState fromSystemSettingsMenu(uint8_t selection);

DisplayState fromSetGasUnderwaterMenu(uint8_t selection);

DisplayState fromSetGasSurfaceMenu(uint8_t selection);

DisplayState fromWaterSalinityMenu(uint8_t selection);

DisplayState fromPPO2AlarmMenu(uint8_t selection);

DisplayState fromNDLAlarmMenu(uint8_t selection);

DisplayState nextDisplayState(DisplayState current_state, Button input);