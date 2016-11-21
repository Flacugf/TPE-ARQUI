#include <naiveConsole.h>
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

char gimmeBuff();
void keepTrackOfBuffer();
void keyEntry();
void printShiftKeys(int character);
void printKeys(int character);
void pianoMode(int character);

#endif /* KEYBOARD_H_ */
