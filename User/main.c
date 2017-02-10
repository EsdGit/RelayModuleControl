#include "main.h"

uint8_t address = 0;
uint8_t testAddress[5];
uint8_t state;
int timestep = 0;
void GetAddress();
void Delay(int ms);
void ParseMessage(uint8_t dataByte);
void changeRelay(uint8_t states);
uint8_t data[MESSAGE_LENGTH];

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		ParseMessage(USART_ReceiveData(USART1));
	}
}

int main()
{
	SysTick_Config(SystemCoreClock/1000);
	Setup();
	GetAddress();
	__enable_irq();

	state = WAIT_FOR_START_BYTE;
	GPIO_ResetBits(GPIOA, USART_REDE);
	while(1)
	{

	}
}

void GetAddress()
{
	testAddress[0] = 0;
	testAddress[1] = 0;
	testAddress[2] = 0;
	testAddress[3] = 0;
	testAddress[4] = 0;
	
	for(uint8_t i = 0; i < 100; i++)
	{
		if(GPIO_ReadInputDataBit(ADDR_PORT, ADDR0))
		{
			testAddress[0] += 1;
		}
		
		if(GPIO_ReadInputDataBit(ADDR_PORT, ADDR1))
		{
			testAddress[1] += 1;
		}
		
		if(GPIO_ReadInputDataBit(ADDR_PORT, ADDR2))
		{
			testAddress[2] += 1;
		}
		
		if(GPIO_ReadInputDataBit(ADDR_PORT, ADDR3))
		{
			testAddress[3] += 1;
		}
		
		if(GPIO_ReadInputDataBit(ADDR_PORT, ADDR4))
		{
			testAddress[4] += 1;
		}	
	}
	
	if(testAddress[0] > 90) address |= 1;
	else address |= 0;
	if(testAddress[1] > 90) address |= (1<<1);
	else address |= (0<<1);
	if(testAddress[2] > 90) address |= (1<<2);
	else address |= (0<<2);
	if(testAddress[3] > 90) address |= (1<<3);
	else address |= (0<<3);
	if(testAddress[4] > 90) address |= (1<<4);
	else address |= (0<<4);
}

void Delay(int ms)
{
	timestep = ms;
	while(timestep != 0){};
}

void SysTick_Handler(void)
{
	if(timestep != 0)
	{
		timestep--;
	}
}

void ParseMessage(uint8_t dataByte)
{
	data[state] = dataByte;
	switch(state)
	{
		case WAIT_FOR_START_BYTE:
			if(dataByte == START_BYTE) state = WAIT_FOR_ADDRESS;
			break;
		case WAIT_FOR_ADDRESS:
			if(dataByte == address) state = WAIT_FOR_DATA;
			else state = WAIT_FOR_START_BYTE;
			break;
		case WAIT_FOR_DATA:
			state = WAIT_FOR_CRC;
			break;
		case WAIT_FOR_CRC:
			if(crc8(data, MESSAGE_LENGTH - 1) == dataByte)
			{
				changeRelay(data[WAIT_FOR_DATA]);
			}
			state = WAIT_FOR_START_BYTE;
			break;
	}
}

void changeRelay(uint8_t states)
{
	if(states & 0x01) GPIO_SetBits(GPIOA, RELAY1);
	else GPIO_ResetBits(GPIOA, RELAY1);
	
	if(states & 0x02) GPIO_SetBits(GPIOB, RELAY2);
	else GPIO_ResetBits(GPIOB, RELAY2);
	
	if(states & 0x04) GPIO_SetBits(GPIOB, RELAY3);
	else GPIO_ResetBits(GPIOB, RELAY3);
	
	if(states & 0x08) GPIO_SetBits(GPIOB, RELAY4);
	else GPIO_ResetBits(GPIOB, RELAY4);
	
	if(states & 0x10) GPIO_SetBits(GPIOB, RELAY5);
	else GPIO_ResetBits(GPIOB, RELAY5);
	
	if(states & 0x20) GPIO_SetBits(GPIOB, RELAY6);
	else GPIO_ResetBits(GPIOB, RELAY6);
	
	if(states & 0x40) GPIO_SetBits(GPIOA, RELAY7);
	else GPIO_ResetBits(GPIOA, RELAY7);
	
	if(states & 0x80) GPIO_SetBits(GPIOA, RELAY8);
	else GPIO_ResetBits(GPIOA, RELAY8);
}

