#include "sys.h"
volatile u32TimDly_t g_Tim0Period10ms = 0UL;

/**
@brief  TIM_Delay()
@param	

*/
en_result_t TMR_Delay(bool judgement, u32TimDly_t *p_dly, uint32_t timecnt)
{
	if(false == (judgement) || (NULL == p_dly))
	{
		if(NULL != p_dly)
		{
			*p_dly = g_Tim0Period10ms;
			return ErrorInvalidParameter;
		}
	}
	
	if(NULL == *p_dly)
	{
			*p_dly = g_Tim0Period10ms;
			return ErrorInvalidParameter;		
	}
	
	if((g_Tim0Period10ms - *p_dly) >= timecnt)
	{
		*p_dly = g_Tim0Period10ms;
		return Ok;
	}
	
	return OperationInProgress;
}



uint8_t crc8(uint8_t *ptr, uint8_t len,uint8_t key)
{
	uint8_t i;
	uint8_t crc=0;
	while(len--!=0)
	{
		for(i=0x80; i!=0; i/=2)
		{
			if((crc & 0x80) != 0)
			{
				crc *= 2;
				crc ^= key;
			}
			else
			crc *= 2;

			if((*ptr & i)!=0)
			crc ^= key;
		}
		ptr++;
	}
	return(crc);
}


uint32_t crc32_compute(uint8_t * p_data, uint16_t size, uint32_t* p_crc)
{
    uint16_t i = 0;
    uint16_t j = 0;
    uint32_t crc;
    crc = ~(*p_crc);
    for (i = 0; i < size; i++)
    {
        crc = crc ^ p_data[i];
        for (j = 8; j > 0; j--)
        {
            crc = (crc >> 1) ^ (0xEDB88320U & ((crc & 1) ? 0xFFFFFFFF : 0));
        }
    }

    return ~crc;
}


uint16_t CRC16_XMODEM(uint8_t* buf, uint8_t len)
{
	volatile uint16_t crc = 0;
	uint8_t i;
	//uint16_t temp; 
	
	while (len--) {
	
	crc ^= *buf++ << 8;


	for (i = 0; i < 8; ++i) {

		if (crc & 0x8000)
			crc = (crc << 1) ^ 0x1021;
		else
			crc = crc << 1;
	}
	}
	return crc;
}


uint16_t CRC16_ModBus(uint8_t *puchMsg, uint8_t usDataLen)
{
 
 uint16_t uCRC = 0xffff;//CRC寄存器
 
 for(uint8_t num=0;num<usDataLen;num++){
	uCRC = (*puchMsg++)^uCRC;//把数据与16位的CRC寄存器的低8位相异或，结果存放于CRC寄存器。
	for(uint8_t x=0;x<8;x++){ //循环8次

		if(uCRC&0x0001){ //判断最低位为：“1”
			uCRC = uCRC>>1; //先右移
			uCRC = uCRC^0xA001; //再与0xA001异或
		}else{ //判断最低位为：“0”
			uCRC = uCRC>>1; //右移
		}
	}
 }
 return uCRC;//返回CRC校验值

}


uint16_t U8toU16(uint8_t msb, uint8_t lsb)
{
    return (uint16_t)(((uint16_t)msb << 8) | lsb);
}

void U16toU8(uint16_t value, uint8_t *const pdata)
{
    pdata[0] = LSB16(value);
    pdata[1] = MSB16(value);
}
