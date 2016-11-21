/*
 * interrupts.h
 *
 */
#include "./types.h"
#ifndef INTERRUPS_H_
#define INTERRUPS_H_


void _irq00Handler(void);
void _irq01Handler(void);
void _irq02Handler(void);
void _irq03Handler(void);
void _irq04Handler(void);
void _irq05Handler(void);

void _cli(void);

void _sti(void);

void picMasterMask(byte mask);

void picSlaveMask(byte mask);

void networkHandlerC();


//Termina la ejecución de la cpu.
void haltcpu(void);

#endif /* INTERRUPS_H_ */
