#include "at24c02_i2c_drv.h"
#include "i2c.h"

/**
 * @brief		AT24C02�����ַдһ���ֽ�����
 * @param		addr ���� д���ݵĵ�ַ��0-255��
 * @param		dat  ���� ���д�����ݵĵ�ַ
 * @param		size  ���� Ҫд�����ݵĸ���
 * @retval		�ɹ� ���� HAL_OK
*/
int8_t At24c02_Write_Byte(uint16_t addr, uint8_t* dat,uint16_t size)
{
		uint16_t i = 0, temp = 0;
    HAL_StatusTypeDef ret = HAL_ERROR ;
    temp = size / (uint16_t)0x08;
    for(i = 0; i < temp; i++)
    {
        ret = HAL_I2C_Mem_Write(&hi2c1, AT24C02_ADDR_WRITE, addr + (i * 8), I2C_MEMADD_SIZE_8BIT, dat + (i * 8), 8, 0xFFFF);
        HAL_Delay(10);
    }
    temp = size % (uint16_t)0x08;
    if(temp)
    {
        HAL_Delay(10);
        ret = HAL_I2C_Mem_Write(&hi2c1, AT24C02_ADDR_WRITE, addr + (i * 8), I2C_MEMADD_SIZE_8BIT, dat + (i * 8), temp, 0xFFFF);
    }

    if(HAL_ERROR == ret)
        return -1 ;
    return HAL_OK ;
}
/**
 * @brief		AT24C02ָ����ַ��ʼ����ָ������������
 * @param		addr ���� �����ݵĵ�ַ��0-255��
 * @param		read_buf ���� ��Ŷ�ȡ���ݵĵ�ַ
 * @param   size ���� Ҫ�������ݵĸ���
 * @retval		�ɹ� ���� HAL_OK
*/
uint8_t At24c02_Read_Byte(uint16_t addr, uint8_t* read_buf, uint16_t size)
{
    return HAL_I2C_Mem_Read(&hi2c1, AT24C02_ADDR_READ, addr, I2C_MEMADD_SIZE_8BIT, read_buf, size, 0xFFFF);
}

