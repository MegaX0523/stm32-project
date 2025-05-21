#ifndef __MY_I2C_H
#define __MY_I2C_H

#include "stm32f10x.h"

void I2C_SCL_W(uint8_t BitValue);
void I2C_SDA_W(uint8_t BitValue);
uint8_t I2C_SDA_R(void);
void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendACK(uint8_t AckBit);
uint8_t MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte(uint8_t AckBit);
uint8_t MyI2C_ReceiveACK(void);

#endif
