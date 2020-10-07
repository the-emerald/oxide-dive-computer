#include "menu.hpp"
#include <cstdint>
#include "display.hpp"
#include "settings.hpp"

DisplayState current_state = Screen1;

DisplayState fromSetGFMenu(uint8_t selection) {
    switch (selection) {
        case 3:
            return UnderwaterMenu;
        default:
            drawGFLSelection(selection);
            return UnderwaterMenu;
    }
}


DisplayState fromUnderwaterMenu(uint8_t selection) {
    switch (selection) {
        case 1:
            return SwitchGas;
        case 2:
            // TODO: Toggle GF business logic
            return Screen1;
        case 3:
            return SetGF;
        case 4:
            return SetGasUnderwater;
        case 5:
            // TODO: Remove this when finished debugging
            if (computer_mode == ComputerMode::Underwater) {
                computer_mode = ComputerMode::Surface;
            }
            else {
                computer_mode = ComputerMode::Underwater;
            }
            return Screen1;
        case 6:
            return Screen1;
        default:
            return UnderwaterMenu;
    }
}

DisplayState fromSwitchGasMenu(uint8_t selection) {
    switch (selection) {
        case 6:
            return UnderwaterMenu;
        default:
            // TODO: Make it confirm choice?
            return Screen1;
    }
}

DisplayState fromSurfaceMenu(uint8_t selection) {
    switch (selection) {
        case 1:
            return DiveSettings;
        case 2:
            return SystemSettings;
        case 3:
            return SetGasSurface;
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
            return Screen1;
        case 6:
            return Screen1;
        default:
            return SurfaceMenu;
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
            return SurfaceMenu;
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
            return SurfaceMenu;
        default:
            return SurfaceMenu;
    }
}

DisplayState fromSetGasSurfaceMenu(uint8_t selection) {
    switch (selection) {
        case 6:
            return SurfaceMenu;
        default:
            drawGasSelection(selection);
            return SetGasSurface;
    }
}

DisplayState fromSetGasUnderwaterMenu(uint8_t selection) {
        switch (selection) {
        case 6:
            return UnderwaterMenu;
        default:
            drawGasSelection(selection);
            return Screen1;
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

DisplayState determineMenuTransition() {
    if (computer_mode == ComputerMode::Underwater) {
        return UnderwaterMenu;
    }
    return SurfaceMenu;
}

DisplayState nextDisplayState(DisplayState current_state, Button input) {
    switch (current_state) {
        case Screen1:
            switch (input) {
                case Cycle:
                    return Screen2;
                case Select:
                    return determineMenuTransition();
            }
        case Screen2:
            switch (input) {
                case Cycle:
                    return Screen1;
                case Select:
                    return determineMenuTransition();
            }
        case About:
            return SurfaceMenu;
        // Default: do not change any state
        default:
            return current_state;
    }
}

