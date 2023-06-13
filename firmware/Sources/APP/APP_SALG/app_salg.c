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
		if(sysRes == HAL_SYS_RESULT_ERROR_CRIT){
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
