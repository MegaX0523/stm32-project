#include "KEY.h"
#include "Delay.h"

void KEY_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIOInitStruct);
}

uint8_t KEY_Press()
{
	uint8_t KeyNum = 0;
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14))
	{
		Delay_ms(20);
		while(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14))
		Delay_ms(20);
		KeyNum = 1;
	}
	return KeyNum;
}