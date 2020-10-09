#include "settings.hpp"
#include "EEPROM.h"

const int gfl_address[] = {0, 1};
const int gfh_address[] = {2, 3};
const int gas_o2_address[] = {4, 5, 6, 7, 8};
const int gas_he_address[] = {9, 10, 11, 12, 13};
const int selected_gas_address = 14;
const int selected_gf_address = 15;
const int ndl_alarm_address = 16;
const int salinity_address = 17;

Gas getGas(uint8_t idx) {
    uint8_t o2 = EEPROM.read(gas_o2_address[idx]);
    uint8_t he = EEPROM.read(gas_he_address[idx]);
    return Gas {
        o2, he, 100 - o2 - he
    };
}

void setGas(const Gas *gas, uint8_t idx) {
    EEPROM.write(gas_o2_address[idx], gas->o2);
    EEPROM.write(gas_he_address[idx], gas->he);
    EEPROM.commit();
}

uint8_t getGFL(uint8_t idx) {
    return EEPROM.read(gfl_address[idx]);
}

void setGFL(uint8_t idx, uint8_t val) {
    EEPROM.write(gfl_address[idx], val);
    EEPROM.commit();
}

uint8_t getGFH(uint8_t idx) {
    return EEPROM.read(gfh_address[idx]);
}

void setGFH(uint8_t idx, uint8_t val) {
    EEPROM.write(gfh_address[idx], val);
    EEPROM.commit();
}

uint8_t getSelectedGas() {
    return EEPROM.read(selected_gas_address);
}

void setSelectedGas(uint8_t val) {
    EEPROM.write(selected_gas_address, val);
    EEPROM.commit();
}

uint8_t getSelectedGF() {
    return EEPROM.read(selected_gf_address);
}

void setSelectedGF(uint8_t val) {
    EEPROM.write(selected_gf_address, val);
    EEPROM.commit();
}

uint8_t getNDLAlarm() {
    return EEPROM.read(ndl_alarm_address);
}

void setNDLAlarm(uint8_t val) {
    EEPROM.write(ndl_alarm_address, val);
    EEPROM.commit();
}

void double_to_array(uint8_t array[8], double val) {
    // TODO: Implement this
}

void array_to_double(uint8_t array[8], double val) {
    // TODO: Implement this
}

ComputerMode computer_mode = Surface;

Salinity getWaterSalinity() {
    return (Salinity) (EEPROM.read(salinity_address) + 1);
}

void setWaterSalinity(Salinity value) {
    EEPROM.write(salinity_address, ((uint8_t) value) - 1);
    EEPROM.commit();
}

// Initialises the EEPROM once. This makes sure sane values are set inside the EEPROM following
// a wipe. Afterwards, it toggles a flag so it will not overwrite user settings.
extern void initialiseEEPROMOnce() {
    if (EEPROM.read(255) == 1) {
        return;
    }
    // Set up gas
    Gas air = Gas { 21, 0, 79 };
    setSelectedGas(0);
    for (int i = 0; i < 5; i++) {
        setGas(&air, i);
    }

    setSelectedGF(0);
    // GF1
    setGFL(0, 99);
    setGFH(0, 99);

    // GF2
    setGFL(1, 99);
    setGFH(1, 99);

    // NDL alarm
    setNDLAlarm(5);

    // Salinity
    setWaterSalinity(Salinity::Fresh);

    EEPROM.write(255, 1);
}
