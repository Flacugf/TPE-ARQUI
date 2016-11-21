#include <stdint.h>
#ifndef VIDEO_H_
#define VIDEO_H_


void BgaWriteRegister(unsigned short, unsigned short);
unsigned short BgaReadRegister(unsigned short);
int BgaIsAvailable(void);
void BgaSetVideoMode(unsigned int, unsigned int ,unsigned int ,int ,int);
void BgaSetBank(unsigned short);
void SetVideoMode(void);

#endif