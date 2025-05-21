#include "PassiveBuzzer.h"
#include "Delay.h"

void PassiveBuzzer_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInitStruct);
	PassiveBuzzer_off();
}

void PassiveBuzzer_Loop(int times, int ms)
{
	while(times--)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		Delay_ms(ms);
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		Delay_ms(ms);
	}
}

void PassiveBuzzer_on()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

void PassiveBuzzer_off()
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
}

