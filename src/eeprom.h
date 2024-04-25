// EEPROMHandler.h
#ifndef EEPROM_H
#define EEPROM_H

#include <Arduino.h>
#include <Wire.h>

// 24C02C is a 2K bit Serial Electrically Erasable PROM with a voltage range of 4.5V to 5.5V. The device is organized as a single block of 256x8-bit memory with a 2-wire serial interface.
#define EEPROM_ADDRESS 0x50

void eepromWriteByte(uint8_t address, uint8_t data);
uint8_t eepromReadByte(uint8_t address);
void readAndPrintAllData();

#endif