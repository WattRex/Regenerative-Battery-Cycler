/*********************************************************************************
* @file           : hal_sys.c
* @brief          : Implementation of HAL_SYS
**********************************************************************************
* @attention
* Research Laboratory in Fluid Dynamics and Combustion Technologies (LIFTEC)
*   Spanish National Research Council (CSIC)
*   c/ María de Luna 10, 50018 Zaragoza, Spain
*
*   All rights reserved. Distribution or duplication without previous
*   written agreement of the owner prohibited.
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "main.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_sys.h"
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

HAL_SYS_result_t HAL_SysInit(void){
	//TODO: implement recovery mode if initialization fails.
	HAL_SYS_result_t res = HAL_SYS_RESULT_SUCCESS;
	/* Reset of all peripherals. */
	res = HAL_Init();
	if (res != HAL_SYS_RESULT_SUCCESS){
		res = HAL_SYS_RESULT_ERROR_CRIT;
	} else{
		error_raised = 0;
		SystemClock_Config();
		if (error_raised){ // System clock initialization error
			res = HAL_SYS_RESULT_ERROR_CRIT;
		}else{

		/* Initialize all configured peripherals */
#ifdef EPC_CONF_PWM_ENABLED
			if (1){
			}else{
#endif

#ifdef EPC_CONF_GPIO_ENABLED
			if(HAL_GpioInit() != HAL_GPIO_RESULT_SUCCESS){
				res = HAL_SYS_RESULT_ERROR_GPIO;
			}else{
#endif

#ifdef EPC_CONF_ADC_DMA_ENABLED
			if(HAL_AdcInit() != HAL_ADC_RESULT_SUCCESS){
				res = HAL_SYS_RESULT_ERROR_ADC;
				// TODO: add dma
			}else{
#endif

#ifdef EPC_CONF_I2C_ENABLED
			if (HAL_I2cInit () != HAL_I2C_RESULT_SUCCESS){
				res |= HAL_SYS_RESULT_ERROR_I2C;
			}
			else{
#endif

#ifdef EPC_CONF_TMR_ENABLED
			res = HAL_TmrInit(HAL_TMR_CLOCK_RT);
			if (HAL_TmrInit(HAL_TMR_CLOCK_RT) != HAL_TMR_RESULT_SUCCESS){
				res = HAL_SYS_RESULT_ERROR_CRIT;
			}else{
#endif

#ifdef EPC_CONF_CAN_ENABLED
			if (HAL_CanInit() != HAL_CAN_RESULT_SUCCESS){
				res = HAL_SYS_RESULT_ERROR_COMM;
			}else{
#endif


// Close initialization }

#ifdef EPC_CONF_CAN_ENABLED
		}
#endif

#ifdef EPC_CONF_TMR_ENABLED
		}
#endif

#ifdef EPC_CONF_I2C_ENABLED
		}
#endif

#ifdef EPC_CONF_ADC_DMA_ENABLED
		}
#endif

#ifdef EPC_CONF_GPIO_ENABLED
		}
#endif

#ifdef EPC_CONF_PWM_ENABLED
		}
#endif

		} // end_if System clock initialization
	} // end_if HAL_Init()
	return res;
}

HAL_SYS_result_t HAL_SysPwrMode(const HAL_SYS_mode_t mode){
	HAL_SYS_result_t res = HAL_SYS_RESULT_SUCCESS;
	if(mode == HAL_SYS_MODE_SLEEP){
		HAL_SuspendTick();
		HAL_PWR_EnterSLEEPMode(0, PWR_SLEEPENTRY_WFI);
	}else{ // HAL_SYS_MODE_NORMAL
	}
	return res;
}

HAL_SYS_result_t HAL_SysReset (void){
	HAL_SYS_result_t res = HAL_SYS_RESULT_SUCCESS;
	// TODO: implement this function
	return res;
}
