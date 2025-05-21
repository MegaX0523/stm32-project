#include "MyI2C.h"
#include "Delay.h"

#define I2C_GPIOCLK RCC_APB2Periph_GPIOB
#define I2C_GPIO GPIOB
#define Pin_SCL GPIO_Pin_6
#define Pin_SDA GPIO_Pin_7
#define Delay_Timeus 10

void I2C_SCL_W(uint8_t BitValue)
{
    GPIO_WriteBit(I2C_GPIO, Pin_SCL, (BitAction)BitValue);
    Delay_us(Delay_Timeus);
}

void I2C_SDA_W(uint8_t BitValue)
{
    GPIO_WriteBit(I2C_GPIO, Pin_SDA, (BitAction)BitValue);
    Delay_us(Delay_Timeus);
}

uint8_t I2C_SDA_R(void)
{
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(I2C_GPIO, Pin_SDA);
    Delay_us(Delay_Timeus);
    return BitValue;
}

void MyI2C_Init(void)
{
    RCC_APB2PeriphClockCmd(I2C_GPIOCLK, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = Pin_SCL;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = Pin_SDA;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_SetBits(GPIOB, Pin_SCL | Pin_SDA);
}

void MyI2C_Start(void)  //SCLΪ�ߵ�ƽʱ��SDA�ɸ߱�ͱ�ʾ��ʼ�źţ�
{
    I2C_SDA_W(1);
    I2C_SCL_W(1);
    I2C_SDA_W(0);
    I2C_SCL_W(0);
}

void MyI2C_Stop(void)   //SCLΪ�ߵ�ƽʱ��SDA�ɵͱ�߱�ʾֹͣ�źţ�
{
    I2C_SDA_W(0);
    I2C_SCL_W(1);
    I2C_SDA_W(1);
}

void MyI2C_SendACK(uint8_t AckBit)  //������SCL�ߵ�ƽʱ����SDA����ʾӦ���źţ�
{
    I2C_SDA_W(AckBit); //AckBit=0��ʾӦ��AckBit=1��ʾ��Ӧ��
    I2C_SCL_W(1);
    I2C_SCL_W(0);
}

uint8_t MyI2C_ReceiveACK(void)  //��ȡ�ӻ���Ӧ���źţ�
{
    uint8_t ACK;
    I2C_SDA_W(1); //�ͷ�SDA��
    I2C_SCL_W(1);
    ACK = I2C_SDA_R();
    I2C_SCL_W(0);
    return ACK;
}

uint8_t MyI2C_SendByte(uint8_t Byte)   //�ӻ���SCL�ߵ�ƽʱ��ȡSDA����;
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        I2C_SDA_W((Byte >> (7 - i)) & 0x01); //��������; 
        I2C_SCL_W(1);
        I2C_SCL_W(0);
    }
    return MyI2C_ReceiveACK(); //��ȡ�ӻ���Ӧ���ź�
}

uint8_t MyI2C_ReceiveByte(uint8_t AckBit) 
{
    uint8_t i, Byte = 0x00;
    I2C_SDA_W(1); //�ͷ�SDA��
    for (i = 0; i < 8; i++)
    {
        I2C_SCL_W(1);
        if (I2C_SDA_R())
        {
            Byte |= (0x80 >> i);
        }
        I2C_SCL_W(0);
    }
    MyI2C_SendACK(AckBit); //AckBit=0��ʾӦ��AckBit=1��ʾ��Ӧ��
    return Byte;
}
