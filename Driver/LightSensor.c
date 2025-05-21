#include "LightSensor.h"
#include "Delay.h"
#include "LED.h"
#include "PassiveBuzzer.h"

void LightSensor_Init()
{
	// AO口模拟输出
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIOInitStructA;
	GPIOInitStructA.GPIO_Mode = GPIO_Mode_AIN;
	GPIOInitStructA.GPIO_Pin = GPIO_Pin_3;
	GPIOInitStructA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInitStructA);
	// DO口数字输出
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	GPIO_InitTypeDef GPIOInitStructB;
//	GPIOInitStructB.GPIO_Mode = GPIO_Mode_IPU;
//	GPIOInitStructB.GPIO_Pin = GPIO_Pin_11;
//	GPIOInitStructB.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIOInitStructB);
}


// 中断模式初始化
void LightSensor_Init2()
{
	// AO口模拟输出
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	GPIO_InitTypeDef GPIOInitStructA;
//	GPIOInitStructA.GPIO_Mode = GPIO_Mode_AIN;
//	GPIOInitStructA.GPIO_Pin = GPIO_Pin_3;
//	GPIOInitStructA.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIOInitStructA);
	// DO口数字输出
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIOInitStructB;
	GPIOInitStructB.GPIO_Mode = GPIO_Mode_IPU;
	GPIOInitStructB.GPIO_Pin = GPIO_Pin_11;
	GPIOInitStructB.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStructB);
	
	// AFIO时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	// 配置中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
	
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line11;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStruct);
}

uint8_t LightSensor_Get()
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
}

void LightSensor_Test()
{
	while(1)
	{	
		if(LightSensor_Get())
		{
			LED_on();
			PassiveBuzzer_on();
		}
		else 
		{
			LED_off();
			PassiveBuzzer_off();
		}
	}
}


