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

void MyI2C_Start(void)  //SCL为高电平时，SDA由高变低表示起始信号；
{
    I2C_SDA_W(1);
    I2C_SCL_W(1);
    I2C_SDA_W(0);
    I2C_SCL_W(0);
}

void MyI2C_Stop(void)   //SCL为高电平时，SDA由低变高表示停止信号；
{
    I2C_SDA_W(0);
    I2C_SCL_W(1);
    I2C_SDA_W(1);
}

void MyI2C_SendACK(uint8_t AckBit)  //主机在SCL高电平时拉低SDA，表示应答信号；
{
    I2C_SDA_W(AckBit); //AckBit=0表示应答，AckBit=1表示非应答
    I2C_SCL_W(1);
    I2C_SCL_W(0);
}

uint8_t MyI2C_ReceiveACK(void)  //读取从机的应答信号；
{
    uint8_t ACK;
    I2C_SDA_W(1); //释放SDA线
    I2C_SCL_W(1);
    ACK = I2C_SDA_R();
    I2C_SCL_W(0);
    return ACK;
}

uint8_t MyI2C_SendByte(uint8_t Byte)   //从机在SCL高电平时读取SDA数据;
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        I2C_SDA_W((Byte >> (7 - i)) & 0x01); //发送数据; 
        I2C_SCL_W(1);
        I2C_SCL_W(0);
    }
    return MyI2C_ReceiveACK(); //读取从机的应答信号
}

uint8_t MyI2C_ReceiveByte(uint8_t AckBit) 
{
    uint8_t i, Byte = 0x00;
    I2C_SDA_W(1); //释放SDA线
    for (i = 0; i < 8; i++)
    {
        I2C_SCL_W(1);
        if (I2C_SDA_R())
        {
            Byte |= (0x80 >> i);
        }
        I2C_SCL_W(0);
    }
    MyI2C_SendACK(AckBit); //AckBit=0表示应答，AckBit=1表示非应答
    return Byte;
}
