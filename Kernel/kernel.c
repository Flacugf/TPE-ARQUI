#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <keyboard.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interrupts.h>
#include <types.h>
extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;
int octave = 4;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
static void * const sampleDataModule2Address = (void*)0x500100;


typedef int (*EntryPoint)();

DESCR_INT* idt = 0;

void int80Handler();
void keyboardHandler();
void timerTickHandler();
void networkHandler();

void setup_IDT_entry (int index, byte selector, dword offset, byte access) {
  idt[index].selector = selector;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset & 0xFFFF0000) >> 16;
  idt[index].offset_h = (offset & 0xFFFFFFFF00000000) >> 32;
  idt[index].access = access;
  idt[index].cero = 0;
}

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress,
		sampleDataModule2Address
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	return getStackBase();
}

int main()
{	
	setup_IDT_entry (0x80, 0x08, &int80Handler, 0x8E);
	setup_IDT_entry (0x21, 0x08, &keyboardHandler, 0x8E);
	setup_IDT_entry (0x20, 0x08, &timerTickHandler, 0x8E);
	setup_IDT_entry (0x2B, 0x08, &networkHandler, 0x8E);

	//Turn on Interrupts
	picMasterMask(0); 
	picSlaveMask(0);
   	_sti();
   	ncClear();
	changeColour();
	changeColour();	
	checkAllBuses();
	uint8_t* mac = setUpRTL();	
	((EntryPoint)sampleCodeModuleAddress)();

	
	
	while(1) {	
	}
}
