/*********************************************************************************
* @file           : app_ctrl.c
* @brief          : Implementation of Application (APP) Power Control (CTRL)
* module. Implements  the control logic  for power management. It checks and
* applies  control modes, handles  limits,   and  updates the   power output
* accordingly.
**********************************************************************************/

/*********************************************************************************
*	Copyright (C) 2023  WattRex <https://github.com/WattRex/>
*
*	This program  is free software: you  can redistribute it and/or modify it under
*	the terms of the GNU Affero General  Public  License  as published  by the Free
*	Software  Foundation, either version 3 of the License, or (at  your option) any
*	later  version.  This program  is   distributed  in  the hope that  it  will be
*	useful,but   WITHOUT  ANY  WARRANTY;   without  even  the implied   warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General
*	Public License for more details. You should   have  received a copy  of the GNU
*	Affero   General  Public License  along   with  this  program.     If  not, see
*	<https://www.gnu.org/licenses/>.
*	
*	This file is part of PowerTower, Regenerative Battery Cycler in
*	<https://github.com/WattRex/Regenerative-Battery-Cycler/>
*
* @author          : WattRex <https://github.com/WattRex/>
* @date			   : 2023-07-04
* @version		   : v1.0.0
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/

#include "app_ctrl.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/

#include "mid_reg.h" 	//Import MID_REG_info to check type
#include "epc_conf.h"
#include "mid_pwr.h"
#include <string.h>
/**********************************************************************************/
/*                      Definition of imported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/
#define steps_to_ms 10 //10kHz to 1kHz (1ms)

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/
typedef enum
{
	limit_reached 	      = 0x0U,
	limit_not_reached 	  = 0x01U,
	limit_already_reached = 0x02U,
	limit_error
} limit_status_e;

typedef enum
{
	action_charge		= 0x0U,
	action_discharge 	= 0x01U,
	action_wait	     	= 0x02U,
	action_error		= 0x03U
} action_e;


/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/

static limit_status_e ctrl_status = limit_already_reached;
static action_e ctrl_action = action_wait;
static uint32_t ctrl_time 	= 0;

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                      Definition of imported constant data                      */
/**********************************************************************************/
extern const MID_REG_info_s EPC_CONF_info;

/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/

/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/

void updateCtrlTime(uint32_t * ctrl_time){
	static uint8_t steps = 0;
	steps +=1;
	if (steps >= steps_to_ms){
		steps = 0;
		*ctrl_time +=1;
	}
}

action_e calcNewAction(const MID_REG_control_s * mode, const MID_REG_meas_property_s * meas){
	action_e res = action_error;
	switch(mode->mode)
		{
			case MID_REG_MODE_IDLE:
				res = action_wait;
				break;
			case MID_REG_MODE_WAIT:
				res = action_wait;
				break;
			case MID_REG_MODE_CC:
				res = (mode->modeRef >= 0) ? action_charge : action_discharge;
				break;
			case MID_REG_MODE_CV:
				res = (mode->modeRef >= meas->lsVolt) ? action_charge : action_discharge;
				break;
			case MID_REG_MODE_CP:
				res = (mode->modeRef >= 0) ? action_charge : action_discharge;
				break;
			default:
				res = action_wait;
				break;
		}
	return res;
}

