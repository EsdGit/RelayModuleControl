#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"

#define ADDR0 GPIO_Pin_6
#define ADDR1 GPIO_Pin_5
#define ADDR2 GPIO_Pin_4
#define ADDR3 GPIO_Pin_3
#define ADDR4 GPIO_Pin_2

#define RELAY1 GPIO_Pin_15 //PA
#define RELAY2 GPIO_Pin_3
#define RELAY3 GPIO_Pin_4
#define RELAY4 GPIO_Pin_5 
#define RELAY5 GPIO_Pin_6
#define RELAY6 GPIO_Pin_7
#define RELAY7 GPIO_Pin_1 //PA
#define RELAY8 GPIO_Pin_0 //PA

#define USART_REDE GPIO_Pin_12 //PA
#define USART_TX GPIO_Pin_9
#define USART_RX GPIO_Pin_10

#define BAUDRATE 57600

#define ADDR_PORT GPIOA

#define WAIT_FOR_START_BYTE 0
#define WAIT_FOR_ADDRESS		1
#define WAIT_FOR_DATA				2
#define WAIT_FOR_CRC				3


#define START_BYTE					0xBB


void SetupAddrGpio();

void SetupUsart();

void SetupRelay();

void Setup();