#include "menu.hpp"
#include <cstdint>

DisplayState current_state = DiveScreen1;

DisplayState fromMenu(uint8_t selection) {
    return DiveScreen1; // TODO: Remove this placeholder
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