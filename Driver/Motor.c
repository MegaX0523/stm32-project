#include "Motor.h"
#include "KEY.h"
#include "OLED.h"

void PWM_Motor_SetCompare(uint16_t value);

void Motor_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStruct);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			//开启AFIO的时钟，重映射必须先开启AFIO的时钟
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);			//将TIM2的引脚部分重映射，具体的映射方案需查看参考手册
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);		//将JTAG引脚失能，作为普通GPIO引脚使用
	
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStruct);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);			
	TIM_InternalClockConfig(TIM3);		
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;		//ARR计数器自动重装值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;		//PSC预分频系数			
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);		
	
	TIM_OCInitTypeDef TIM_OCInitStructure;							
	TIM_OCStructInit(&TIM_OCInitStructure);                        
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
	TIM_OCInitStructure.TIM_Pulse = 0;								
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);                      
	
	TIM_Cmd(TIM3, ENABLE);	
	
}

void Motor_Speed_Set(int16_t Speed)
{
	PWM_Motor_SetCompare(0);
	if (Speed >= 0)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		TIM_OC1PolarityConfig(TIM3, TIM_OCPolarity_High);
		PWM_Motor_SetCompare(Speed);
	}
	else 
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		TIM_OC1PolarityConfig(TIM3, TIM_OCPolarity_Low);
		PWM_Motor_SetCompare(-Speed);
	}
}
	
void PWM_Motor_SetCompare(uint16_t value)
{
	if(value > 990)
	{
		value = 0;
	}
	TIM_SetCompare1(TIM3, value);
}

void Key_ctl_Motor()
{
	float Speed = 0;
	
	OLED_ShowString(2, 1, "Speed=");
	OLED_ShowSignedNum(2, 8, Speed, 3);
	Motor_Speed_Set(0);
	while(!KEY_Press())
	{
	}
	Speed = -35;
	OLED_ShowSignedNum(2, 8, Speed, 3);
	while(1)
	{
		if(KEY_Press())
		{
			Speed += 5;
			if(Speed > 40)
			{
				Speed = 0;
			}
			OLED_ShowSignedNum(2, 8, Speed, 3);
			Motor_Speed_Set(Speed);
		}
	}
}

