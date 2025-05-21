#include "ColorLED.h"
#include "Delay.h"

void PWM_LED_Init();

void ColorLED_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			//开启AFIO的时钟，重映射必须先开启AFIO的时钟
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);			//将TIM2的引脚部分重映射，具体的映射方案需查看参考手册
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);		//将JTAG引脚失能，作为普通GPIO引脚使用
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef G_R_LEDInitStruct;
	G_R_LEDInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	G_R_LEDInitStruct.GPIO_Pin = Green_LEDAPin | Red_LEDAPin;
	G_R_LEDInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &G_R_LEDInitStruct);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef B_LEDInitStruct;
	B_LEDInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	B_LEDInitStruct.GPIO_Pin = Blue_LEDBPin;
	B_LEDInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &B_LEDInitStruct);
	
	PWM_LED_Init();
	ColorLED_SetLight(0);
}

void PWM_LED_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			
	TIM_InternalClockConfig(TIM2);		
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;		//ARR计数器自动重装值		
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;	//PSC预分频系数			
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);		

	TIM_OCInitTypeDef GreenLED_InitStruct;
	GreenLED_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	GreenLED_InitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	GreenLED_InitStruct.TIM_OutputState = TIM_OutputState_Enable;
	GreenLED_InitStruct.TIM_Pulse = 0;	//CCR输出比较寄存器
	TIM_OC1Init(TIM2, &GreenLED_InitStruct);	
			
	TIM_OCInitTypeDef BlueLED_InitStruct;
	BlueLED_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	BlueLED_InitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	BlueLED_InitStruct.TIM_OutputState = TIM_OutputState_Enable;
	BlueLED_InitStruct.TIM_Pulse = 100;
	TIM_OC2Init(TIM2, &BlueLED_InitStruct);
	
	TIM_OCInitTypeDef RedLED_InitStruct;
	RedLED_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	RedLED_InitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	RedLED_InitStruct.TIM_OutputState = TIM_OutputState_Enable;
	RedLED_InitStruct.TIM_Pulse = 0;
	TIM_OC3Init(TIM2, &RedLED_InitStruct);
	
	TIM_Cmd(TIM2, ENABLE);			
}

void ColorLED_SetLight(uint16_t Light)
{
	TIM_SetCompare1(TIM2, Light);
	TIM_SetCompare2(TIM2, Light);
	TIM_SetCompare3(TIM2, Light);
}

void ColorLED_Breath()
{
	int16_t i = 0;
	while(1)
	{
		for(i = 0; i <= 100 ; i ++)
		{
			ColorLED_SetLight(i);
			Delay_ms(20);
		}
		for(i = 100; i >= 0 ; i --)
		{
			ColorLED_SetLight(i);
			Delay_ms(20);
		}
	}
}