APP_CTRL_result_e checkLimit(MID_REG_control_s * mode, const MID_REG_meas_property_s * meas, action_e ctrl_action,
		uint32_t ctrl_time, limit_status_e * res){
	// time limit (same for all modes)
	if(mode->limitType == MID_REG_LIMIT_TIME){
		if (ctrl_time >= (uint32_t)mode->limRef){
			*res = limit_reached;
		}
	}
	//constant voltage mode
	else if(mode->mode == MID_REG_MODE_CV){
		//charge
		if (ctrl_action == action_charge){
			//limit current
			if (mode->limitType == MID_REG_LIMIT_CURR && meas->lsCurr <= (uint16_t)mode->limRef &&
					ctrl_time >= EPC_CONF_CTRL_TRANS_TIME){
				*res = limit_reached;
			}
			//limit power
			else if(mode->limitType == MID_REG_LIMIT_PWR && ctrl_time >= EPC_CONF_CTRL_TRANS_TIME){
				int16_t power = (int16_t)((int32_t)(meas->lsCurr * (int16_t)meas->lsVolt) / MID_PWR_TO_dW);
				if (power <= (uint16_t)mode->limRef){
					*res = limit_reached;
				}else{
					*res = limit_not_reached;
				}
			}else{
				*res = limit_not_reached;
			}
		//discharge
		}else{
			//limit current
			if (mode->limitType == MID_REG_LIMIT_CURR && meas->lsCurr >= (uint16_t)mode->limRef &&
					ctrl_time >= EPC_CONF_CTRL_TRANS_TIME){
				*res = limit_reached;
			}
			//limit power
			else if(mode->limitType == MID_REG_LIMIT_PWR && ctrl_time >= EPC_CONF_CTRL_TRANS_TIME){
				int16_t power = (int16_t)((int32_t)(meas->lsCurr * (int16_t)meas->lsVolt) / MID_PWR_TO_dW);
				if (power >= (uint16_t)mode->limRef){
					*res = limit_reached;
				}else{
					*res = limit_not_reached;
				}
			}else{
				*res = limit_not_reached;
			}
		}
	}
	//constant current mode
	else if(mode->mode == MID_REG_MODE_CC){
		//charge
		if (ctrl_action == action_charge){
			//limit voltage
			if (mode->limitType == MID_REG_LIMIT_VOLT && meas->lsVolt >= (uint16_t)mode->limRef){
				*res = limit_reached;
			}
			//limit power
			else if(mode->limitType == MID_REG_LIMIT_PWR && ctrl_time >= EPC_CONF_CTRL_TRANS_TIME){
				int16_t power = (int16_t)((int32_t)(meas->lsCurr * (int16_t)meas->lsVolt) / MID_PWR_TO_dW);
				if (power >= (uint16_t)mode->limRef){
					*res = limit_reached;
				}else{
					*res = limit_not_reached;
				}
			}else{
				*res = limit_not_reached;
			}
		//discharge
		}else{
			//limit voltage
			if (mode->limitType == MID_REG_LIMIT_VOLT && meas->lsVolt <= (uint16_t)mode->limRef){
				*res = limit_reached;
			}
			//limit power
			else if(mode->limitType == MID_REG_LIMIT_PWR && ctrl_time >= EPC_CONF_CTRL_TRANS_TIME){
				int16_t power = (int16_t)((int32_t)(meas->lsCurr * (int16_t)meas->lsVolt) / MID_PWR_TO_dW);
				if (power >= (uint16_t)mode->limRef){
					*res = limit_reached;
				}else{
					*res = limit_not_reached;
				}
			}else{
				*res = limit_not_reached;
			}
		}
	}
	//constant power mode
	else if(mode->mode == MID_REG_MODE_CP){
		//charge
		if (ctrl_action == action_charge){
			//limit voltage
			if (mode->limitType == MID_REG_LIMIT_VOLT && meas->lsVolt >= (uint16_t)mode->limRef){
				*res = limit_reached;
			}
			//limit current
			else if(mode->limitType == MID_REG_LIMIT_CURR && meas->lsCurr <= (uint16_t)mode->limRef &&
					ctrl_time >= EPC_CONF_CTRL_TRANS_TIME){
				*res = limit_reached;
			}else{
				*res = limit_not_reached;
			}
		//discharge
		}else{
			//limit voltage
			if (mode->limitType == MID_REG_LIMIT_VOLT && meas->lsVolt <= (uint16_t)mode->limRef){
				*res = limit_reached;
			}
			//limit current
			else if(mode->limitType == MID_REG_LIMIT_CURR && meas->lsCurr <= (uint16_t)mode->limRef &&
					ctrl_time >= EPC_CONF_CTRL_TRANS_TIME){
				*res = limit_reached;
			}else{
				*res = limit_not_reached;
			}
		}
	}
	else if (ctrl_action==action_wait){
		*res = limit_not_reached;
	}else{
		*res = limit_error;
	}
	return APP_CTRL_RESULT_SUCCESS;
}


/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

