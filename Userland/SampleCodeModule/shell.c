#include <stdint.h>


extern uint8_t bss;
extern uint8_t endOfBinary;

void shellConsole()	{
	//Clean BSS
	memset(&bss, 0, &endOfBinary - &bss);

	char keyBuffer[64];
	int funcion1=0;
	int funcion2;
	int funcion3;
	int funcion4;
	int funcion5;
	int funcion6;
	int funcion7;
	int funcion8;
	int message;
	help();

	while (1){
		print("");
		printInLine("$>  ");
		scanf(keyBuffer);
		funcion1 = strCompare(keyBuffer, "piano");
		funcion2 = strCompare(keyBuffer, "fortune");
		funcion3 = strCompare(keyBuffer, "-c");
		funcion4 = strCompare(keyBuffer, "help");
		funcion5 = strCompare(keyBuffer, "music");
		funcion6 = strCompare(keyBuffer, "badtime");
		funcion7 = strCompare(keyBuffer, "close");
		funcion8 = strCompare(keyBuffer, "video");
		message = checkIfMessage(keyBuffer);
		if(funcion1){
			pianoPiola();
		}
		else {
			if(funcion2){
				fortune();
			}
			else if(funcion3){
				changeTermColour();
			}
			else if(funcion7){
				close();
			}
			else if(funcion8){
				video();
			}
			else if(funcion4){
				help();
			}
			else if(funcion5){
				playSong1();
			}
			else if(funcion6){
				printSlow("What a beautyful day");
				printSlow("Sun shining, the birds are singing");
				printSlow("On days like this kids like you should...");
				for(int i=0; i<10; i++){
					changeTermColour();
				}
				playSong1();
				close();
			}
			else if(message){
				sendMessage(keyBuffer);
				//print("Es un mensaje");
			}
			else{
				print("No es un comando valido");
			}

		}
		
	}
}