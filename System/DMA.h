#ifndef __DMA_H
#define __DMA_H

#include "stm32f10x.h"                  // Device header

void MyDMA_Init(uint32_t *addr1, uint32_t *addr2, uint16_t size);
void MyDMA_Transfer();

#endif