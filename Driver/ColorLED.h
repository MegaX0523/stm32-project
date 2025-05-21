#ifndef __COLOR_LED_H
#define __COLOR_LED_H

#include "stm32f10x.h"                  // Device header

#define Green_LEDAPin GPIO_Pin_15
#define Blue_LEDBPin GPIO_Pin_3
#define Red_LEDAPin GPIO_Pin_2

void ColorLED_Init();
void ColorLED_SetLight(uint16_t Light);
void ColorLED_Breath();

#endif