#ifndef __W25Q64_H
#define __W25Q64_H

#include "stm32f10x.h"                  // Device header

#define OperationSuccess 0
#define WaitOvertime 1
#define OutOfRange 2  
#define ExceedPageSize 3

void W25Q64_Init(void);
void W25Q64_ShowID(void);
void W25Q64_WriteEnable(void);
uint8_t W25Q64_WaitBusy(void);
uint8_t W25Q64_PageProgram(uint32_t addr, uint8_t *data, uint16_t len);
uint8_t W25Q64_ReadData(uint32_t addr, uint8_t *data, uint16_t len);
uint8_t W25Q64_SectorErase(uint32_t addr);
uint8_t W25Q64_BlockErase(uint32_t addr);
uint8_t W25Q64_ChipErase(void);

#endif