/**
 *  can.c
 *  @Author: CJQ2805
 *  2023/6/5  10:37
 */
 
#include "can.h"
#include "CAN_CircularBuf.h"
extern FDCAN_HandleTypeDef hfdcan1;
FDCAN_TxHeaderTypeDef FDCAN_TxHeader;
FDCAN_RxHeaderTypeDef FDCAN_RxHeader;


struct _can_param_t{
	
	u32 u32tx_mail_box;
	u8 au8tx_data[8];	
	volatile u8 au8rx_data[8];
	
};
struct _can_param_t gt_can_param;


u8 can_tx(u32 ID, u8* pu8send_buff)
{
	u16 u16cnt = 0;
	u8	u8err  = 0;
	HAL_StatusTypeDef	  HAL_Stat = HAL_ERROR;
	
	FDCAN_TxHeader.Identifier = ID;
	FDCAN_TxHeader.IdType = FDCAN_STANDARD_ID;
	FDCAN_TxHeader.TxFrameType = FDCAN_DATA_FRAME;
	FDCAN_TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	FDCAN_TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	FDCAN_TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	FDCAN_TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	FDCAN_TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	FDCAN_TxHeader.MessageMarker = 0;	
	
	 while(HAL_Stat != HAL_OK)
	 { 
		HAL_Stat = HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &FDCAN_TxHeader, pu8send_buff);
		u16cnt ++;
		if(u16cnt > 60000)
		{
			u8err = 1;
			break;
		}
			
	 }
	 
	return u8err;
}


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if (hfdcan == &hfdcan1)
	{
		if ((RxFifo0ITs & FDCAN_IT_LIST_RX_FIFO0) != RESET)
		{
		
			if(HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &FDCAN_RxHeader, (u8*)gt_can_param.au8rx_data) != HAL_OK)
			{
				//error
			}
			else
			{					
				can_rx_data(1, &FDCAN_RxHeader, (u8*)gt_can_param.au8rx_data);
			}
			
			HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_LIST_RX_FIFO0, 0);
		}
	
	}

}

void CAN_CheckError(void)
{
	FDCAN_ErrorCountersTypeDef count;
	HAL_FDCAN_GetErrorCounters(&hfdcan1, &count);

	if ((HAL_FDCAN_GetState(&hfdcan1) == HAL_FDCAN_STATE_ERROR)  || (count.TxErrorCnt > 200) || (count.RxErrorCnt > 100)) //(HAL_FDCAN_GetError(&hfdcan1) != 0) || || (HAL_FDCAN_GetState(&hfdcan1) == HAL_FDCAN_STATE_RESET)
	{
		HAL_Delay(1000);				
		HAL_FDCAN_MspDeInit(&hfdcan1);
		HAL_FDCAN_DeInit(&hfdcan1);
		HAL_FDCAN_MspInit(&hfdcan1);
		FDCAN1_Init();

//		SEGGER_RTT_printf(0,"count.TxErrorCnt = %d\r\n",count.TxErrorCnt);
//		SEGGER_RTT_printf(0,"count.RxErrorCnt= %d\r\n", count.RxErrorCnt);
//		SEGGER_RTT_printf(0,"can error\r\n");
	}
}

