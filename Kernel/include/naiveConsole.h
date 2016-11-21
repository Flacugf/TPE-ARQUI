#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

void ncPrint(const char * string);
void ncPrintChar(char character);
void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear();
void print(char* msg, int colour);
void ncNextline();
static uint32_t uintToBase(uint64_t value, char* buffer, uint32_t base);
void mrResetti();
void pointNLine(int n);
void pointLastLine();
void ncPrintLastLine(char* string);
void swapLines(int lineToSwap, int destination);
int isEndOfScreen();
void scroll();
void moveBackCursor();
void deleteCharacter();



#endif