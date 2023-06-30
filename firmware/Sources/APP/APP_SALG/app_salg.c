/*********************************************************************************
* @file           : app_salg.c
* @brief          : Implementation of APP SALG
**********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include <string.h>

#include "app_salg.h"
#include "app_iface.h"
//#include "app_ctrl.h" // TODO: uncomment it

#include "mid_reg.h"
#include "mid_dabs.h"

#include "hal_sys.h"
#include "epc_conf.h"

#include "hal_tmr.h"
#include "hal_wdg.h"


/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
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
volatile uint8_t rt_n_ints = 0, rt_int_triggered = 0, pw_meas_n_ints = 0;

MID_REG_limit_s limit = { 0 };
MID_REG_control_s consign = {
			MID_REG_DISABLED, 	// outStatus
			MID_REG_MODE_IDLE, 	// mode
			MID_REG_LIMIT_TIME, // limitType
			0,									// modeRef
			0										// limRef
	};

MID_REG_control_s control = {
		MID_REG_DISABLED, 	// outStatus
		MID_REG_MODE_IDLE, 	// mode
		MID_REG_LIMIT_TIME, // limitType
		0,									// modeRef
		0										// limRef
};

MID_REG_error_status_s errorStatus = { 0 };
MID_REG_meas_property_s measures = { 0 };

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

/*This register has to be initialized in run because the definition of limit ranges
 * in EPC_CONF as an struct makes it impossible for the linker to understand that in
 * EPC_CONF this memory zones are signed to the defines in this module.*/
APP_SALG_result_e InitSalgLimitRegister () {

	/*		limit  	*/
	limit.hsVoltMax 		= EPC_CONF_limit_range.hsVoltMax;
	limit.hsVoltMin 		= EPC_CONF_limit_range.hsVoltMin;
	limit.lsVoltMax 		= EPC_CONF_limit_range.lsVoltMax;
	limit.lsVoltMin 		= EPC_CONF_limit_range.lsVoltMin;
	limit.lsCurrMax 		= EPC_CONF_limit_range.lsCurrMax;
	limit.lsCurrMin 		= EPC_CONF_limit_range.lsCurrMin;
	limit.lsPwrMax  		= EPC_CONF_MAX_EPC_PWR_DEF;
	limit.lsPwrMin  		= EPC_CONF_MIN_EPC_PWR_DEF;
	limit.tempMax   		= EPC_CONF_TEMP_MAX_DEF;
	limit.tempMin   		= EPC_CONF_TEMP_MIN_DEF;

	return APP_SALG_RESULT_SUCCESS;
}

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/
#ifndef EPC_CONF_TESTING
void HAL_TMR_RT_Callback(){
//	HAL_SysResume();
	rt_n_ints += 1;
	rt_int_triggered = 1;
}

void HAL_TMR_PWR_MEAS_Callback(void){
//	HAL_SysResume();
	pw_meas_n_ints += 1;
}
#endif

APP_SALG_result_e APP_SalgInit(){
	/* Initialize HAL */
	APP_SALG_result_e res= APP_SALG_RESULT_ERROR;
	HAL_SYS_result_e sysRes = HAL_SysInit();
	if(sysRes == HAL_SYS_RESULT_SUCCESS){
		res = APP_SALG_RESULT_SUCCESS;
	} else{

		// Set error status
		errorStatus.intErr = MID_REG_ERROR_RAISED;
		errorStatus.lastErrVal = (uint16_t) sysRes;

		// Turn of leds with error status
		MID_DabsUpdateLeds(control.mode, measures.lsCurr, &errorStatus);

		// Communicate error
		if(sysRes == HAL_SYS_RESULT_ERROR_CRIT_PERIPH){
			// There is not error on critical system or CAN, so communicate error through can network
			APP_IfaceProcessPeriodic(&measures, &errorStatus);
		}
		// Disable control
		// TODO: disable ctrl

		// Enter uC on sleep mode
		HAL_SysPwrMode(HAL_SYS_MODE_SLEEP);
	}


	// Initialize registers
	InitSalgLimitRegister(); //TODO: this returns allways APP_SALG_RESULT_SUCCESS. cast to ignore or do something :)
	AppIfacePeriodicRegister();

	#ifdef EPC_CONF_WDG_ENABLED
		HAL_WdgInit();
	#endif

	return res;
}

#include "main.h"
APP_SALG_result_e APP_SalgStatusMachine(){
	APP_SALG_result_e res = APP_SALG_RESULT_SUCCESS;
//	APP_CTRL_result_e ctrl_res = APP_CTRL_RESULT_SUCCESS;
	APP_IFACE_result_e iface_res = APP_IFACE_RESULT_SUCCESS;

	HAL_TmrStart(HAL_TMR_CLOCK_RT);
	HAL_TmrStart(HAL_TMR_CLOCK_PWR_MEAS);
	while(1){

		// 9.0 Enters on sleep mode
		/** CPU is stopped and all peripherals continue to operate.
		 * When an interrupt occur wake up the CPU
		 */
		while(rt_int_triggered == 0){
//			HAL_SysPwrMode(HAL_SYS_MODE_SLEEP);
		}

		HAL_GPIO_TogglePin(Led2_GPIO_Port, Led2_Pin);
//		HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_SET);
		// 1.0 Timer interrupt raised, sampling temperature measures
		rt_int_triggered = 0;
		pw_meas_n_ints = 0;

		// TODO: check return values

		// 2.0 Get measures
		HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_SET);
		res |= MID_DabsUpdateMeas(MID_DABS_MEAS_ELECTRIC, &measures);
		HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_RESET);
		res |= MID_DabsUpdateMeas(MID_DABS_MEAS_TEMP, &measures);

		// 3.0 Read for incoming messages
		res |= APP_IfaceIncommingMsg(&control, &measures, &errorStatus, &limit, &consign);

		// 4.0 Apply control actions
//		ctrl_res |= APP_CtrlCheckErrors (&errorStatus, &measures, &limit);
//		ctrl_res |= APP_CtrlApplyNewMode (&consign, &measures, &limit);
//		ctrl_res |= APP_CtrlUpdate(&control, &measures, &limit);

		// 5.0 Process periodic outgoing communication
		res |= APP_IfaceProcessPeriodic(&measures, &errorStatus);

		// 6.0 Update LEDs
		res |= MID_DabsUpdateLeds(control.mode, measures.lsCurr, &errorStatus);

		// 7.0 Notify user of status change
		res |= APP_IfaceNotifyModeChange(&control);

		HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_RESET);


		// 8.0 Heartbeat to whatchdog
		#ifdef EPC_CONF_WDG_ENABLED
			HAL_WdgRefresh();
		#endif

	} // End while
}
