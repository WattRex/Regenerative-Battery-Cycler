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

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/

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

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

APP_CTRL_result_e APP_CtrlCheckErrors (MID_REG_errorStatus_s * errors,
		const MID_REG_meas_property_s * meas, const MID_REG_limit_s * limits){

	res = APP_CTRL_RESULT_ERROR_INT;

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



