#include "W25Q64.h"
#include "W25Q64_INS.h"
#include "SPI.h"
#include "OLED.h"

#define WaitTimeOut 1000000 // Timeout value for waiting

void W25Q64_Init(void)
{
	MySPI_Init(); // Initialize SPI
}

void W25Q64_ShowID(void)
{
	uint8_t IDinfo[3];
	MySPI_Start();
	MySPI_SwapByte(0x9F);			  // Read ID command
	IDinfo[0] = MySPI_SwapByte(W25Q64_DUMMY_BYTE); // Manufacturer
	IDinfo[1] = MySPI_SwapByte(W25Q64_DUMMY_BYTE); // Memory Type
	IDinfo[2] = MySPI_SwapByte(W25Q64_DUMMY_BYTE); // Capacity
	MySPI_Stop();

	OLED_ShowHexNum(1, 1, IDinfo[0], 2);
	OLED_ShowHexNum(2, 1, IDinfo[1], 2);
	OLED_ShowHexNum(3, 1, IDinfo[2], 2);
}

void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE); // Write Enable command
	MySPI_Stop();
}

uint8_t W25Q64_WaitBusy(void)
{
	uint32_t timeout = WaitTimeOut;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1); // Read Status Register 1 command
	while (MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 01)					  // Wait until the busy bit is cleared
	{
		timeout--;
		if (!timeout) 
		{
			MySPI_Stop();
			return WaitOvertime; // Timeout
		}
	}
	MySPI_Stop();
	return OperationSuccess; // Not Timeout
}

uint8_t W25Q64_PageProgram(uint32_t addr, uint8_t *data, uint16_t len)
{
	if (addr + len > W25Q64_MAX_ADDRESS) // Check if address exceeds maximum
	{
		return OutOfRange; // Address out of range
	}
	if ((addr % 256) + len > 256) // Check if length exceeds page size
	{
		return ExceedPageSize; // Length out of range
	}
	if (len > 256) // Check if length exceeds page size
	{
		len = 256;
	}
	W25Q64_WriteEnable(); // Enable write operation
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM); // Page Program command
	MySPI_SwapByte((addr >> 16) & 0xFF); // Address MSB
	MySPI_SwapByte((addr >> 8) & 0xFF);  // Address Middle Byte
	MySPI_SwapByte(addr & 0xFF);         // Address LSB
	for (uint16_t i = 0; i < len; i++)
	{
		MySPI_SwapByte(data[i]); // Write data
	}
	MySPI_Stop();
	return W25Q64_WaitBusy(); // Wait until the operation is complete
}

uint8_t W25Q64_ReadData(uint32_t addr, uint8_t *data, uint16_t len)
{
	if (addr + len > W25Q64_MAX_ADDRESS) // Check if address exceeds maximum
	{
		return OutOfRange; // Address out of range
	}
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA); // Read Data command
	MySPI_SwapByte((addr >> 16) & 0xFF); // Address MSB
	MySPI_SwapByte((addr >> 8) & 0xFF);  // Address Middle Byte
	MySPI_SwapByte(addr & 0xFF);         // Address LSB
	for (uint16_t i = 0; i < len; i++)
	{
		data[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE); // Read data
	}
	MySPI_Stop();
	return OperationSuccess; // Success
}

uint8_t W25Q64_SectorErase(uint32_t addr)
{
	if (addr > W25Q64_MAX_ADDRESS) // Check if address exceeds maximum
	{
		return OutOfRange; // Address out of range
	}
	W25Q64_WriteEnable(); // Enable write operation
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB); // Sector Erase command
	MySPI_SwapByte((addr >> 16) & 0xFF);     // Address MSB
	MySPI_SwapByte((addr >> 8) & 0xFF);      // Address Middle Byte
	MySPI_SwapByte(addr & 0xFF);             // Address LSB
	MySPI_Stop();
	return W25Q64_WaitBusy(); // Wait until the operation is complete
}

uint8_t W25Q64_BlockErase(uint32_t addr)
{
	if (addr > W25Q64_MAX_ADDRESS) // Check if address exceeds maximum
	{
		return OutOfRange; // Address out of range
	}
	W25Q64_WriteEnable(); // Enable write operation
	MySPI_Start();
	MySPI_SwapByte(W25Q64_BLOCK_ERASE_64KB); // Block Erase command
	MySPI_SwapByte((addr >> 16) & 0xFF);     // Address MSB
	MySPI_SwapByte((addr >> 8) & 0xFF);      // Address Middle Byte
	MySPI_SwapByte(addr & 0xFF);             // Address LSB
	MySPI_Stop();
	return W25Q64_WaitBusy(); // Wait until the operation is complete
}

uint8_t W25Q64_ChipErase(void)
{
	W25Q64_WriteEnable(); // Enable write operation
	MySPI_Start();
	MySPI_SwapByte(W25Q64_CHIP_ERASE); // Chip Erase command
	MySPI_Stop();
	return W25Q64_WaitBusy(); // Wait until the operation is complete
}

