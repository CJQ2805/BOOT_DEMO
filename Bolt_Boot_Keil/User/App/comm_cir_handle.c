/**
 *  comm_cir_handle.c
 *  @Author: CJQ2805
 *  2023/1/28  8:55
 */ 
#include "comm_cir_handle.h"
#include "CAN_CircularBuf.h"
#include "sys.h"
struct _comm_cir_handle_t   gt_comm_cir_handle;

void CAN_DataDecode(void)
{
	t_can_packet   trx_packet;
	u32 u32cnt = 0;
	u8 u8heart_flag = 0;
	memset(&trx_packet, 0x00, sizeof(trx_packet));
		
	if(can_take_data(&gt_STDID_can1_circul_buf, &trx_packet) <= 0 )
	{
//		u32cnt++;
//		if(u32cnt> 500)
//		{
//			u32cnt = 0;
//		}
		return;
	}
	u32cnt = 0;	
	
	switch(trx_packet.u_u32id_field.Bit.b16Data_table_index)
	{
		case ID_COMM_BMS_WORK_STAT_INFO:

			u32cnt = 0;			
			//comm_bms_stat_info_decode(trx_packet.au8data);
		break;
//		
//		case ID_COMM_BMS_FAULT_INFO:
//			gt_comm_cir_handle.u8slave_update_flag = 0;
//			comm_bms_fault_info_decode(trx_packet.au8data);
//			break;
//		
//		case ID_COMM_BMS_CELL_VOLT_INFO:	
//			comm_bms_cell_info_trans();
//			break;

//		case ID_COMM_VCU_UPDATE_ID_INFO:
//			comm_update_id_info_decode(trx_packet.au8data);
//			break;
//		
//		case ID_COMM_VCU_CHARGE_INFO:
//			u8heart_flag = 1;
//			gt_comm_cir_handle.u8heart_timeout_flag = 0;
//			comm_vcu_charge_info_decode(trx_packet.au8data);
//			break;

//		case ID_COMM_BMS_SPECIAL_FAULT_RELIEVE_INFO:
//			comm_bms_special_fault_decode(trx_packet.au8data);
//			break;	

//		case ID_COMM_BATTERY_VERSION_INFO:			
//			comm_bms_version_info_trans();
//			break;
//		
//		case ID_COMM_BATTERY_PACK_STAT_INFO:
//			comm_battery_pack_stat_decode(trx_packet.au8data);
//			break;
//		
//		case ID_COMM_BATTERY_STAT_QU_INFO:
//			comm_battery_stat_qu_info_trans();
//			break;
//		
//		default:
//			break;
	}
}


