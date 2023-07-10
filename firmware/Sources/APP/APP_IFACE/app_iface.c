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
#ifndef EPC_CONF_TESTING
void MID_CommCallbackControlMode(MID_REG_control_s const * const data){
	switch (data->mode){
		case MID_REG_MODE_CC:
			if (data->modeRef > tmp_ptr_limits->lsCurrMax || data->modeRef < tmp_ptr_limits->lsCurrMin){
				callback_res = MID_COMM_RESULT_FORMAT_ERROR;
			}
			break;
		case MID_REG_MODE_CV:
			if (data->modeRef > tmp_ptr_limits->lsVoltMax || data->modeRef < tmp_ptr_limits->lsVoltMin){
				callback_res = MID_COMM_RESULT_FORMAT_ERROR;
			}
			break;
		case MID_REG_MODE_CP:
			if (data->modeRef > tmp_ptr_limits->lsPwrMax || data->modeRef < tmp_ptr_limits->lsPwrMin){
				callback_res = MID_COMM_RESULT_FORMAT_ERROR;
			}
			break;
		case MID_REG_MODE_WAIT:
			if (data->outStatus != MID_REG_DISABLED){
				callback_res = MID_COMM_RESULT_FORMAT_ERROR;
			}
			break;
		case MID_REG_MODE_IDLE:
			//NOP
			break;
		default:
			callback_res = MID_COMM_RESULT_FORMAT_ERROR;
			break;

	}
	if (callback_res == MID_COMM_RESULT_SUCCESS){
		switch (data->limitType){
			case MID_REG_LIMIT_CURR:
				if (data->limRef > tmp_ptr_limits->lsCurrMax || data->limRef < tmp_ptr_limits->lsCurrMin ||
						data->mode == MID_REG_MODE_CC ){ //|| tmp_ptr_meas->lsVolt
					callback_res = MID_COMM_RESULT_FORMAT_ERROR;
				}
				break;
			case MID_REG_LIMIT_VOLT:
				if (data->limRef > tmp_ptr_limits->lsVoltMax || data->limRef < tmp_ptr_limits->lsVoltMin){
					callback_res = MID_COMM_RESULT_FORMAT_ERROR;
				}
				break;
			case MID_REG_LIMIT_PWR:
				if (data->limRef > tmp_ptr_limits->lsPwrMax || data->limRef < tmp_ptr_limits->lsPwrMin){
					callback_res = MID_COMM_RESULT_FORMAT_ERROR;
				}
				break;
			case MID_REG_LIMIT_TIME:
				//NOP
				break;
			default:
				callback_res = MID_COMM_RESULT_FORMAT_ERROR;
				break;
		}
	}
	if (callback_res == MID_COMM_RESULT_SUCCESS){
		*tmp_ptr_consign = *data;
	}
	callback_res |= MID_CommSendControlMode(tmp_ptr_consign);

}

void MID_CommCallbackConfigPeriodicConfig(MID_REG_periodic_s const * const data){
	if (data->electricMsgStatus == MID_REG_ENABLED || data->tempMsgStatus == MID_REG_ENABLED || data->usrHeartBeatStatus == MID_REG_ENABLED){
		// If enabled, check if period is above minimum
		if (data->electricMsgPeriod < EPC_CONF_periodic_time_min.electricMsgPeriod ||
				data->tempMsgPeriod < EPC_CONF_periodic_time_min.tempMsgPeriod ||
				data->usrHeartBeatPeriod < EPC_CONF_periodic_time_min.usrHeartBeatPeriod){
			callback_res = MID_COMM_RESULT_ERROR;
		}
	}
	if (callback_res == MID_COMM_RESULT_SUCCESS){
		periodicConfig = *data;
	}
	callback_res = MID_CommSendPeriodic(&periodicConfig);
}

void MID_CommCallbackRequest(const MID_COMM_request_e req){
	if(req == MID_COMM_REQUEST_INFO){
		callback_res = MID_CommSendInfo();
	}
	else if (req == MID_COMM_REQUEST_CONTROL){
		callback_res = MID_CommSendControlMode((MID_REG_control_s * const ) tmp_ptr_control);
	}
	else if (req == MID_COMM_REQUEST_STATUS){
		callback_res = MID_CommSendStatus((MID_REG_error_status_s * const ) tmp_ptr_status);
	}
	else if (req == MID_COMM_REQUEST_ELECT_MEAS){
		callback_res = MID_CommSendElectMeas((MID_REG_meas_property_s * const ) tmp_ptr_meas);
	}
	else if (req == MID_COMM_REQUEST_TEMP_MEAS){
		callback_res = MID_CommSendTempMeas((MID_REG_meas_property_s * const ) tmp_ptr_meas);
	}
	else if (req == MID_COMM_REQUEST_HEARTBEAT){
		periodicCounter.usrHeartBeatPeriod = 0;
	}
	else{
		callback_res = MID_COMM_RESULT_FORMAT_ERROR;
	}
}

