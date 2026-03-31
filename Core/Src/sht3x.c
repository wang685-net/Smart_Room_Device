#include "i2c.h"
#include "sht3x.h"



static uint8_t sht30_crc8(uint8_t *data, size_t len) 
{
    uint8_t crc = 0xFF;
	
    for (size_t i = 0; i < len; i++) 
		{
        crc ^= data[i];
        for (uint8_t bit = 8; bit > 0; --bit) 
				{
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc = (crc << 1);
        }
    }
		
    return crc;
}


void SHT3X_Init(void)
{
	
}



uint8_t SHT3X_Get(float* temp, float* humi)
{
	uint8_t data[6] = {0};
	uint16_t data2 = 0;
	uint16_t addr = SHT3X_ADDR;
	
	uint8_t cmd[2] = {0x2C, 0x06};
	
	// 给 SHT3X 传感器发送测量命令
	if(HAL_OK != HAL_I2C_Master_Transmit(&hi2c1, addr << 1, cmd, sizeof(cmd), 1000))
		return 1;
	
  HAL_Delay(15);
	
	
	// 接收 SHT3X 传感器的测量结果数据
	if(HAL_OK != HAL_I2C_Master_Receive(&hi2c1, addr << 1, data, sizeof(data), 1000))
		return 2;
	
	// 校验数据
	if(sht30_crc8(data, 2) != data[2] || sht30_crc8(data + 3, 2) != data[5])
		return 3;
	
	// 解析数据：计算出实际温度和湿度值
	data2 = ((uint16_t)data[0] << 8) + data[1];
	
	if(temp != NULL)
	{
		*temp = -45 + 175.0 * data2 / 65535;
	}
	
	data2 = ((uint16_t)data[3] << 8) + data[4];
	
	if(humi != NULL)
	{
		*humi = 100.0 * data2 / 65535;
	}	
	
	return 0;
}


