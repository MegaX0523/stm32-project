#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"                  // Device header

void MySPI_W_CS(uint8_t BitValue);
void MySPI_W_SCK(uint8_t BitValue);
void MySPI_W_MOSI(uint8_t BitValue);
uint8_t MySPI_R_MISO(void);
void MySPI_Init(void);
void MySPI_Start();
void MySPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t SendByte);

#endif