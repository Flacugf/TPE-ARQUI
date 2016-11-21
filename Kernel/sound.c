#include <lib.h>


void playSound(uint32_t frequence) {
	uint32_t divisor;
	uint8_t tmp;
	divisor = 1193180 / frequence;
	outb(0x43, 0xb6);
	outb(0x42, (uint8_t) divisor);
	outb(0x42, (uint8_t) (divisor >> 8));
	tmp = inb(0x61);
	if(tmp != (tmp | 3)) {
		outb(0x61, (tmp | 3));
	}
}

void changeWavelenght() {
	outb(0x43, 0xB6);
}

void noSound() {
	uint8_t tmp = (inb(0x61) & 0xFC);
	outb(0x61, tmp);
}


void beepBoop(int frequence) {
	playSound(frequence);
	
}