/**
 *  comm_cir_handle.h
 *  @Author: CJQ2805
 *  2022/12/5  14:18
 */ 
 
#ifndef __COMM_CIR_HANDLE_H
#define __COMM_CIR_HANDLE_H
#include "sys.h"

enum _id_inside_comm_bms_info_e{

	ID_COMM_BATTERY_CAP_INFO					= 0x120,
	ID_COMM_BATTERY_VOLT_CUR_INFO				= 0x121,
	ID_COMM_BMS_VOLT1_INFO						= 0x122,
	ID_COMM_BMS_VOLT2_INFO						= 0x123,
	ID_COMM_BMS_TEMP1_INFO						= 0x124,
	ID_COMM_BMS_TEMP2_INFO						= 0x125,
	ID_COMM_BMS_WORK_STAT_INFO					= 0x127,
	ID_COMM_BMS_FAULT_INFO						= 0x128,
	ID_COMM_BMS_CELL_VOLT_INFO					= 0x131,	
	ID_COMM_BATTERY_VERSION_INFO				= 0x132,
	ID_COMM_BMS_SPECIAL_FAULT_RELIEVE_INFO		= 0x133,
	ID_COMM_VCU_UPDATE_ID_INFO 					= 0x140,
	
};



struct _comm_cir_handle_t{
	
	u8  u8double_can_comm_fault;
	u8  u8id_can_comm_fault;
	u8  u8comm_stat;
	
	u8  u8slave_update_flag;
	
	u8 u8heart_timeout_flag;
};

extern struct _comm_cir_handle_t   gt_comm_cir_handle;

void CAN_DataDecode(void);

#endif


