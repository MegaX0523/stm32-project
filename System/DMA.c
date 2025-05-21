#include "DMA.h"

void MyDMA_Init(uint32_t *addr1, uint32_t *addr2, uint16_t size)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // 使能DMA1时钟

    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)addr1; // 外设地址
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)addr2; // 内存地址
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = size;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure); // 初始化DMA1通道1
}

void MyDMA_Transfer()
{
    DMA_Cmd(DMA1_Channel1, DISABLE); // 使能DMA1通道1
    DMA_SetCurrDataCounter(DMA1_Channel1, 4); // 设置数据计数器
    DMA_Cmd(DMA1_Channel1, ENABLE); // 使能DMA1通道1

    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET); // 等待传输完成
    DMA_ClearFlag(DMA1_FLAG_TC1); // 清除传输完成标志
}