#include "OLEDShow.h"
#include "OLED.h"
#include "Timer.h"
#include "Interrupt.h"
#include "Delay.h"
#include "DMA.h"
#include "AD.h"

extern uint16_t Time_Sec;
extern uint16_t Time_Min;
extern uint8_t DataA[4];
extern uint8_t DataB[4];

void OLED_TimeShow()
{
    OLED_ShowString(1, 1, "Run Time:");
    OLED_ShowChar(1, 12, 'm');
    OLED_ShowChar(1, 15, 's');

    while (1)
    {
        OLED_ShowNum(1, 10, Time_Min, 2);
        OLED_ShowNum(1, 13, Time_Sec, 2);
    }
}

// need Encoder_Init()
void OLED_CounterShow()
{
    OLED_ShowString(2, 1, "Count:");
    while (1)
    {
        OLED_ShowSignedNum(2, 7, Encoder_countGet(), 3);
    }
}

// need AD_Init()
void OLED_VoltageShow()
{
    OLED_ShowString(3, 1, "Voltage:");
    OLED_ShowChar(3, 9, 'V');
    OLED_ShowChar(3, 12, '.');
    while (1)
    {
        OLED_ShowNum(3, 10, AD_Getvolatge(), 1);
        OLED_ShowNum(3, 13, (uint16_t)(AD_Getvolatge() * 100) % 100, 2);
    }
}

void OLED_DMAShow()
{
    OLED_ShowString(1, 1, "DataA");
    OLED_ShowHexNum(1, 8, (uint32_t)DataA, 8);
    OLED_ShowString(3, 1, "DataB");
    OLED_ShowHexNum(3, 8, (uint32_t)DataB, 8);
    while (1)
    {
        DataA[0]++;
        DataA[1]++;
        DataA[2]++;
        DataA[3]++;

        OLED_ShowHexNum(2, 1, DataA[0], 2);
        OLED_ShowHexNum(2, 4, DataA[1], 2);
        OLED_ShowHexNum(2, 7, DataA[2], 2);
        OLED_ShowHexNum(2, 10, DataA[3], 2);

        OLED_ShowHexNum(4, 1, DataB[0], 2);
        OLED_ShowHexNum(4, 4, DataB[1], 2);
        OLED_ShowHexNum(4, 7, DataB[2], 2);
        OLED_ShowHexNum(4, 10, DataB[3], 2);

        Delay_ms(1000);
        MyDMA_Transfer();

        OLED_ShowHexNum(2, 1, DataA[0], 2);
        OLED_ShowHexNum(2, 4, DataA[1], 2);
        OLED_ShowHexNum(2, 7, DataA[2], 2);
        OLED_ShowHexNum(2, 10, DataA[3], 2);

        OLED_ShowHexNum(4, 1, DataB[0], 2);
        OLED_ShowHexNum(4, 4, DataB[1], 2);
        OLED_ShowHexNum(4, 7, DataB[2], 2);
        OLED_ShowHexNum(4, 10, DataB[3], 2);

        Delay_ms(1000);
    }
}