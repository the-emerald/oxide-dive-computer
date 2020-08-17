#include "menu.hpp"
#include <cstdint>
#include "display.hpp"

DisplayState current_state = DiveScreen1;

DisplayState fromMenu(uint8_t selection) {
    switch (selection) {
        case 1:
            return DiveSettings;
        case 2:
            return SystemSettings;
        case 3:
            return Gas;
        case 4:
            return About;
        case 5:
            return DiveScreen1;
        default:
            return Menu;
    }
}

DisplayState fromDiveSettingsMenu(uint8_t selection) {
    switch (selection) {
        case 1:
            return GFL1;
        case 2:
            return GFL2;
        case 3:
            return WaterType;
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

DisplayState fromGasMenu(uint8_t selection) {
    switch (selection) {
        case 11:
            return Menu;
        default:
            drawGasSelection(selection);
            return Menu;
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