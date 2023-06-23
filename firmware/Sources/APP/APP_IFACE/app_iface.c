/*********************************************************************************
* @file           : app_iface.c
* @brief          : Implementation of APP IFACE
**********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "app_iface.h"
#include "mid_comm.h"
#include <string.h>

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include "mid_reg.h"

/**********************************************************************************/
/*                      Definition of imported constant data                      */
/**********************************************************************************/
extern const MID_REG_limit_s EPC_CONF_limit_range; //used to check new limits
extern const MID_REG_periodic_s EPC_CONF_periodic_time_min; //used to check new limits and init APP_IFACE_periodic

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

static MID_REG_periodic_s periodicConfig = {};

// Callback global variables
static MID_REG_control_s const * tmp_ptr_control;
static MID_REG_meas_property_s const * tmp_ptr_meas;
static MID_REG_error_status_s * tmp_ptr_status;
static MID_REG_limit_s * tmp_ptr_limits;
static MID_REG_control_s * tmp_ptr_consign;
static MID_COMM_result_e callback_res;

// Periodic variables
static MID_REG_periodic_s periodicCounter;
static MID_REG_error_status_s prevStatus;
static MID_REG_control_s prevControl;

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

void MID_CommCallbackControlMode(MID_REG_control_s * const data){
	*tmp_ptr_consign = *data;
}

void MID_CommCallbackConfigPeriodicConfig(MID_REG_periodic_s * data){
	periodicConfig = *data;
}

void MID_CommCallbackRequest(const MID_COMM_request_e req){
	if(req == MID_COMM_REQUEST_INFO){
		callback_res |= MID_CommSendInfo();
	}
	else if (req == MID_COMM_REQUEST_CONTROL){
		callback_res |= MID_CommSendControlMode(tmp_ptr_control);
	}
	else if (req == MID_COMM_REQUEST_STATUS){
		callback_res |= MID_CommSendStatus((MID_REG_error_status_s * const ) tmp_ptr_status);
	}
	else if (req == MID_COMM_REQUEST_ELECT_MEAS){
		callback_res |= MID_CommSendElectMeas((MID_REG_meas_property_s * const ) tmp_ptr_meas);
	}
	else if (req == MID_COMM_REQUEST_TEMP_MEAS){
		callback_res |= MID_CommSendTempMeas((MID_REG_meas_property_s * const ) tmp_ptr_meas);
	}
	else if (req == MID_COMM_REQUEST_HEARTBEAT){
		periodicCounter.usrHeartBeatPeriod = 0;
	}
	else{
		callback_res = MID_COMM_RESULT_ERROR;
	}
}

void MID_CommCallbackLimit(const MID_COMM_msg_id_e lim_type, const uint16_t valueMin, const uint16_t valueMax){
	if(lim_type == MID_COMM_MSG_ID_LS_VOLT_LIMIT){
		tmp_ptr_limits->lsVoltMax = valueMax;
		tmp_ptr_limits->lsVoltMin = valueMin;
	}
	else if(lim_type == MID_COMM_MSG_ID_LS_CURR_LIMIT){
		tmp_ptr_limits->lsCurrMax = valueMax;
		tmp_ptr_limits->lsCurrMin = valueMin;
	}
	else if(lim_type == MID_COMM_MSG_ID_HS_VOLT_LIMIT){
		tmp_ptr_limits->hsVoltMax = valueMax;
		tmp_ptr_limits->hsVoltMin = valueMin;
	}
	else if(lim_type == MID_COMM_MSG_ID_PWR_LIMIT){
		tmp_ptr_limits->lsPwrMax = valueMax;
		tmp_ptr_limits->lsPwrMin = valueMin;
	}
	else if(lim_type == MID_COMM_MSG_ID_TEMP_LIMIT){
		tmp_ptr_limits->tempMax = valueMax;
		tmp_ptr_limits->tempMin = valueMin;
	}
}

/*This register has to be initialized in run because the definition of limit ranges
 * in EPC_CONF as an struct makes it impossible for the linker to understand that in
 * EPC_CONF this memory zones are signed to the defines in this module.*/
