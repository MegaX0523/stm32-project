#include "Servo.h"
#include "KEY.h"
#include "OLED.h"

void PWM_sg90_SetCompare(uint16_t value);

void Servo_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef sg90InitStruct;
	sg90InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	sg90InitStruct.GPIO_Pin = GPIO_Pin_2;
	sg90InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &sg90InitStruct);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			
	TIM_InternalClockConfig(TIM2);		
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;		//ARR计数器自动重装值，舵机输入信号周期20ms		
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC预分频系数			
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);		
	
	TIM_OCInitTypeDef TIM_OCInitStructure;							
	TIM_OCStructInit(&TIM_OCInitStructure);                        
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
	TIM_OCInitStructure.TIM_Pulse = 0;								
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);                      
	
	TIM_Cmd(TIM2, ENABLE);	
}

void Servo_Angle_Set(float angle)
{
	PWM_sg90_SetCompare(angle / 180 * 2000 + 500);
}
	
void PWM_sg90_SetCompare(uint16_t value)
{
	if((value < 500) || (value > 2500))
	{
		value = 500;
	}
	TIM_SetCompare3(TIM2, value);
}

void Key_ctl_Servo()
{
	float angle = 0;
	
	OLED_ShowString(2, 1, "Angle=");
	OLED_ShowNum(2, 8, 0, 3);
	Servo_Angle_Set(angle);
	while(1)
	{
		if(KEY_Press())
		{
			angle += 30;
			if(angle > 180)
			{
				angle = 0;
			}
			OLED_ShowNum(2, 8, angle, 3);
			Servo_Angle_Set(angle);
		}
	}
}
