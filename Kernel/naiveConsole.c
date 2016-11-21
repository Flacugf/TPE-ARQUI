#include <naiveConsole.h>

#define START_OF_SCREEN ((char *)0xB8000)
#define HEIGHT (25)
#define WIDTH (80)
#define FULLSIZE (HEIGHT * WIDTH * 2)
#define LAST_SPACE ((char *)(START_OF_SCREEN+HEIGHT*WIDTH*2-2))
#define LAST_LINE ((char *)(START_OF_SCREEN + ((HEIGHT - 1) * WIDTH * 2)))
#define END_OF_SCREEN ((char *)(START_OF_SCREEN+HEIGHT*WIDTH*2))

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;
static const uint32_t endOfScreen = 80 * 25 * 2;
static int colour = 0;
/*Prints a msg with colour*/
void print(char* msg, int colour){
	int leng = strLength(msg);
	int i=0;
	int j=0;

	while(i < leng){
	currentVideo[0] = msg[i];
	currentVideo[1] = (char) colour;
	i++;
	currentVideo += 2;
	if(isEndOfScreen()){
			scroll();
		}
	}
}

void ncPrint(const char * string)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		ncPrintChar(string[i]);
}


void ncPrintChar(char character)
{
	*currentVideo = character;
	currentVideo += 2;
	if(isEndOfScreen()){
			scroll();
		}
	
}

void ncNewline()
{
	do
	{
		ncPrintChar(' ');
		if(isEndOfScreen()){
			scroll();
		}
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void ncNextline()
{
	do
	{
		currentVideo += 2;
		if(isEndOfScreen()){
			scroll();
		}
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void ncPrintDec(uint64_t value)
{
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value)
{
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value)
{
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    ncPrint(buffer);
}

void ncClear()
{
	int i;

	for (i = 0; i < height * width; i++)
		video[i * 2] = ' ';
	currentVideo = video;
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

void mrResetti(){
	currentVideo = (char*) 0xB8000;
}

void pointNLine(int n) {
	mrResetti();
	int i;
	for(i = 0 ;i < n ;i++){
		ncNextline();
	}
}

void pointLastLine(){
	currentVideo = LAST_LINE;
}

void ncPrintLastLine(char* string) {
	pointLastLine();
	ncPrint(string);
}

void swapLines(int lineToSwap, int destination) {
	char* line;
	pointNLine(lineToSwap);
	int i = 0;
	int j = 0;
	do
	{
		line[j] = currentVideo[i];
		i += 2;
		j++;
	}
	while(i < (width * 2) - 6);
	pointNLine(destination);
	ncPrint(line);
}

int isEndOfScreen(){
	if(currentVideo >= END_OF_SCREEN){
		return 1;
	}
	return 0;
}

void scroll()
{
	char * copy_from = (char *) (START_OF_SCREEN + WIDTH * 2);
	currentVideo = (char *)START_OF_SCREEN;

	do
	{
		*currentVideo = *copy_from;
		currentVideo += 2;
		copy_from += 2;
	}
	while ((uint64_t)copy_from != END_OF_SCREEN);

	currentVideo = (char *) (START_OF_SCREEN + (HEIGHT - 1) * WIDTH * 2);

	do
	{
		*currentVideo = 0;
		currentVideo += 2;
	}
	while(currentVideo != END_OF_SCREEN);

	currentVideo = (char *) (START_OF_SCREEN + (WIDTH * (HEIGHT - 1) * 2));
}

void moveBackCursor(){
	if(currentVideo-2 > START_OF_SCREEN && currentVideo != LAST_LINE+8){
		currentVideo = currentVideo - 2;	
	}
	
}

void deleteCharacter(){
	*currentVideo = 0;
	
}

void changeColour() {
	ncClear();
	colour++;
	if(colour > 7) {
		colour = 1;
	}

	for (int i = 0; i < height * width; i++) {
		print(" ", colour*16);
	}
	
}