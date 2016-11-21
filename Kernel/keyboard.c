#include <keyboard.h>
#include <lib.h> 
#include <naiveConsole.h>
char myBuffer[64];
static int current = 0;
static int octave = 4;
char buffer;
int keyFlag;
int pianoFlag;
int shiftFlag = 1;

char keyboard[58] = {0,0,'1','2','3','4','5','6','7','8','9','0','-','=','\b'/*Backspace*/,0,
'q','w','e','r','t','y','u','i','o','p','[',']','\n',
0/*Algo*/,'a','s','d','f','g','h','j','k','l',';','\'', 0 , 0 , 0 ,'\'','x','c','v','b','n','m',',','.','/',0,0,0,' '};

char shiftKeyboard[58] = {0,0,'!','@','#','$','%','^','&','*','(',')','_','+','\b'/*Backspace*/,0,
'Q','W','E','R','T','Y','U','I','O','P','{','}','\n',
0/*Algo*/,'A','S','D','F','G','H','J','K','L',':','\'',0,0,0,
'Z','X','C','V','B','N','M','<','>','?',0,0,0,' '};



void addToBuffer(char entry) {
	if(entry==2 && !pianoFlag){
		return;
	}
	buffer = entry;	
}

char gimmeBuff() {
	return buffer;
}

void keyEntry() {
	while(inb(0x64) & 1){
		int entry = inb(0x60);
		printKeys(entry);
		}
	}

void pianoEntry() {
	while(inb(0x64) & 1){
		int entry = inb(0x60);
		printKeys(entry);
		}
	}


void pianoMode(int character) {
	switch(character){  
	  case 'a'://DO
	   switch(4){
	   		case 1:
	   			playSound(32);
	   			break;
	   		case 2:
	   			playSound(65);
	   			break;
	   		case 3:
	   			playSound(130);
	   			break;
	   		case 4:
	   			playSound(261);
	   			break;
	   		case 5:
	   			playSound(523);
	   			break;
	   		case 6:
	   			playSound(1046);
	   			break;
	   }
	   break;
	  case 's'://RE
	   switch(4){
	   		case 1:
	   		playSound(36);
	   			break;
	   		case 2:
	   		playSound(73);
	   			break;
	   		case 3:
	   		playSound(146);
	   			break;
	   		case 4:
	   		playSound(293);
	   			break;
	   		case 5:
	   		playSound(587);
	   			break;
	   		case 6:
	   		playSound(1174);
	   			break;
	   }break;
	  case 'd'://MI
	   switch(4){
	   		case 1:
	   		playSound(41);
	   			break;
	   		case 2:
	   		playSound(82);
	   			break;
	   		case 3:
	   		playSound(164);
	   			break;
	   		case 4:
	   		playSound(329);
	   			break;
	   		case 5:
	   		playSound(659);
	   			break;
	   		case 6:
	   		playSound(1318);
	   			break;
	   		playSound(32);
	   			break;
	   }	   
	   break;
	  case 'f'://FA
	   switch(4){
	   		case 1:
	   			playSound(43);
	   			break;
	   		case 2:
	   			playSound(87);
	   			break;
	   		case 3:
	   			playSound(174);
	   			break;
	   		case 4:
	   			playSound(349);
	   			break;
	   		case 5:
	   			playSound(698);
	   			break;
	   		case 6:
	   			playSound(1369);
	   			break;
	   }
	   break;
	  case 'g'://SOL
	   switch(4){
	   		case 1:
	   			playSound(49);
	   			break;
	   		case 2:
	   			playSound(98);
	   			break;
	   		case 3:
	   			playSound(196);
	   			break;
	   		case 4:
	   			playSound(392);
	   			break;
	   		case 5:
	   			playSound(783);
	   			break;
	   		case 6:
	   			playSound(1567);
	   			break;
	   }
	   break;
	  case 'h'://LA
	   switch(4){
	   		case 1:
	   			playSound(55);
	   			break;
	   		case 2:
	   			playSound(110);
	   			break;
	   		case 3:
	   			playSound(220);
	   			break;
	   		case 4:
	   			playSound(440);
	   			break;
	   		case 5:
	   			playSound(880);
	   			break;
	   		case 6:
	   			playSound(1760);
	   			break;
	   }
	   break;
	  case 'j'://SI
	   switch(4){
	   		case 1:
	   			playSound(61);
	   			break;
	   		case 2:
	   			playSound(123);
	   			break;
	   		case 3:
	   			playSound(246);
	   			break;
	   		case 4:
	   			playSound(493);
	   			break;
	   		case 5:
	   			playSound(987);
	   			break;
	   		case 6:
	   			playSound(1975);
	   			break;
	   }
	   break;
	  case 'k':
	   octave++;
	   break;
	  case 'l':
	   octave--;
	   break;
	   case 'u':
	  	playSound(523);
	   	break;
	  case 'i':
	  	playSound(587);
	  	break;
	  case 'o':
	  	playSound(659);
	  	break;
	  case 'p':
	  	playSound(698);
	  	break;
	  case 'e':
	  	pianoFlag = 0;
	  	ncNewline();
	  	ncPrint("Chau piano");
	  	ncNewline();
	  default:
	  	noSound();
	  	break;
	}
}

void printKeys(int character) {
	if(character != 0x1C && character != 0x0E && character < 57 && character != 0x2A && shiftFlag == 1){ 
		ncPrintChar(keyboard[character]);
		addToBuffer(keyboard[character]);
		keyFlag = 0;
	} else if(character == 0x1C){
		ncNewline();
		   addToBuffer(keyboard[character]);
		   ncNewline();
		   keyFlag = 0;
	} else if(character == 0x0E && character < 58){
		   addToBuffer('\b');
		   moveBackCursor();
		   deleteCharacter();
		   keyFlag = 0;
	}else if(character == 0x2A){
		shiftFlag = 0;
	}else if(character == 0xAA){
		shiftFlag = 1;
	}
	else if(!shiftFlag && character < 58){
		ncPrintChar(shiftKeyboard[character]);
		addToBuffer(shiftKeyboard[character]);
		keyFlag = 0;
	}
	else{
		addToBuffer(2);
	}
}
