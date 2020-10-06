#include "menu.hpp"
#include <cstdint>
#include "display.hpp"
#include "settings.hpp"

DisplayState current_state = DiveScreen1;

DisplayState fromMenu(uint8_t selection) {
    switch (selection) {
        case 1:
            return DiveSettings;
        case 2:
            return SystemSettings;
        case 3:
            return SetGas;
        case 4:
            return About;
        case 5:
            // TODO: Remove this when finished debugging
            if (computer_mode == ComputerMode::Underwater) {
                computer_mode = ComputerMode::Surface;
            }
            else {
                computer_mode = ComputerMode::Underwater;
            }
            return DiveScreen1;
        case 6:
            return DiveScreen1;
        default:
            return Menu;
    }
}

DisplayState fromDiveSettingsMenu(uint8_t selection) {
    switch (selection) {
        case 1: case 2:
            drawGFLSelection(selection);
            return DiveSettings;
        case 3:
            return WaterSalinity;
        case 4:
            return PPO2Alarm;
        case 5:
            return NDLAlarm;
        case 6:
            return Menu;
        default:
            return DiveSettings;
    }
}

DisplayState fromSystemSettingsMenu(uint8_t selection) {
    switch (selection) {
        case 1:
            return Display;
        case 2:
            return Bluetooth;
        case 3:
            return ResetTissues;
        case 4:
            return ResetSettings;
        case 5:
            return Menu;
        default:
            return Menu;
    }
}

DisplayState fromSetGasMenu(uint8_t selection) {
    switch (selection) {
        case 6:
            return Menu;
        default:
            drawGasSelection(selection);
            return SetGas;
    }
}

DisplayState fromWaterSalinityMenu(uint8_t selection) {
    switch (selection) {
        case 4:
            return DiveSettings;
        default:
            // TODO: Write code to update salinity
            return DiveSettings;
    }
}

DisplayState fromPPO2AlarmMenu(uint8_t selection) {
    switch (selection) {
        case 8: case 9:
            return DiveSettings;
        default:
            // TODO: Add function for selecting ppO2
            return DiveSettings;
    }
}

DisplayState fromNDLAlarmMenu(uint8_t selection) {
    switch (selection) {
        case 1:
            drawNDLAlarmSelection();
            return DiveSettings;
        default:
            return DiveSettings;
    }
}

DisplayState nextDisplayState(DisplayState current_state, Button input) {
    switch (current_state) {
        case DiveScreen1:
            switch (input) {
                case Cycle:
                    return DiveScreen2;
                case Select:
                    return Menu;
            }
        case DiveScreen2:
            switch (input) {
                case Cycle:
                    return DiveScreen1;
                case Select:
                    return Menu;
            }
        case About:
            return Menu;
        // Default: do not change any state
        default:
            return current_state;
    }
}