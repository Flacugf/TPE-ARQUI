#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
char *cpuVendor(char *result);
int strLength(char* msg);
void outd(uint16_t port, uint16_t value);
void outq(uint16_t port, uint32_t value);
uint8_t inb(uint16_t port);
uint8_t ind(uint16_t port);
uint8_t inq(uint16_t port);
char getRax();
void syscaller(uint16_t interrupt);
uint8_t* getAddress(const char* buffer);
int hexToChar(char c);

#endif