#include "Setups.h"

void SetupAddrGpio()
{
	GPIO_InitTypeDef gpioStruct;
	gpioStruct.GPIO_Mode = GPIO_Mode_IN;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_Pin = ADDR0 | ADDR1 | ADDR2 | ADDR3 | ADDR4;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpioStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ADDR_PORT, &gpioStruct);
}

void SetupRelay()
{
	GPIO_InitTypeDef gpioStruct;
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_Pin = RELAY1 | RELAY7 | RELAY8;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpioStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioStruct);
	
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_Pin = RELAY2 | RELAY3 | RELAY4 | RELAY5 | RELAY6;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpioStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioStruct);
}

void SetupUSART()
{
	USART_InitTypeDef usartStruct;
	USART_StructInit(&usartStruct);
	usartStruct.USART_BaudRate = BAUDRATE;
	usartStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usartStruct.USART_Parity = USART_Parity_No;
	usartStruct.USART_StopBits = USART_StopBits_1;
	usartStruct.USART_WordLength = USART_WordLength_8b;
		
	USART_Init(USART1, &usartStruct);
	
  GPIO_InitTypeDef gpioStruct;
	GPIO_StructInit(&gpioStruct);
	gpioStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_Pin = USART_REDE;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpioStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioStruct);
	
	gpioStruct.GPIO_Mode = GPIO_Mode_AF;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_Pin = USART_TX;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioStruct);
	
	gpioStruct.GPIO_Mode = GPIO_Mode_AF;
	gpioStruct.GPIO_OType = GPIO_OType_PP;
	gpioStruct.GPIO_Pin = USART_RX;
	gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioStruct);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
	
	NVIC_InitTypeDef nvicStruct;
	nvicStruct.NVIC_IRQChannel = USART1_IRQn;
	nvicStruct.NVIC_IRQChannelPriority = 0;
	nvicStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStruct);
	
	NVIC_EnableIRQ(USART1_IRQn);
	
	USART_Cmd(USART1,ENABLE);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}



void Setup()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	SetupAddrGpio();
	SetupRelay();
	SetupUSART();
}