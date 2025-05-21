#include "MPU6050.h"
#include "MyI2C.h"
#include "OLED.h"

mpudata_t MPU6050_Data; // MPU6050 data structure

void MPU_WriteReg(uint8_t RegAddr, uint8_t Data)
{
    MyI2C_Start();
    if (!MyI2C_SendByte(MPU6050_ADDR))
    {
        MyI2C_SendByte(RegAddr); // Send register address
        MyI2C_SendByte(Data);    // Send data
    }
    MyI2C_Stop();
}

uint8_t MPU_ReadReg(uint8_t RegAddr)
{
    uint8_t Data = 0;
    MyI2C_Start();
    if (!MyI2C_SendByte(MPU6050_ADDR))
    {
        MyI2C_SendByte(RegAddr);             // Send register address
        MyI2C_Start();                       // Repeated start
        MyI2C_SendByte(MPU6050_ADDR | 0x01); // Send read command
        Data = MyI2C_ReceiveByte(1);         // Read data
    }
    MyI2C_Stop();
    return Data;
}

void MPU_Init(void)
{
    MyI2C_Init();

    MPU_WriteReg(MPU6050_PWR_MGMT_1, 0x01); // Set clock source to PLL with X axis gyroscope reference
    MPU_WriteReg(MPU6050_PWR_MGMT_2, 0x00); // Disable sleep mode
    MPU_WriteReg(MPU6050_SMPLRT_DIV, 0x09); // Set sample rate to 1kHz
    MPU_WriteReg(MPU6050_CONFIG, 0x06); // Set DLPF to 5Hz
    MPU_WriteReg(MPU6050_GYRO_CONFIG, 0x18);    // Set full scale range to ¡À2000¡ã/s
    MPU_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);   // Set full scale range to ¡À16g
}

void MPU_GetData(mpudata_t *MPU6050_Data)
{
    uint8_t i = 0;
    uint8_t data[14] = {0};

    MyI2C_Start();
    if (!MyI2C_SendByte(MPU6050_ADDR))
    {
        MyI2C_SendByte(MPU6050_ACCEL_XOUT_H); // Send register address
        MyI2C_Start();                       // Repeated start
        MyI2C_SendByte(MPU6050_ADDR | 0x01); // Send read command
        for (i = 0; i < 14; i++)
        {
            data[i] = MyI2C_ReceiveByte(i == 13); // Read data
        }
    }
    MyI2C_Stop();

    MPU6050_Data->accel[0] = (int16_t)((data[0] << 8) | data[1]);
    MPU6050_Data->accel[1] = (int16_t)((data[2] << 8) | data[3]);
    MPU6050_Data->accel[2] = (int16_t)((data[4] << 8) | data[5]);
    MPU6050_Data->temp = (int16_t)((data[6] << 8) | data[7]);
    MPU6050_Data->gyro[0] = (int16_t)((data[8] << 8) | data[9]);
    MPU6050_Data->gyro[1] = (int16_t)((data[10] << 8) | data[11]);
    MPU6050_Data->gyro[2] = (int16_t)((data[12] << 8) | data[13]);
}

void MPU_ShowData()
{
    while(1)
    {
        MPU_GetData(&MPU6050_Data); // Get data from MPU6050
        OLED_ShowNum(1, 1, MPU6050_Data.accel[0], 6); // Show X acceleration
        OLED_ShowNum(2, 1, MPU6050_Data.accel[1], 6); // Show Y acceleration
        OLED_ShowNum(3, 1, MPU6050_Data.accel[2], 6); // Show Z acceleration
        OLED_ShowNum(4, 1, MPU6050_Data.temp, 6);     // Show temperature
        OLED_ShowNum(5, 1, MPU6050_Data.gyro[0], 6);  // Show X gyroscope
        OLED_ShowNum(6, 1, MPU6050_Data.gyro[1], 6);  // Show Y gyroscope
        OLED_ShowNum(7, 1, MPU6050_Data.gyro[2], 6);  // Show Z gyroscope
    }
}