APP_IFACE_result_e AppIfacePeriodicRegister () {

	/*		APP_IFACE_periodic  	*/
	periodicConfig.usrHeartBeatPeriod = EPC_CONF_periodic_time_min.usrHeartBeatPeriod;
	periodicConfig.electricMsgPeriod  = EPC_CONF_periodic_time_min.electricMsgPeriod;
	periodicConfig.tempMsgPeriod      = EPC_CONF_periodic_time_min.tempMsgPeriod;
	periodicConfig.usrHeartBeatStatus	= MID_REG_DISABLED;
	periodicConfig.electricMsgStatus	= MID_REG_DISABLED;
	periodicConfig.tempMsgStatus		= MID_REG_DISABLED;

	return APP_IFACE_RESULT_SUCCESS;
}
	
APP_IFACE_result_e APP_IfaceIncommingMsg(MID_REG_control_s const *  const control,
	MID_REG_meas_property_s const * const meas, MID_REG_error_status_s * const status,
	MID_REG_limit_s * limits, MID_REG_control_s *consign){
	APP_IFACE_result_e res = APP_IFACE_RESULT_SUCCESS;
	MID_COMM_result_e mid_res;

	// Set global variables
	tmp_ptr_control = control; tmp_ptr_meas = meas; tmp_ptr_status = status;
	tmp_ptr_limits = limits; tmp_ptr_consign = consign;
	callback_res = MID_COMM_RESULT_SUCCESS;
	periodicCounter.usrHeartBeatPeriod += 1;

	mid_res = MID_CommProcessIncommingData();
	mid_res |= callback_res;
	if (mid_res == MID_COMM_RESULT_NO_MESSAGES || mid_res == MID_COMM_RESULT_SUCCESS){
		res = APP_IFACE_RESULT_SUCCESS;
	}else {
		status->commErr = MID_REG_ERROR_RAISED;
		status->lastErrVal = mid_res;
		res = APP_IFACE_RESULT_ERROR;
	}
	if(periodicConfig.usrHeartBeatStatus == MID_REG_ENABLED && periodicCounter.usrHeartBeatPeriod >= periodicConfig.usrHeartBeatPeriod){
		status->commErr = MID_REG_ERROR_RAISED;
		status->lastErrVal = periodicCounter.usrHeartBeatPeriod;
	}

	return res;
}

APP_IFACE_result_e APP_IfaceProcessPeriodic(MID_REG_meas_property_s * const meas,
	MID_REG_error_status_s *  const status){
	APP_IFACE_result_e res = APP_IFACE_RESULT_SUCCESS;
	MID_COMM_result_e mid_res = MID_COMM_RESULT_SUCCESS;

	if (periodicConfig.electricMsgStatus){
		periodicCounter.electricMsgPeriod += 1;
		if(periodicCounter.electricMsgPeriod >= periodicConfig.electricMsgPeriod){
			periodicCounter.electricMsgPeriod = 0;
			mid_res |= MID_CommSendElectMeas(meas);
		}
	}
	else if(periodicConfig.tempMsgStatus){
		periodicCounter.tempMsgPeriod += 1;
		if(periodicCounter.tempMsgPeriod >= periodicConfig.tempMsgPeriod){
			periodicCounter.tempMsgPeriod = 0;
			mid_res |= MID_CommSendTempMeas(meas);
		}
	}

	if(memcmp(&prevStatus, status, sizeof(MID_REG_error_status_s)) != 0){
		// Send status if changed
		mid_res |= MID_CommSendStatus(status);
		prevStatus = *status;
	}

	if (mid_res == MID_COMM_RESULT_NO_MESSAGES || mid_res == MID_COMM_RESULT_SUCCESS){
		res = APP_IFACE_RESULT_SUCCESS;
	}
	return res;
}

// Notify change on mode if mode has been changed
APP_IFACE_result_e APP_IfaceNotifyModeChange (MID_REG_control_s const * const control){
	APP_IFACE_result_e res = APP_IFACE_RESULT_SUCCESS;
	if(memcmp(&prevControl, control, sizeof(MID_REG_control_s)) != 0){
		res |= MID_CommSendControlMode(control);
		prevControl = *control;
	}

	return res;
}
