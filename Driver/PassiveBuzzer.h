#ifndef __PASSIVEBUZZER_H
#define __PASSIVEBUZZER_H

#include "stm32f10x.h"                  // Device header

void PassiveBuzzer_Init();
void PassiveBuzzer_Loop(int times, int ms);
void PassiveBuzzer_on();
void PassiveBuzzer_off();

#endif