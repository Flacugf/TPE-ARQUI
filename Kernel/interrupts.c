#include <keyboard.h>
#include <naiveConsole.h>
#include <lib.h>
#include <video.h>
#include <rtl.h>


#define SYSTEM_CALL_READ 1
#define SYSTEM_CALL_WRITE 2
#define SYSTEM_CALL_WRITE_SLOW 3
#define SYSTEM_CALL_WRITE_INLINE 8
#define SYSTEM_CALL_PLAY_SOUND 42
#define SYSTEM_CALL_DEATH 4
#define SYSTEM_CALL_COLOUR 6
#define SYSTEM_CALL_PLAY_SONG 9
#define SYSTEM_CALL_VIDEO 10
#define SYSTEM_CALL_SEND 11

extern char* myBuffer;
extern int current;
extern keyFlag; 
extern pianoFlag;
static int timer = 0;
int flag = 1;
char c;

void waitAbeat(){
	timer=1;
	while(timer%8);
}

void waitATick(){
	timer=1;
	while(timer%3);
}

void waitNSeconds(int seconds){
	while(seconds){
		waitAbeat();
		seconds--;
	}
}
void playNSeconds(int note, int seconds) {
	while(seconds){
		if(!timer){
			seconds--;
		}
		pianoMode(note);
	}
	noSound();
}

	void int80HandlerC(char* userBuffer, int rax, int size) {
		char* aux = userBuffer;
		int i = 0;
		int enter = 0;
		switch(rax){
			case SYSTEM_CALL_READ:
				while(!enter && i < size){
					keyFlag = 1;	
					while(keyFlag);
					*userBuffer = gimmeBuff();	
					i++;
					if(*userBuffer == '\n'){
						enter++;
					}
				}
				break;
			case SYSTEM_CALL_WRITE:
				pointLastLine();
				for(i = 0; i < size; i++){
					ncPrintChar(*userBuffer);
					userBuffer++;
				}
				ncNextline();
				break;
			case SYSTEM_CALL_WRITE_INLINE:
				pointLastLine();
				for(i = 0; i < size; i++){
					ncPrintChar(*userBuffer);
					userBuffer++;
				}
				break;
			case SYSTEM_CALL_WRITE_SLOW:
				pointLastLine();
				int pitch = 220;
				for(i = 0; i < size; i++){
					ncPrintChar(*userBuffer);
					playSound(pitch);
					waitATick();
					noSound();
					waitATick();
					userBuffer++;
					pitch += 5;
				}
				ncNextline();
				break;
			case SYSTEM_CALL_PLAY_SOUND:
				pianoFlag = 1;
				while(pianoFlag){
					char a = gimmeBuff();
					while(keyFlag);
					pianoMode(a);
					noSound();
				} 
				break;
			case SYSTEM_CALL_COLOUR:
				changeColour();
				break;
			case SYSTEM_CALL_DEATH:
				ncClear();
				_cli();
				while(1){
					pointNLine(12);
					print("Puede apagar el sistema", 0x01);
					pointNLine(12);
					print("Puede apagar el sistema", 0x02);
					pointNLine(12);
					print("Puede apagar el sistema", 0x03);
					pointNLine(12);
					print("Puede apagar el sistema", 0x04);
					pointNLine(12);
					print("Puede apagar el sistema", 0x05);
					pointNLine(12);
					print("Puede apagar el sistema", 0x06);	
				}
				break;

			case SYSTEM_CALL_VIDEO:
			SetVideoMode();
			break;

			case SYSTEM_CALL_SEND:			
			ncPrint("");
			uint8_t* address = getAddress(userBuffer);
			sendMessage(userBuffer+18,address,size);
			break;

			case SYSTEM_CALL_PLAY_SONG:
				while((c=*userBuffer)!=0){
						pianoMode(c);
						waitAbeat();
						userBuffer++;
					}
					noSound();
				}

		}
		

	void keyboardHandlerC() {
		keyEntry();
	}

	void timerTickHandlerC(){
		timer++;
		if(timer/18){
			timer = 0;
		}
	}

	void networkHandlerC(){
		receiveMessage();
	}
