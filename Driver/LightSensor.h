#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H

#include "stm32f10x.h" 

void LightSensor_Init();
void LightSensor_Init2();
uint8_t LightSensor_Get();
void LightSensor_Test();
uint16_t LS_CountGet();

#endif