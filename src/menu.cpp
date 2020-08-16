#include "menu.hpp"
#include <cstdint>

DisplayState current_state = DiveScreen1;

DisplayState fromMenu(uint8_t selection) {
    switch (selection) {
        case 1:
            return Settings;
        case 2:
            return Gas;
        case 3:
            return About;
        case 4:
            return DiveScreen1;
        default:
            return Menu;
    }
}

DisplayState fromSettingsMenu(uint8_t selection) {
    // TODO: Replace this
    return Menu;
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
        // TODO: Remove this when Menu selection functionality is implemented
        case Menu:
            return DiveScreen1;
        default:
            return current_state;
    }
}