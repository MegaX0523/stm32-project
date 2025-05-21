#include "InputCapture.h"
#include "OLED.h"

void IC_SignalProduce();

void IC_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInitStruct);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);			
	TIM_InternalClockConfig(TIM3);		
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65535 - 1;		//ARR计数器自动重装值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC预分频系数			
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);		
	
	TIM_OCInitTypeDef TIM_OCInitStructure;							
	TIM_OCStructInit(&TIM_OCInitStructure);                        
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
	TIM_OCInitStructure.TIM_Pulse = 0;								
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);                      
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter = 0xF;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection =TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
	TIM_PWMIConfig(TIM3, &TIM_ICInitStruct);
	
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3, ENABLE);	
	
	IC_SignalProduce();
	
	OLED_ShowString(1, 1, "Freq=000000Hz");
	OLED_ShowString(2, 1, "Duty=000%");
}

void IC_SignalProduce()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInitStruct);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			
	TIM_InternalClockConfig(TIM2);		
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;		//ARR计数器自动重装值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;		//PSC预分频系数			
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);		
	
	TIM_OCInitTypeDef TIM_OCInitStructure;							
	TIM_OCStructInit(&TIM_OCInitStructure);                        
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
	TIM_OCInitStructure.TIM_Pulse = 30;								
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);                      
	
	TIM_Cmd(TIM2, ENABLE);	
}

uint32_t IC_GetFreq()
{
//	return (72000000 / TIM_GetPrescaler(TIM3)) / TIM_GetCapture1(TIM3); 	//算72000000 / TIM_GetPrescaler(TIM3)花时间……
	return 1000000 / TIM_GetCapture1(TIM3);
}

uint32_t IC_GetDuty()
{
	return TIM_GetCapture2(TIM3) * 100 / TIM_GetCapture1(TIM3);
}

void IC_OLEDShow()
{
	OLED_ShowNum(1, 6, IC_GetFreq(), 6);
	OLED_ShowNum(2, 6, IC_GetDuty(), 3);
}