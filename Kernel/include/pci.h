#include <naiveConsole.h>
#ifndef PCI_H_
#define PCI_H_

uint16_t pciConfigReadWord (uint8_t bus, uint8_t slot,uint8_t func, uint8_t offset);
uint16_t pciConfigWriteWord (uint8_t bus, uint8_t slot,uint8_t func, uint8_t offset, uint16_t data);
void checkDevice(uint8_t bus, uint8_t device, uint8_t function);
void enableMasterBit(uint8_t bus, uint8_t device, uint8_t function, uint8_t regist);

#endif /* PCI_H */
