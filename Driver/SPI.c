#include "SPI.h"
#include "Delay.h"

void MySPI_W_CS(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_9, BitValue); // CS pin
}

void MySPI_W_SCK(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, BitValue); // SCK pin
    Delay_us(10); // Optional delay for SPI clock
}

void MySPI_W_MOSI(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_7, BitValue); // MOSI pin
}

uint8_t MySPI_R_MISO(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6); // MISO pin
}

void MySPI_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Enable GPIOA clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   // Enable GPIOB clock
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);  // Enable SPI1 clock

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                   // 50MHz
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7; // SCK, MOSI
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // MISO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // CS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    MySPI_W_CS(1);  // CS pin high
    MySPI_W_SCK(0); // SCK pin low
}

void MySPI_Start()
{
    MySPI_W_CS(0); // CS pin low
}

void MySPI_Stop()
{
    MySPI_W_CS(1); // CS pin high
}

uint8_t MySPI_SwapByte(uint8_t SendByte)
{
    uint8_t i, RecByte = 0;
    for (i = 0; i < 8; i++)
    {
        MySPI_W_MOSI((SendByte & 0x80) ? 1 : 0); // Send MSB first
        SendByte <<= 1;                        // Shift left
        MySPI_W_SCK(1);                          // SCK pin high
        RecByte <<= 1;                         // Shift left
        RecByte |= MySPI_R_MISO();               // Read MISO pin
        MySPI_W_SCK(0);                          // SCK pin low
    }
    return RecByte;
}