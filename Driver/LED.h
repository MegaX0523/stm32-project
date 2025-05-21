#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h" 

void LED_Init();
void LED_Loop(int times, int ms);
void LED_on();
void LED_off();
void LED_Turn();

#endif

