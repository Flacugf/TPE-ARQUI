#include <stdint.h>


void outb(uint16_t port, uint8_t value);
void outd(uint16_t port, uint16_t value);
void outq(uint16_t port, uint32_t value);
uint8_t inb(uint16_t port);
uint8_t ind(uint16_t port);
uint8_t inq(uint16_t port);
void syscaller(uint16_t interrupt);
char getRax();

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

/*Calculates strings length*/
int strLength (char* msg) {
	int length = 0;
	while(*msg) {
	msg++;
	length++;
	}
	return length;
}

int hexToChar(char c){
	if ( c >= '0' && c <= '9' ){
		return c - '0';
	}else if ( c >= 'A' || c <= 'F'){
		return 10 + c - 'A';
	}else if ( c >= 'a' || c <= 'f') {
		return 10 + c - 'a';
	}else{
		return -1;
	}
}

uint8_t* getAddress(const char* buffer){
	uint8_t* aux = buffer;
	uint8_t address[6];
	for(int i=0;i<6;i++){
		address[i] = hexToChar(*buffer) * 0x10;
		buffer++;
		address[i] += hexToChar(*buffer);
		buffer++;
		buffer++;
	}
	return address;
}

void printMac(uint8_t * mac){
  int size;
  char aux[30];
  for ( int i = 0 ; i < 6 ; i++ ){
    size = parseInt(aux, mac[i], 16);
    if ( size == 1 ){
     ncPrint("0");
    }
    aux[size] = 0;
    ncPrint(aux);
    if ( i != 5 ){
      ncPrint(":");
    }
  }
}
int digits(long number, int radix){
    int ans = 0;
    if (number == 0)
        return 1;

    if ( number < 0 ){
        number *= -1;
        ans++;
    }

    while ( number != 0 ){
        number /= radix;
        ans++;
    }
    return ans;
}
int parseInt(char * buffer, long number, int radix){
    int size, i, aux, auxSize;


    size = digits(number, radix);
    auxSize = size;

    if ( number < 0 ){
        buffer[0] = '-';
        number *= -1;
        buffer++;
        auxSize--;
    }

    for(i = auxSize - 1; i >= 0 ; i-- ){
        aux = number % radix;
        if ( aux >= 10 && aux <= 37){
            buffer[i] = 'A'+(aux - 10);
        }else{
            buffer[i] = number % radix + '0';
        }
        number /= radix;
    }
    return size;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}
	

