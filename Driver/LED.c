#include "LED.h"
#include "Delay.h"

void LED_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIOInitStruct);
	LED_off();
}

void LED_Loop(int times, int ms)
{
	while(times--)
	{
		LED_on();
		Delay_ms(ms);
		LED_off();
		Delay_ms(ms);
	}
}

void LED_on()
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

void LED_off()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void LED_Turn()
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, 
		!GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13));
}
