#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
char *cpuVendor(char *result);
int strLength(char* msg);
uint8_t* getAddress(const char* buffer);
int hexToChar(char c);
int digits(long number, int radix);
int parseInt(char * buffer, long number, int radix);
void printMac(uint8_t * mac);

#endif