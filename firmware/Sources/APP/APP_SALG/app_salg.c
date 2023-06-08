/*********************************************************************************
* @file           : app_salg.c
* @brief          : Implementation of APP SALG
**********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include <stdlib.h>
#include <string.h>

#include "app_salg.h"
//#include "app_iface.h"
//#include "app_ctrl.h"

#include "hal_sys.h"
#include "epc_conf.h"

#ifdef EPC_CONF_TMR_ENABLED // TODO: remove it after integration
	#include "hal_tmr.h"
#endif
//#include "hal_wdg.h"
#include "main.h" // TODO: remove it when error handler is executed on hal_sys

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include "mid_reg.h"
extern const MID_REG_limit_s EPC_CONF_limit_range;
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
volatile uint8_t n_ints= 0, int_triggered = 0;


/*		LIMITS  	*/
MID_REG_limit_s APP_SALG_limit = {};
MID_REG_control_s APP_SALG_consign = {};
MID_REG_control_s APP_SALG_control = {};
MID_REG_errorStatus_s APP_SALG_errorStatus = {};
MID_REG_meas_s APP_SALG_meas = {};

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

APP_SALG_result_e InitRegisters () {


	/*		APP_SALG_limit  	*/
	APP_SALG_limit.hsVoltMax 		= EPC_CONF_limit_range.hsVoltMax;
	APP_SALG_limit.hsVoltMin 		= EPC_CONF_limit_range.hsVoltMin;
	APP_SALG_limit.lsVoltMax 		= EPC_CONF_limit_range.lsVoltMax;
	APP_SALG_limit.lsVoltMin 		= EPC_CONF_limit_range.lsVoltMin;
	APP_SALG_limit.lsCurrMax 		= EPC_CONF_limit_range.lsCurrMax;
	APP_SALG_limit.lsCurrMin 		= EPC_CONF_limit_range.lsCurrMin;
	APP_SALG_limit.lsPwrMax  		= EPC_CONF_MAX_EPC_PWR_DEF;
	APP_SALG_limit.lsPwrMin  		= EPC_CONF_MIN_EPC_PWR_DEF;
	APP_SALG_limit.tempMax   		= EPC_CONF_TEMP_MAX_DEF;
	APP_SALG_limit.tempMin   		= EPC_CONF_TEMP_MIN_DEF;

	/*		APP_SALG_consign  	*/
	APP_SALG_consign.outStatus  	= MID_REG_DISABLED;
	APP_SALG_consign.mode			= MID_REG_MODE_IDLE;
	APP_SALG_consign.limitType		= MID_REG_LIMIT_TIME;
	APP_SALG_consign.modeRef		= 0;
	APP_SALG_consign.limRef			= 0;

	/*		APP_SALG_control  	*/
	APP_SALG_consign.outStatus  	= MID_REG_DISABLED;
	APP_SALG_consign.mode			= MID_REG_MODE_IDLE;
	APP_SALG_consign.limitType		= MID_REG_LIMIT_TIME;
	APP_SALG_consign.modeRef		= 0;
	APP_SALG_consign.limRef			= 0;

	/*		APP_SALG_errorStatus  	*/
	APP_SALG_errorStatus.hsVoltErr 	= MID_REG_ERROR_NONE;
	APP_SALG_errorStatus.lsVoltErr	= MID_REG_ERROR_NONE;
	APP_SALG_errorStatus.lsCurrErr	= MID_REG_ERROR_NONE;
	APP_SALG_errorStatus.commErr	= MID_REG_ERROR_NONE;
	APP_SALG_errorStatus.tempErr	= MID_REG_ERROR_NONE;
	APP_SALG_errorStatus.intErr		= MID_REG_ERROR_NONE;
	APP_SALG_errorStatus.lastErrVal	= 0;

	/*		APP_SALG_meas  	*/
	APP_SALG_meas.hsVolt			= 0;
	APP_SALG_meas.lsVolt			= 0;
	APP_SALG_meas.lsCurr			= 0;
	APP_SALG_meas.tempBody			= 0;
	APP_SALG_meas.tempAnod			= 0;
	APP_SALG_meas.tempAmb			= 0;

	return APP_SALG_RESULT_SUCCESS;
}

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/
#ifndef EPC_CONF_TESTING
void HAL_TMR_TIM2_Callback(){
	HAL_ResumeTick();
	n_ints += 1;
	int_triggered += 1;
}
#endif

APP_SALG_result_e APP_SalgInit(){
	/* Initialize HAL */
	APP_SALG_result_e res= APP_SALG_RESULT_SUCCESS;
	HAL_SYS_result_e sysRes = HAL_SysInit();
	while(sysRes != HAL_SYS_RESULT_SUCCESS){
		if(sysRes == HAL_SYS_RESULT_ERROR_CRIT || sysRes == HAL_SYS_RESULT_ERROR_COMM){
			// TODO: move it to hal_sys
			/* Try re-initialization due to critical error */
			__disable_irq();
		}else{
			// Inform error on initialization
			// TODO: inform error via CAN network
		}
//	 TODO: código de error de leds con funciones de bajo nivel
		HAL_DeInit();
		sysRes = HAL_SysInit();
	}

//	HAL_WdgInit();

	// Initialize registers
	InitRegisters(); //TODO: this returns allways APP_SALG_RESULT_SUCCESS. cast to ignore or do something :)

	return res;
}


APP_SALG_result_e APP_SalgStatusMachine(){

	while(1){
		// Enters in sleep mode, CPU is stopped and all peripherals continue to operate.
		// When an interrupt occur wake up the CPU
		if(int_triggered == 0){
		}
		int_triggered = 0;


	} // End while

//		HAL_WdgRefresh();

}
