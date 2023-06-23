/*********************************************************************************
* @file           : mid_comm.c
* @brief          : Implementation of MID COMM
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "hal_can.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "mid_comm.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include "string.h" // memcpy

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/
#define CAN_MASK_DEV_ID 0x7F0
#define CAN_MASK_MSG_ID 0x00F

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/
#define __PACK_CAN_ID(DEV_ID, MSG_ID)  (((DEV_ID << 4) & CAN_MASK_DEV_ID) | (MSG_ID & CAN_MASK_MSG_ID))
#define __CMP_MSG_ID(CAN_ID, MSG_ID)  (CAN_ID & CAN_MASK_MSG_ID) == MSG_ID
#define __CHECK_RANGE_MSG_ID(CAN_ID, MSG_ID_MIN, MSG_ID_MAX)  ( ((CAN_ID & CAN_MASK_MSG_ID) >= MSG_ID_MIN) && ((CAN_ID & CAN_MASK_MSG_ID) <= MSG_ID_MAX) )

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
uint32_t tx_id, rx_id;
uint8_t tx_data[8], rx_data[8];
uint8_t rx_size;

MID_REG_control_s ctrl;
MID_REG_periodic_s periodic;

/**********************************************************************************/
/*                        Definition of imported variables                        */
/**********************************************************************************/
extern const MID_REG_info_s EPC_REG_info;

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/

/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/
__weak void MID_CommCallbackControlMode(MID_REG_control_s * const data);


__weak void  MID_CommCallbackConfigPeriodicConfig(MID_REG_periodic_s * const  data);


__weak void  MID_CommCallbackRequest(const MID_COMM_request_e req);


__weak void  MID_CommCallbackLimit(const MID_COMM_msg_id_e lim_type, const uint16_t valueMin, const uint16_t valueMax);

MID_COMM_result_e MID_CommInit(void){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	res |= HAL_CanAddFilters(0x120, 0x7F0);
	return res;
}


MID_COMM_result_e MID_CommProcessIncommingData(void){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	uint8_t size = 0;
	HAL_CAN_result_e res_can = HAL_CanReceive(&rx_id, rx_data, &size);
	while(res_can != HAL_CAN_RESULT_NO_MESSAGE && res == MID_COMM_RESULT_SUCCESS){
		if (__CMP_MSG_ID(rx_id, MID_COMM_MSG_ID_MODE) && size == 8){
				memcpy((uint8_t *)&ctrl, rx_data, size);
				MID_CommCallbackControlMode(&ctrl);
		} else if(__CMP_MSG_ID(rx_id, MID_COMM_MSG_ID_REQ) && size == 1){
				MID_COMM_request_e req;
				memcpy((uint8_t *)&req, rx_data, size);
				MID_CommCallbackRequest(req);
		} else if(__CHECK_RANGE_MSG_ID(rx_id, MID_COMM_MSG_ID_LS_VOLT_LIMIT, MID_COMM_MSG_ID_TEMP_LIMIT)){
				MID_COMM_msg_id_e lim = (rx_id & CAN_MASK_MSG_ID);
				if (size == 4){
					uint16_t valueMax = (rx_data[0] << 8) | rx_data[1];
					uint16_t valueMin = (rx_data[2] << 8) | rx_data[3];
					MID_CommCallbackLimit(lim, valueMin, valueMax);
				}
		} else if(__CMP_MSG_ID(rx_id, MID_COMM_MSG_ID_PERIODIC) && size == 6){
				memcpy((uint8_t *)&periodic, rx_data, size);
				MID_CommCallbackConfigPeriodicConfig(&periodic);
		} else{
			res = MID_COMM_RESULT_ERROR;
		}
		res_can = HAL_CanReceive(&rx_id, rx_data, &size);
	}

	return res;
}

MID_COMM_result_e MID_CommSendInfo (void){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	tx_id = __PACK_CAN_ID(EPC_CONF_info.id, MID_COMM_MSG_ID_INFO);
	size_t size = sizeof(EPC_CONF_info);
	memcpy(tx_data, &EPC_CONF_info, (uint8_t) size);
	res |= HAL_CanTransmit(tx_id, tx_data, size);
	return res;
}

MID_COMM_result_e MID_CommSendStatus ( MID_REG_error_status_s * const status ){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	tx_id = __PACK_CAN_ID(EPC_CONF_info.id, MID_COMM_MSG_ID_STATUS);
	size_t size = sizeof(*status);
	memcpy(tx_data, status, size);
	res |= HAL_CanTransmit(tx_id, tx_data, size);
	return res;
}

MID_COMM_result_e MID_CommSendReqLimits (const MID_COMM_request_e req, MID_REG_limit_s * const limits ){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	uint8_t offset = (req - MID_COMM_REQUEST_LIMITS_LS_VOLT);
	uint8_t* ptr_data = (uint8_t *) limits;
	size_t size = 4;

	if (req >= MID_COMM_REQUEST_LIMITS_LS_VOLT && req <= MID_COMM_REQUEST_LIMITS_TEMP){
		tx_id = __PACK_CAN_ID(EPC_CONF_info.id, (MID_COMM_MSG_ID_LS_VOLT_LIMIT+offset));
		ptr_data += offset*size;
		memcpy(tx_data, ptr_data, size);
		res |= HAL_CanTransmit(tx_id, tx_data, size);
	}
	return res;
}




MID_COMM_result_e MID_CommSendElectMeas (MID_REG_meas_property_s * const meas){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	tx_id = __PACK_CAN_ID(EPC_CONF_info.id, MID_COMM_MSG_ID_ELECT_MEAS);
	size_t size = 6;
	memcpy(tx_data, meas, size);
	res |= HAL_CanTransmit(tx_id, tx_data, size);
	return res;
}


MID_COMM_result_e MID_CommSendTempMeas (MID_REG_meas_property_s * const meas){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	tx_id = __PACK_CAN_ID(EPC_CONF_info.id, MID_COMM_MSG_ID_TEMP_MEAS);
	size_t size = 6;
	uint8_t* ptr_data = (uint8_t *) meas;
	ptr_data += size;
	memcpy(tx_data, ptr_data, size);
	res |= HAL_CanTransmit(tx_id, tx_data, size);
	return res;
}


MID_COMM_result_e MID_CommSendControlMode (MID_REG_control_s const * const mode){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	tx_id = __PACK_CAN_ID(EPC_CONF_info.id, MID_COMM_MSG_ID_MODE);
	size_t size = sizeof(*mode);
	memcpy(tx_data, mode, size);
	res |= HAL_CanTransmit(tx_id, tx_data, size);
	return res;
}


MID_COMM_result_e MID_CommSendPeriodic (MID_REG_periodic_s const * const periodic){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	tx_id = __PACK_CAN_ID(EPC_CONF_info.id, MID_COMM_MSG_ID_PERIODIC);
	size_t size = sizeof(*periodic);
	memcpy(tx_data, periodic, size);
	res |= HAL_CanTransmit(tx_id, tx_data, size);
	return res;
}