APP_CTRL_result_e APP_CtrlCheckErrors (MID_REG_error_status_s * errors,
		const MID_REG_meas_property_s * meas, const MID_REG_limit_s * limits){

	APP_CTRL_result_e res = APP_CTRL_RESULT_ERROR_INT;
	MID_PWR_result_e internalRes = MID_PWR_RESULT_TIMEOUT;

	//Inverse priority check to set lastErrVal to error with the biggest priority

// Check body temp
	if ((EPC_CONF_info.tBody == MID_REG_HW_STS_SENS) &&
			((meas->tempBody > limits->tempMax) || (meas->tempBody < limits->tempMin))){
			errors->tempErr = MID_REG_ERROR_RAISED;
			errors->lastErrVal =  (uint16_t)meas->tempBody;
			res = APP_CTRL_RESULT_ERROR_RAISED;
	}else{
		errors->tempErr  = MID_REG_ERROR_NONE;
	}

	// Check anode temp
	if ((EPC_CONF_info.tAnodType != MID_REG_HW_TANOD_NO_ANODE) &&
			((meas->tempAnod > limits->tempMax) || (meas->tempAnod < limits->tempMin))){
			errors->tempErr = MID_REG_ERROR_RAISED;
			errors->lastErrVal =  (uint16_t)meas->tempBody;
			res = APP_CTRL_RESULT_ERROR_RAISED;
	}else{
		errors->tempErr  = MID_REG_ERROR_NONE;
	}

	// Check amb temp
	if ((EPC_CONF_info.tAmb == MID_REG_HW_PLASTIC_NTC) &&
			((meas->tempAmb > limits->tempMax) || (meas->tempAmb < limits->tempMin))){
			errors->tempErr = MID_REG_ERROR_RAISED;
			errors->lastErrVal =  (uint16_t)meas->tempAmb;
			res = APP_CTRL_RESULT_ERROR_RAISED;
	}else{
		errors->tempErr  = MID_REG_ERROR_NONE;
	}

	// Check ls current
	if (meas->lsCurr > limits->lsCurrMax || meas->lsCurr < limits->lsCurrMin){
			errors->lsCurrErr  = MID_REG_ERROR_RAISED;
			errors->lastErrVal =  (uint16_t)meas->lsCurr;
			res = APP_CTRL_RESULT_ERROR_RAISED;
	}else{
			errors->lsCurrErr  = MID_REG_ERROR_NONE;
	}

	// Check ls voltage
	if (meas->lsVolt > limits->lsVoltMax || meas->lsVolt < limits->lsVoltMin){
			errors->lsVoltErr  = MID_REG_ERROR_RAISED;
			errors->lastErrVal =  meas->lsVolt;
			res = APP_CTRL_RESULT_ERROR_RAISED;
	}else{
			errors->lsVoltErr  = MID_REG_ERROR_NONE;
	}

	// Check hs voltage
	if (meas->hsVolt > limits->hsVoltMax || meas->hsVolt < limits->hsVoltMin){
		errors->hsVoltErr  = MID_REG_ERROR_RAISED;
		errors->lastErrVal =  meas->hsVolt;
		res = APP_CTRL_RESULT_ERROR_RAISED;
	}else{
		errors->hsVoltErr  = MID_REG_ERROR_NONE;
	}

	// Check internal error flag && comm flag to stop conversion if raised in other modules
	if (errors->commErr == MID_REG_ERROR_RAISED || errors->intErr == MID_REG_ERROR_RAISED){
		res = APP_CTRL_RESULT_ERROR_RAISED;
	}

	// Disable power conversion if any error is raised
	if (res == APP_CTRL_RESULT_ERROR_RAISED){
		internalRes = MID_PwrSetOutput(MID_PWR_Disable);
		res = (internalRes == MID_PWR_RESULT_SUCCESS) ? APP_CTRL_RESULT_ERROR_RAISED : APP_CTRL_RESULT_ERROR_INT;
	}else{
		res = APP_CTRL_RESULT_SUCCESS;
	}

	return res;
}

