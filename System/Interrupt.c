#include "app.h"
#include "Interrupt.h"

int16_t Encoder_count = 0;
uint16_t Time_Sec = 0;
uint16_t Time_Min = 0;


int16_t Encoder_countGet()
{
#ifdef Encoder_USE_INTERRUPT
    return Encoder_count;
#else
    return TIM_GetCounter(TIM3);
#endif
}


void EXTI15_10_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line11) == SET)
	{
		if(LightSensor_Get())
		{
			LED_on();
		}
		else
		{
			LED_off();
		}
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
#ifdef Encoder_USE_INTERRUPT
	else if(EXTI_GetITStatus(EXTI_Line12) == SET)
	{
		Delay_ms(2);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
			{
				Encoder_count ++;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
#endif
}


void EXTI0_IRQHandler()
{
#ifdef Encoder_USE_INTERRUPT
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		Delay_ms(2);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0)
			{
				Encoder_count --;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
#endif
}

void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Time_Sec ++;
		if(Time_Sec >= 60)
		{
			Time_Min ++;
			Time_Sec = 0;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

