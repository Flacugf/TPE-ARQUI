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

#define IOADDRESS 0xC000
#define RX_BUFFER 0x550000
#define TX_BUFFER 0x600000

#define RTL_TSAD_1     0x20
#define RTL_TSAD_2     0x24
#define RTL_TSAD_3     0x28
#define RTL_TSAD_4     0x2C
#define RTL_RVAD       0x30
#define RTL_COMMANDER  0x37
#define RTL_IMR        0x3C
#define RTL_ISR        0x3E
#define RTL_TX_CONFIG  0x40
#define RTL_RX_CONFIG  0x44
#define RTL_CONFIG_1 0x52

#define PIC_SLAVE_ADDR 0xA0
#define PIC_ACKNOW     0x20

#define IRQ_ROK_REG    0x0001
#define IRQ_TOK_REG    0x0004

typedef struct rtlStruct{

    uint8_t macAddress[6];
    uint8_t* rxBuffer;
    uint8_t* txBuffer;
    uint8_t rxNum;
    uint8_t txNum;

} rtlStruct;

static rtlStruct rtl;

void turnOnRTL(){
    outb(IOADDRESS + 0x52, 0x0);
}

void softwareReset(){
    outb(IOADDRESS + 0x37, 0x10);
    while( (inb(IOADDRESS + 0x37) & 0x10) != 0) { }
}

void initBuffers(){
    rtl.rxBuffer = RX_BUFFER;
    rtl.txBuffer = TX_BUFFER;
    uint32_t rxBuffAddress = (uint32_t) rtl.rxBuffer;
    uint32_t txBuffAddress = (uint32_t) rtl.txBuffer;
    outq(IOADDRESS + 0x40, 0x03000700);
    outq(IOADDRESS + 0x30, rxBuffAddress);
    outq(IOADDRESS + 0x20, txBuffAddress);
}

void setImrIsr(){
    outd(IOADDRESS + 0x3C, 0x0005);
}

void configureReceiveBuffer(){
    outq(IOADDRESS + 0x44, 0xf | (1 << 7));
}

void enableReceiveAndTransmitter(){
    outb(IOADDRESS + 0x37, 0x0C);
}

void isrHandler(){
    outd(IOADDRESS + 0x3E, 0x1);
}

uint8_t * getMacAddress() {

    uint8_t macAddress0 = inb(IOADDRESS);  
    uint8_t macAddress1 = inb(IOADDRESS + 1);
    uint8_t macAddress2 = inb(IOADDRESS + 2);
    uint8_t macAddress3 = inb(IOADDRESS + 3);
    uint8_t macAddress4 = inb(IOADDRESS + 4);
    uint8_t macAddress5 = inb(IOADDRESS + 5);

    rtl.macAddress[0]=macAddress0;
    rtl.macAddress[1]=macAddress1;
    rtl.macAddress[2]=macAddress2;
    rtl.macAddress[3]=macAddress3;
    rtl.macAddress[4]=macAddress4;
    rtl.macAddress[5]=macAddress5;

    return rtl.macAddress;
}

uint8_t * setUpRTL(){
    turnOnRTL();
    softwareReset();
    configureReceiveBuffer();
    initBuffers();
    outd( IOADDRESS + 0x3C , 0x000F);
    setImrIsr();
    enableReceiveAndTransmitter();
    isrHandler();
    rtl.rxNum = 0;
    rtl.txNum = 0;
    return getMacAddress();
}

void mem_cpy(uint8_t * buffer, uint8_t * cpy, uint64_t length){
  for ( int i = 0 ; i < length ; i++ ){
    buffer[i] = cpy[i];
}
}

void sendMessage(uint8_t* str,uint8_t* address, uint16_t length) {
    uint16_t statusAddress = IOADDRESS + 0x10 + (rtl.txNum * 4);
    uint8_t totalLength = length + 12 + 2; //Message length + Both addresses + ' '
    uint8_t* buffer = rtl.txBuffer;
    while (!(inq(statusAddress) & 0x2000)){}
    mem_cpy(buffer,address,6);
    mem_cpy(buffer+6,rtl.macAddress,6);
    mem_cpy(buffer+13,&length,1);
    mem_cpy(buffer+14,str,length);
    outq(statusAddress,(uint64_t) buffer);
    uint32_t status;
    status = 0;
    status |= totalLength & 0x1FFF;
    status |= 0 << 13;
    status |= (0 & 0x3F) <<16;
    outq(statusAddress, (uint64_t)status);
    rtl.txNum = (rtl.txNum+1)%4;
    rtl.txNum &= 0x03;

}


void printMac(uint8_t * mac){
  int size;
  char aux[30];
  for ( int i = 0 ; i < 6 ; i++ ){
    size = parseInt(aux, mac, 16);
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
int
digits(long number, int radix){
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
int
parseInt(char * buffer, long number, int radix){
    int size, i, aux, aux_size;


    size = digits(number, radix);
    aux_size = size;

    if ( number < 0 ){
        buffer[0] = '-';
        number *= -1;
        buffer++;
        aux_size--;
    }

    for(i = aux_size - 1; i >= 0 ; i-- ){
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
void receiveMessage(){
  uint16_t checkInt = ind(IOADDRESS + RTL_ISR);
  int size;
  char aux[30];
  if ( (checkInt & IRQ_ROK_REG ) != 0){
    int whisp=1;
    int broad=1;
    uint8_t * destMac = &rtl.rxBuffer[4];
    for ( int i = 0 ; i < 6; i++){
      if ( whisp ){
        if ( destMac[i] != rtl.macAddress[i] ){
          whisp = 0;
        }
      }
      if ( broad ){
        if ( destMac[i] != 0xFF ){
          broad = 0;
        }
      }
    }
    if(!whisp && !broad){
      outd(IOADDRESS + RTL_ISR, IRQ_ROK_REG);
      setUpRTL();
      outb(PIC_SLAVE_ADDR,PIC_ACKNOW);
      return;
    }
    ncNextline();
    ncPrint("Enviado Por:");
    printMac(&rtl.rxBuffer[10]);
    ncNextline();
    ncPrint((char*)&rtl.rxBuffer[18]);
    ncPrint(&rtl.rxBuffer[38]);
    ncNextline();
    outd(IOADDRESS + RTL_ISR, IRQ_ROK_REG);
    setUpRTL();
  }else if ( (checkInt & IRQ_TOK_REG) != 0){
    outd(IOADDRESS + 0x3E, IRQ_TOK_REG);
    setUpRTL();
  }else {
    ncPrint("Error");
  }
  outd(PIC_SLAVE_ADDR,PIC_ACKNOW);
}