APP_CTRL_result_e APP_CtrlUpdate (MID_REG_control_s * mode, const MID_REG_meas_property_s * meas,
		const MID_REG_limit_s * limits){
	APP_CTRL_result_e res = APP_CTRL_RESULT_ERROR_INT;
	MID_PWR_result_e internalRes = MID_PWR_RESULT_SUCCESS;
	updateCtrlTime(&ctrl_time);
	checkLimit(mode, meas, ctrl_action, ctrl_time, &ctrl_status);

	if (ctrl_status == limit_not_reached && internalRes == MID_PWR_RESULT_SUCCESS){
		//check if limit is reached, if not apply control 
		switch(mode->mode)
		{
			case MID_REG_MODE_WAIT:
				// If change output to disable change also register to disable
				internalRes = MID_PwrSetOutput(MID_PWR_Disable);
				mode->outStatus = MID_PWR_Disable;
				res = (internalRes == MID_PWR_RESULT_SUCCESS) ? APP_CTRL_RESULT_SUCCESS : APP_CTRL_RESULT_ERROR_INT;
				break;
			case MID_REG_MODE_CV:
				internalRes = MID_PwrApplyCtrl(mode->modeRef, meas->lsVolt, meas->lsCurr, MID_PWR_MODE_CV, *limits);
				res = (internalRes == MID_PWR_RESULT_SUCCESS) ? APP_CTRL_RESULT_SUCCESS : APP_CTRL_RESULT_ERROR_INT;
				break;
			case MID_REG_MODE_CC:
				internalRes = MID_PwrApplyCtrl(mode->modeRef, meas->lsVolt, meas->lsCurr, MID_PWR_MODE_CC, *limits);
				res = (internalRes == MID_PWR_RESULT_SUCCESS) ? APP_CTRL_RESULT_SUCCESS : APP_CTRL_RESULT_ERROR_INT;
				break;
			case MID_REG_MODE_CP:
				internalRes = MID_PwrApplyCtrl(mode->modeRef, meas->lsVolt, meas->lsCurr, MID_PWR_MODE_CP, *limits);
				res = (internalRes == MID_PWR_RESULT_SUCCESS) ? APP_CTRL_RESULT_SUCCESS : APP_CTRL_RESULT_ERROR_INT;
				break;
			case MID_REG_MODE_IDLE:
				//NOP
				//If no operation needed is success
				res = APP_CTRL_RESULT_SUCCESS;
				break;
			default:
				// If change output to disable change also register to disable
				internalRes = MID_PwrSetOutput(MID_PWR_Disable);
				mode->outStatus = MID_PWR_Disable;
				res = APP_CTRL_RESULT_ERROR_INT;
				break;
		}
	}else if(ctrl_status == limit_reached && internalRes == MID_PWR_RESULT_SUCCESS){

		MID_REG_control_s newMode = {
				MID_REG_DISABLED, 	// outStatus
				MID_REG_MODE_IDLE, 	// mode
				MID_REG_LIMIT_TIME, // limitType
				0,					// modeRef
				0					// limRef
		};
		//First change output
		// If change output to disable change also register to disable
		internalRes = MID_PwrSetOutput(MID_PWR_Disable);
		mode->outStatus = MID_PWR_Disable;
		res = (internalRes == MID_PWR_RESULT_SUCCESS) ? APP_CTRL_RESULT_SUCCESS : APP_CTRL_RESULT_ERROR_INT;
		//Then change the mode
		if (res == APP_CTRL_RESULT_SUCCESS){
			res = APP_CtrlApplyNewMode(&newMode, mode, meas);
			ctrl_status = limit_already_reached;
		}
	}else if(ctrl_status == limit_already_reached){
		//If no operation needed is success
		res = APP_CTRL_RESULT_SUCCESS;
	}else{
		res = APP_CTRL_RESULT_ERROR_INT;
	}

	return res;
}

APP_CTRL_result_e APP_CtrlApplyNewMode (const MID_REG_control_s * newMode, MID_REG_control_s * mode,
		const MID_REG_meas_property_s * meas){
	APP_CTRL_result_e res = APP_CTRL_RESULT_ERROR_INT;
	MID_PWR_result_e internalRes = MID_PWR_RESULT_TIMEOUT;
	if (newMode->outStatus == MID_REG_DISABLED){
		internalRes = MID_PwrSetOutput(MID_PWR_Disable);
	}
	//ctrl_action will receive if mode is charging or discharging
	ctrl_action = calcNewAction(newMode, meas);
	if (newMode->mode == MID_REG_MODE_ERROR || newMode->mode == MID_REG_MODE_IDLE){
		ctrl_status = limit_already_reached;
	}else{
		ctrl_status = limit_not_reached;
	}
	ctrl_time = 0;
	memcpy(mode, newMode, sizeof(MID_REG_control_s));
	//Enable PWR output for the modes that require power transfer
	if ((newMode->mode == MID_REG_MODE_CV || newMode->mode == MID_REG_MODE_CP || newMode->mode == MID_REG_MODE_CC) &&
			newMode->outStatus == MID_REG_ENABLED){
		//Update DO when new mode is applied
		internalRes = MID_PwrCalculateD0(meas->hsVolt, meas->lsVolt);
		if (internalRes == MID_PWR_RESULT_SUCCESS){
			internalRes = MID_PwrSetOutput(MID_PWR_Enable);
		}
	}else {
		//If not in control mode, the output is always disabled
		mode->outStatus == MID_REG_DISABLED;
	}
	res = (internalRes == MID_PWR_RESULT_SUCCESS) ? APP_CTRL_RESULT_SUCCESS : APP_CTRL_RESULT_ERROR_INT;

	return res;
}

