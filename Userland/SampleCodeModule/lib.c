#include <lib.h>

#define DATA_MODULE_2_ADDRESS 0x500100


void write(char* str, int length);
void read(char* str, int length);
void colourSwap();
void playSong(char* strSong);
void writeSlow(char* str, int length);
void writeInLine(char*str, int length);
void send(int address, const char* str);

int strLength(char* str) {
	int length = 0;
	while(*str && str != '\n'){
		length++;
		str++;
	}
	return length;
}

int charCmp(char c1, char c2) {
	if(c1 - c2){
		return 0;
	}
	return 1;
}

void print(char* str) {
	int length = strLength(str);
	write(str, length);
}

void printInLine(char* str){
	int length = strLength(str);
	writeInLine(str,length);
}

void printSlow(char* str) {
	int length = strLength(str);
	writeSlow(str, length);
}

int scanf(char* str) {
	int length = 0;
	char c;
	char* aux =str;
	int goAway = 1;
	while(goAway) {
		c = getChar();
			if(c != 0 && c!= '\n') {
				if(c == '\b') {					
					if(aux<str){
						str--;
						*str = 0;
						length--;
					}
					
					}else{
						*str = c;
						str++;
						length++;
					}
				} else 
				{
					*str = 0;
					goAway = 0;
				}
			}
	return length;

}

void putChar(char c) {
	write(&c, 1);
}

char getChar() {
	char key;
	read(&key, 1);
	return key;
}

void pianoPiola(){
	playSound();
}

void fortune(){
	char c[64];
	print("Introduzca su fortuna");
	int length = scanf(c);
	if(length < 3) {
		print("Kept you waiting huh?");
	}
	else if (length <= 15){
		print("The cake is a lie");
	}
	else if (length == 16){
		print("Praise the Sun");
	} 
	else {
		print("Stay a while and listen");
	}
}

int strCompare(const char* str1, const char* str2) {
	int len1 = strLength(str1);
	int len2 = strLength(str2);
	if(len1 == len2) {
		for(int i = 0; i<len1 && i<len2; i++){
			if(!charCmp(*str1, *str2)){
				return 0;
			}
			str1++;
			str2++;
		}
		return 1;
	}
	return 0;
}

void changeTermColour(){
	colourSwap();
}

void close() {
	closeCpu();
}

void help(){
	print("piano: Prende el piano, a-j = Do-Si. e para salir");
	print("fortune: Escribi algo y recibi tu fortuna");
	print("-c: Cambia el color de la terminal, tienen un orden fijo");
	print("music: Leer una cancion desde un archivo");
	print("close: Cuelga la terminal y el SO");
	print("video: Inicia modo video e imprime un fractal");
	print("help: Re imprime estas instrucciones");
	print("badtime: ...");
	
}

void playSong1(){
	playSong((char*)DATA_MODULE_2_ADDRESS);
}

int checkIfMessage(const char* str){
	int i = 0;
	int flag = 1;
	for(; i<5 && flag;i++){
		if((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F')){
			str++;
		}else{
			flag = 0;
		}
		if((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F')){
			str++;
		}else{
			flag = 0;
		}
		if(!(*str == ':')){
			flag = 0;
		}
		str++;
	}
	if((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F')){
			str++;
		}else{
			flag = 0;
		}
		if((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F')){
			str++;
		}else{
			flag = 0;
		}
	return flag;

}

void sendMessage(const char* str){
	int length = strLength(str + 18);
	send(str,length);
}
