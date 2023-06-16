/*********************************************************************************
* @file           : mid_comm.c
* @brief          : Implementation of HAL TMR
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include <string.h>

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "mid_comm_test.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
uint8_t recvCtrl = 0, recvPeriodic = 0, recvReq = 0, recvLimit = 0;

MID_REG_errorStatus_s tx_status = {
	MID_REG_ERROR_RAISED, // hsVoltErr
	MID_REG_ERROR_NONE,		// lsVoltErr
	MID_REG_ERROR_RAISED, // lsCurrErr
	MID_REG_ERROR_NONE, 	// commErr
	MID_REG_ERROR_RAISED,	// tempErr
	MID_REG_ERROR_NONE, 	// intErr
	0xFCAB								// lastErrVal
};

MID_REG_meas_property_s tx_meas = {
	0xFFDC,	// tempBody
	0xC0FE,	// tempAnod
	0xEEDC,	// tempAmb
	0xAAAA,	// hsVolt
	0xBBBB,	// lsVolt
	0xCCCC	// lsCurr
};

MID_REG_control_s tx_ctrl = {
	MID_REG_ENABLED,		// outStatus
	MID_REG_MODE_CV,		// mode
	MID_REG_LIMIT_PWR,	// limitType
	0xABCD,							// modeRef
	0xFFFF,							// limRef
};

MID_REG_limit_s tx_limits = {
	0xFFFF,	// lsVoltMax
	0x1111,	// lsVoltMin
	0xFFFF,	// lsCurrMax
	0x2222,	// lsCurrMin
	0xFFFF,	// hsVoltMax
	0x3333,	// hsVoltMin
	0xFFFF,	// lsPwrMax
	0x4444,	// lsPwrMin
	0xFFFF,	// tempMax
	0x5555,	// tempMin
};


MID_REG_control_s rx_ctrl;
MID_REG_limit_s rx_limits;
MID_REG_periodic_s rx_periodic;

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
MID_COMM_result_e sendData(void){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	res |= MID_CommSendInfo();
	HAL_Delay(1);

	res |= MID_CommSendStatus(&tx_status);
	HAL_Delay(1);

	res |= MID_CommSendElectMeas(&tx_meas);
	HAL_Delay(1);
	
	res |= MID_CommSendTempMeas(&tx_meas);
	HAL_Delay(1);

	res |= MID_CommSendControlMode(&tx_ctrl);
	HAL_Delay(1);

	res |= MID_CommSendReqLimits(MID_COMM_REQUEST_LIMITS_LS_VOLT, &tx_limits);
	HAL_Delay(1);
	res |= MID_CommSendReqLimits(MID_COMM_REQUEST_LIMITS_LS_CURR, &tx_limits);
	HAL_Delay(1);
	res |= MID_CommSendReqLimits(MID_COMM_REQUEST_LIMITS_HS_VOLT, &tx_limits);
	HAL_Delay(1);
	res |= MID_CommSendReqLimits(MID_COMM_REQUEST_LIMITS_PWR, &tx_limits);
	HAL_Delay(1);
	res |= MID_CommSendReqLimits(MID_COMM_REQUEST_LIMITS_TEMP, &tx_limits);
	HAL_Delay(1);
	return res;
}


MID_COMM_result_e recvData(void){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	// Reset flags completed
	rx_ctrl = (MID_REG_control_s){ 0 };
	rx_limits = (MID_REG_limit_s){ 0 };
	rx_periodic = (MID_REG_periodic_s){ 0 };
	recvCtrl = 0, recvReq = 0, recvLimit = 0, recvPeriodic = 0;
	res |= MID_CommProcessIncommingData();
	res = MID_COMM_RESULT_ERROR;

	// Check reception of MSG 0xYY0
	if(recvCtrl != 1 || memcmp(&tx_ctrl, &rx_ctrl, sizeof(MID_REG_control_s)) != 0 ){
		res = MID_COMM_RESULT_ERROR;
	}

	// Check reception of MSG 0xYY1
	if(recvCtrl != 1 || memcmp(&tx_ctrl, &rx_ctrl, sizeof(MID_REG_errorStatus_s)) != 0 ){
			res = MID_COMM_RESULT_ERROR;
	}

	// Check reception of MSG 0xYY2-6
	if(recvLimit!= 5 || memcmp(&tx_limits, &rx_limits, sizeof(MID_REG_limit_s)) != 0 ){
			res = MID_COMM_RESULT_ERROR;
	}

	// Check reception of MSG 0xYY7
//	if(recvCtrl != 1 || memcmp(&tx_limits, &rx_limits, sizeof(MID_REG_limit_s)) != 0 ){
//			res = MID_COMM_RESULT_ERROR;
//	}

	return res;
}
/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

void MID_CommCallbackControlMode(MID_REG_control_s * const data){
	recvCtrl += 1;
	rx_ctrl = *data;
}


void  MID_CommCallbackRequest(const MID_COMM_request_e req){

}


void  MID_CommCallbackLimit(const MID_COMM_msg_id_e lim_type, const uint16_t valueMin, const uint16_t valueMax){
	recvLimit += 1;
	if (lim_type == MID_COMM_MSG_ID_LS_VOLT_LIMIT){
		rx_limits.lsVoltMin = valueMin;
		rx_limits.lsVoltMax = valueMax;
	} else if (lim_type == MID_COMM_MSG_ID_LS_CURR_LIMIT){
		rx_limits.lsCurrMin = valueMin;
		rx_limits.lsCurrMax = valueMax;
	}else if (lim_type == MID_COMM_MSG_ID_HS_VOLT_LIMIT){
		rx_limits.hsVoltMin = valueMin;
		rx_limits.hsVoltMax = valueMax;
	}else if (lim_type == MID_COMM_MSG_ID_PWR_LIMIT){
		rx_limits.lsPwrMin = valueMin;
		rx_limits.lsPwrMax = valueMax;
	}else if (lim_type == MID_COMM_MSG_ID_TEMP_LIMIT){
		rx_limits.tempMin= valueMin;
		rx_limits.tempMax = valueMax;
	}
}

void  MID_CommCallbackConfigPeriodicConfig(MID_REG_periodic_s * const  data){
	recvPeriodic += 1;
	rx_periodic = *data;
}

MID_COMM_result_e CommMainTest(void){
	MID_COMM_result_e res = MID_COMM_RESULT_SUCCESS;
	MID_CommInit();
	res |= sendData();
	res |= recvData();
	return res;
}
