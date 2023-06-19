/*********************************************************************************
* @file           : app_ctrl.c
* @brief          : Implementation of APP CTRL
**********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/

#include "app_ctrl.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/

#include "mid_reg.h" 	//Import MID_REG_info to check type
#include "epc_conf.h"
//#include "mid_pwr.h"
/**********************************************************************************/
/*                      Definition of imported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/
#define to_dW 100000
#define steps_to_ms 10 //10kHz to 1kHz (1ms)

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/
typedef enum
{
	limit_reached 	  = 0x0U,
	limit_not_reached = 0x01U,
	limit_error
} limit_status_e;

typedef enum
{
	action_charge		= 0x0U,
	action_discharge 	= 0x01U,
	action_wait	     	= 0x02
} action_e;


/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/

static limit_status_e ctrl_status = limit_reached;

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
		ctrl_time +=1;
	}
}

limit_status_e checkLimit(MID_REG_control_s * mode, const MID_REG_meas_property_s * meas, action_e ctrl_action, uint32_t ctrl_time){
	limit_status_e res = limit_not_reached;
	//check mode

		// voltage limit, charge
	if (mode->limitType == MID_REG_LIMIT_VOLT && ctrl_action == action_charge){
		if (meas->lsVolt >= (uint16_t)mode->limRef){
			res = limit_reached;
		}
	}	// voltage limit, discharge
	else if(mode->limitType == MID_REG_LIMIT_VOLT && ctrl_action == action_discharge){
		if (meas->lsVolt <= (uint16_t)mode->limRef){
			res = limit_reached;
		}
	}	// current limit, charge
	else if(mode->limitType == MID_REG_LIMIT_CURR && ctrl_action == action_charge){
		if (meas->lsCurr <= (int16_t)mode->limRef){
			res = limit_reached;
				}
	}	// current limit, discharge
	else if(mode->limitType == MID_REG_LIMIT_CURR && ctrl_action == action_discharge){
		if (meas->lsCurr >= (int16_t)mode->limRef){
			res = limit_reached;
		}
	}	// power, charge
	else if(mode->limitType == MID_REG_LIMIT_PWR && ctrl_action == action_charge){
		int16_t power = (int16_t)((int32_t)(meas->lsCurr * (int16_t)meas->lsVolt) / to_dW);
		if (power <= (int16_t)mode->limRef){
			res = limit_reached;
		}
	}	// power, discharge
	else if(mode->limitType == MID_REG_LIMIT_PWR && ctrl_action == action_discharge){
		int16_t power = (int16_t)((int32_t)(meas->lsCurr * (int16_t)meas->lsVolt) / to_dW);
		if (power >= (int16_t)mode->limRef){
			res = limit_reached;
		}
	}	// time
	else if(mode->limitType == MID_REG_LIMIT_TIME){
		if (ctrl_time >= mode->limRef){
			res = limit_reached;
		}
	}else{
		res = limit_error;
	}

	return res;
}


/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

APP_CTRL_result_e APP_CtrlCheckErrors (MID_REG_errorStatus_s * errors,
		const MID_REG_meas_property_s * meas, const MID_REG_limit_s * limits){

	APP_CTRL_result_e res = APP_CTRL_RESULT_ERROR_INT;

	//Inverse priority check to set lastErrVal to error with the biggest priority

	// Check body temp
	if ((EPC_CONF_info.hwVer%2 == 0) && // TODO: Use function to know if there is sensor present
			((meas->tempBody > limits->tempMax) || (meas->tempBody < limits->tempMin))){
			errors->tempErr = MID_REG_ERROR_RAISED;
			errors->lastErrVal =  (uint16_t)meas->tempBody;
			res = APP_CTRL_RESULT_ERROR_FOUND;
	}else{
		errors->tempErr  = MID_REG_ERROR_NONE;
	}

	// Check anode temp
	if ((EPC_CONF_info.hwVer%2 == 0) && // TODO: Use function to know if there is sensor present
			((meas->tempAnod > limits->tempMax) || (meas->tempAnod < limits->tempMin))){
			errors->tempErr = MID_REG_ERROR_RAISED;
			errors->lastErrVal =  (uint16_t)meas->tempBody;
			res = APP_CTRL_RESULT_ERROR_FOUND;
	}else{
		errors->tempErr  = MID_REG_ERROR_NONE;
	}

	// Check amb temp
	if ((EPC_CONF_info.hwVer%2 == 0) && // TODO: Use function to know if there is sensor present
			((meas->tempBody > limits->tempMax) || (meas->tempBody < limits->tempMin))){
			errors->tempErr = MID_REG_ERROR_RAISED;
			errors->lastErrVal =  (uint16_t)meas->tempBody;
			res = APP_CTRL_RESULT_ERROR_FOUND;
	}else{
		errors->tempErr  = MID_REG_ERROR_NONE;
	}

	// Check ls current
	if (meas->lsCurr > limits->lsCurrMax || meas->lsCurr < limits->lsCurrMin){
			errors->lsCurrErr  = MID_REG_ERROR_RAISED;
			errors->lastErrVal =  (uint16_t)meas->lsCurr;
			res = APP_CTRL_RESULT_ERROR_FOUND;
	}else{
			errors->lsCurrErr  = MID_REG_ERROR_NONE;
	}

	// Check ls voltage
	if (meas->lsVolt > limits->lsVoltMax || meas->lsVolt < limits->lsVoltMin){
			errors->lsVoltErr  = MID_REG_ERROR_RAISED;
			errors->lastErrVal =  meas->lsVolt;
			res = APP_CTRL_RESULT_ERROR_FOUND;
	}else{
			errors->lsVoltErr  = MID_REG_ERROR_NONE;
	}

	// Check hs voltage
	if (meas->hsVolt > limits->hsVoltMax || meas->hsVolt < limits->hsVoltMin){
		errors->hsVoltErr  = MID_REG_ERROR_RAISED;
		errors->lastErrVal =  meas->hsVolt;
		res = APP_CTRL_RESULT_ERROR_FOUND;
	}else{
		errors->hsVoltErr  = MID_REG_ERROR_NONE;
	}

	// Check internal error flag && comm flag to stop conversion if raised in other modules
	if (errors->commErr == MID_REG_ERROR_RAISED || errors->intErr == MID_REG_ERROR_RAISED){
		res = APP_CTRL_RESULT_ERROR_FOUND;
	}

	// Disable power conversion if any error is raised
	if (res == APP_CTRL_RESULT_ERROR_FOUND){
		//TODO: Disable PWM -> MID_Pwr if APP_CTRL_RESULT_ERROR_FOUND
	}else{
		res = APP_CTRL_RESULT_SUCCESS;
	}

	return res;
}


APP_CTRL_result_e APP_CtrlUpdate (MID_REG_control_s * mode, const MID_REG_meas_property_s * meas,
		const MID_REG_limit_s * limits){
	APP_CTRL_result_e res = APP_CTRL_RESULT_ERROR_INT;
	static action_e ctrl_action = action_wait;
	static uint32_t ctrl_time 	= 0;

	updateCtrlTime(&ctrl_time);
	ctrl_status = checkLimit(mode, meas, ctrl_action, ctrl_time);

	if (ctrl_status == limit_not_reached){
		//check if limit is reached
		switch(mode->mode)
		{
			case MID_REG_MODE_IDLE:
				//TODO: Disable PWM
				//change limit to reached
				break;
			case MID_REG_MODE_WAIT:
				//TODO: Disable PWM
				break;
			case MID_REG_MODE_CV:
				//call to MID_PWR_PI
				break;
			case MID_REG_MODE_CC:
				//call to MID_PWR_PI
				break;
			case MID_REG_MODE_CP:
				//call to MID_PWR_PI
				break;
			default:
				//TODO: Disable PWM
				res = APP_CTRL_RESULT_ERROR_INT;
		}

	}else if(ctrl_status == limit_reached){
		//change mode to IDLE

		res = APP_CTRL_RESULT_SUCCESS;
	}else{
		res = APP_CTRL_RESULT_ERROR_INT;
	}

	return res;

}

