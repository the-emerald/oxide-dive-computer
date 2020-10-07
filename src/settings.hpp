#pragma once

#include "libcapra_core_xtensa.h"

extern Gas getGas(uint8_t idx);
extern void setGas(const Gas *gas, uint8_t idx);

extern uint8_t getGFL(uint8_t idx);
extern void setGFL(uint8_t idx, uint8_t val);

extern uint8_t getGFH(uint8_t idx);
extern void setGFH(uint8_t idx, uint8_t val);

extern uint8_t getSelectedGas();
extern void setSelectedGas(uint8_t val);

extern uint8_t getSelectedGF();
extern void setSelectedGF(uint8_t val);

extern uint8_t getNDLAlarm();
extern void setNDLAlarm(uint8_t val);

void double_to_array(uint8_t array[8], double val);
void array_to_double(uint8_t array[8], double val);

enum ComputerMode {
    Surface,
    Underwater
};

extern ComputerMode computer_mode;

// The following section is useful for mockup purposes only.
extern void initialiseEEPROMOnce();
