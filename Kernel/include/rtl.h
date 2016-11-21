#include <naiveConsole.h>
#ifndef RTL_H_
#define RTL_H_

void turnOnRTL();
void softwareReset();
void initReceivedBuffer();
void setImrIsr();
void configureReceiveBuffer();
void enableReceiveAndTransmitter();
void isrHandler();
uint8_t setUpRTL();
uint8_t * getMacAddress();
void receiveMessage();
void sendMessage(uint8_t* str,uint8_t* address, uint16_t length);

#endif /* RTL_H_ */