void MID_CommCallbackLimit(const MID_COMM_msg_id_e lim_type, const uint16_t valueMin, const uint16_t valueMax){
	uint8_t offset = (MID_COMM_REQUEST_LIMITS_LS_VOLT - MID_COMM_MSG_ID_LS_VOLT_LIMIT);
	if ((int16_t)valueMin<valueMax){
		if(lim_type == MID_COMM_MSG_ID_LS_VOLT_LIMIT){
			if(valueMin >= EPC_CONF_limit_range.lsVoltMin && valueMax <= EPC_CONF_limit_range.lsVoltMax){
				tmp_ptr_limits->lsVoltMax = valueMax;
				tmp_ptr_limits->lsVoltMin = valueMin;
			}
			else{
				callback_res = MID_COMM_RESULT_FORMAT_ERROR;
			}
		}
		else if(lim_type == MID_COMM_MSG_ID_LS_CURR_LIMIT){
			if((int16_t)valueMin >= EPC_CONF_limit_range.lsCurrMin && (int16_t)valueMax <= EPC_CONF_limit_range.lsCurrMax){
				tmp_ptr_limits->lsCurrMax = (int16_t)valueMax;
				tmp_ptr_limits->lsCurrMin = (int16_t)valueMin;
			}
			else{
				callback_res = MID_COMM_RESULT_FORMAT_ERROR;
			}
		}
		else if(lim_type == MID_COMM_MSG_ID_HS_VOLT_LIMIT){
			if(valueMin >= EPC_CONF_limit_range.hsVoltMin && valueMax <= EPC_CONF_limit_range.hsVoltMax){
				tmp_ptr_limits->hsVoltMax = valueMax;
				tmp_ptr_limits->hsVoltMin = valueMin;
			}
			else{
				callback_res = MID_COMM_RESULT_FORMAT_ERROR;
			}
		}
		else if(lim_type == MID_COMM_MSG_ID_PWR_LIMIT){
			if((int16_t)valueMin >= EPC_CONF_limit_range.lsPwrMin && (int16_t)valueMax <= EPC_CONF_limit_range.lsPwrMax){
				tmp_ptr_limits->lsPwrMax = (int16_t)valueMax;
				tmp_ptr_limits->lsPwrMin = (int16_t)valueMin;
			}
			else{
				callback_res = MID_COMM_RESULT_FORMAT_ERROR;
			}
		}
		else if(lim_type == MID_COMM_MSG_ID_TEMP_LIMIT){
			if((int16_t)valueMin >= EPC_CONF_limit_range.tempMin && (int16_t)valueMax <= EPC_CONF_limit_range.tempMax){
				tmp_ptr_limits->tempMax = (int16_t)valueMax;
				tmp_ptr_limits->tempMin = (int16_t)valueMin;
			}
			else{
				callback_res = MID_COMM_RESULT_FORMAT_ERROR;
			}
		}
	}
	else {
		callback_res = MID_COMM_RESULT_FORMAT_ERROR;
	}
	callback_res = MID_CommSendReqLimits(lim_type+offset, tmp_ptr_limits);
}
#endif

APP_IFACE_result_e AppIfaceInit() {

	/*		APP_IFACE_periodic  	*/
	periodicConfig.usrHeartBeatPeriod = EPC_CONF_periodic_time_min.usrHeartBeatPeriod;
	periodicConfig.electricMsgPeriod  = EPC_CONF_periodic_time_min.electricMsgPeriod;
	periodicConfig.tempMsgPeriod      = EPC_CONF_periodic_time_min.tempMsgPeriod;
	periodicConfig.usrHeartBeatStatus	= MID_REG_DISABLED;
	periodicConfig.electricMsgStatus	= MID_REG_DISABLED;
	periodicConfig.tempMsgStatus		= MID_REG_DISABLED;
	MID_COMM_result_e res = MID_CommInit();
	return (res == MID_COMM_RESULT_SUCCESS) ? APP_IFACE_RESULT_SUCCESS : APP_IFACE_RESULT_ERROR;
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
	if (tmp_ptr_status->hsVoltErr == MID_REG_ERROR_NONE &&
			tmp_ptr_status->lsCurrErr == MID_REG_ERROR_NONE &&
			tmp_ptr_status->lsVoltErr == MID_REG_ERROR_NONE &&
			tmp_ptr_status->tempErr == MID_REG_ERROR_NONE){
		mid_res = MID_CommProcessIncommingData();
		mid_res |= callback_res;
		if (mid_res == MID_COMM_RESULT_NO_MESSAGES || mid_res == MID_COMM_RESULT_SUCCESS){
			res = APP_IFACE_RESULT_SUCCESS;
			if (status->commErr == MID_REG_ERROR_RAISED && mid_res == MID_COMM_RESULT_SUCCESS){
				status->commErr = MID_REG_ERROR_NONE;
			}
		}else if (mid_res == MID_COMM_RESULT_FORMAT_ERROR){
			res = APP_IFACE_RESULT_SUCCESS;
		}else{
			status->commErr = MID_REG_ERROR_RAISED;
			status->lastErrVal = mid_res;
			res = APP_IFACE_RESULT_ERROR;
		}
	}
	if(periodicConfig.usrHeartBeatStatus == MID_REG_ENABLED && periodicCounter.usrHeartBeatPeriod >= periodicConfig.usrHeartBeatPeriod){
		status->commErr = MID_REG_ERROR_RAISED;
		status->lastErrVal = periodicCounter.usrHeartBeatPeriod;
		res = APP_IFACE_RESULT_ERROR;
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
	}else{
		status->commErr = MID_REG_ERROR_RAISED;
	}
	return res;
}

// Notify change on mode if mode has been changed
APP_IFACE_result_e APP_IfaceNotifyModeChange (MID_REG_control_s const * const control){
	APP_IFACE_result_e res = APP_IFACE_RESULT_SUCCESS;
	if(memcmp(&prevControl, control, sizeof(MID_REG_control_s)) != 0){
		res |= MID_CommSendControlMode((MID_REG_control_s * const )control);
		prevControl = *control;
	}
	return res;
}
