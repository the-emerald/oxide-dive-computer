#include "settings.hpp"

Gas gases[5] = {
    Gas {
        21, 0, 79
    },
    Gas {
        21, 0, 79
    },    
    Gas {
        21, 0, 79
    },    
    Gas {
        21, 0, 79
    },    
    Gas {
        21, 0, 79
    }
};

uint8_t gfls[2] = {100, 100};

uint8_t gfhs[2] = {100, 100};

uint8_t ndl_alarm = ~0;
uint8_t current_gas = 0;
uint8_t current_gf = 0;

ComputerMode computer_mode = Surface;