/* MegaX0523's STM32F103C8T6 Project */

#include "stm32f10x.h" // Device header
#include "app.h"
#include "Interrupt.h"
#include "Timer.h"
#include "OLEDShow.h"

void InitSTM32();

uint8_t tmp;
uint8_t DataA[4] = {0x0, 0x1, 0x2, 0x3};
uint8_t DataB[4] = {0x0, 0x0, 0x0, 0x0};
uint8_t DataC[256] = {0x0};
uint8_t DataD[256] = {0x0};
extern mpudata_t MPU6050_Data; // MPU6050 data structure

int main(void)
{
	InitSTM32();
	int j = 0;

	//	Key_ctl_Servo();
	//	Key_ctl_Motor();
	//	Key_ctl_IC();
	// 	OLED_DMAShow();z
	// W25Q64_ShowID();
	// MySPI_W_SCK(1);
	for (int i = 0; i < 256; i++)
	{
		DataC[i] = 255 - i;
	}
	W25Q64_SectorErase(0x000000);
	W25Q64_PageProgram(0x000000, DataC, 256);
	W25Q64_ReadData(0x000000, DataD, 256);
	while (1)
	{
		//		ColorLED_Breath();
		//		IC_OLEDShow();
		if (KEY_Press())
		{
			OLED_ShowHexNum(1, 1, DataD[j], 2);
			OLED_ShowHexNum(2, 1, DataD[j + 1], 2);
			OLED_ShowHexNum(3, 1, DataD[j + 2], 2);
			OLED_ShowHexNum(4, 1, DataD[j + 3], 2);
			j += 4;
		}
	}
}

void InitSTM32()
{
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 配置NVIC为分组2

	//	LED_Init();
	//	ColorLED_Init();
	OLED_Init();
	KEY_Init();
	//	LightSensor_Init();
	//	LightSensor_Init2();
	//	PassiveBuzzer_Init();
	//	Encoder_Init();
	Timer_Init();
	//	Servo_Init();
	//	Motor_Init();
	//	IC_Init();
	// AD_Init();
	// MyDMA_Init((uint32_t*)DataA, (uint32_t*)DataB, 4);
	// MPU_Init();
	W25Q64_Init();
}
