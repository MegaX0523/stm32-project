#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"                  // Device header

void Servo_Init();
void Servo_Angle_Set(float angle);
void Key_ctl_Servo();

#endif