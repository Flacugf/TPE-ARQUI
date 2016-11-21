    #include <stdint.h>
    #include <naiveConsole.h>

void outb(uint16_t port, uint8_t value);
void outd(uint16_t port, uint16_t value);
void outq(uint16_t port, uint32_t value);
uint8_t inb(uint16_t port);
uint16_t ind(uint16_t port);
uint32_t inq(uint16_t port);
void syscaller(uint16_t interrupt);
char getRax();

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC

#define RTL_VENDOR_ID 0x10EC
#define RTL_DEVICE_ID 0x8139

#define COMMAND_REGISTER 0x4

    //PCI Configuration Space Access Mechanism #1
uint16_t pciConfigReadWord (uint8_t bus, uint8_t slot,
 uint8_t func, uint8_t offset)
{
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint16_t tmp = 0;

        /* create configuration address as per Figure 1 */
    
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
      (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

        /* write out the address */
    
    outq(CONFIG_ADDRESS, address);
        /* read in the data */
        /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
    
    tmp = (uint16_t)((inq(CONFIG_DATA) >> ((offset & 2) * 8)) & 0xffff);
    return (tmp);
}
 uint16_t pciConfigWriteWord (uint8_t bus, uint8_t slot,
 uint8_t func, uint8_t offset, uint16_t data)
{
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

        /* create configuration address as per Figure 1 */
    
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
      (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

        /* write out the address */
    
    outq( CONFIG_ADDRESS, address);
        /* read in the data */
        /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
    outq( CONFIG_DATA, data);
}


void checkDevice(uint8_t bus, uint8_t device, uint8_t function) {
		uint16_t vendorId = pciConfigReadWord(bus, device, function, 0);
		uint16_t deviceId = pciConfigReadWord(bus, device, function, 0x2);
		if(vendorId == RTL_VENDOR_ID && deviceId == RTL_DEVICE_ID){    
			enableMasterBit(bus,device,function,COMMAND_REGISTER);           
		}
     }

void enableMasterBit(uint8_t bus, uint8_t device, uint8_t function, uint8_t regist){
    uint16_t command;
    command = pciConfigReadWord(bus,device,function,regist);
    command |= 0x4;
    pciConfigWriteWord(bus,device,function,regist,command);
}     
     
     //Brute force Scan. Faltan mas iteraciones
     void checkAllBuses(void) {
         int bus;
         int device;
         int function;

         for(bus = 0; bus < 256; bus++) {
             for(device = 0; device < 32; device++) {
             	for(function = 0; function < 8; function++){
             		checkDevice(bus, device, function);
                }
             }
         }
     }

