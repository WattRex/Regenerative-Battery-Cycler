/*********************************************************************************
* @file              : hal_sys.c
* @brief             : Implementation of Hardware Abstraction Layer (HAL) of the
* System  Initialization and  Control.   This  module  provides    functions for
* initializing various peripherals and controlling the power mode of the system.
* The  initialization  process includes configuring   GPIOs, PWM, ADC,  CAN, STS
* (Temperature Sensor), TMR (Timers), and WDG  (Watchdog). The system can be put
* into  sleep mode or normal mode based on the input.  The file  also contains a
* function for system reset (TODO).
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
#include "epc_conf.h"
#include "epc_st_err.h" //Import EPC_ST_ERR_COUNTER
#include "main.h" //to use systemclock

#ifdef EPC_CONF_PWM_ENABLED
#include "hal_pwm.h"
#endif
#ifdef EPC_CONF_GPIO_ENABLED
   #include "hal_gpio.h"
#endif
#ifdef EPC_CONF_ADC_DMA_ENABLED
   #include "hal_adc.h"
#endif
#ifdef EPC_CONF_STS_ENABLED
   #include "hal_sts.h"
#endif
#ifdef EPC_CONF_TMR_ENABLED
   #include "hal_tmr.h"
#endif
#ifdef EPC_CONF_WDG_ENABLED
   #include "hal_wdg.h"
#endif
#ifdef EPC_CONF_CAN_ENABLED
   #include "hal_can.h"
#endif

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
/*                        Definition of imported variables                        */
/**********************************************************************************/
extern uint8_t EPC_ST_ERR_COUNTER;

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

HAL_SYS_result_e HAL_SysInit(void){
	//TODO: implement recovery mode if initialization fails.
	HAL_SYS_result_e res = HAL_SYS_RESULT_SUCCESS;
	/* Reset of all peripherals. */
	res = HAL_Init();
	if (res != HAL_SYS_RESULT_SUCCESS){
		res = HAL_SYS_RESULT_ERROR_CRIT;
	} else{
		EPC_ST_ERR_COUNTER = 0;
		SystemClock_Config();
		if (EPC_ST_ERR_COUNTER){ // System clock initialization error
			res = HAL_SYS_RESULT_ERROR_CRIT;
		}else{

		/* Initialize all configured peripherals */
#ifdef EPC_CONF_GPIO_ENABLED
			if(HAL_GpioInit() != HAL_GPIO_RESULT_SUCCESS){
				res = HAL_SYS_RESULT_ERROR_CRIT;
			}else{
#endif

#ifdef EPC_CONF_CAN_ENABLED
			if (HAL_CanInit() != HAL_CAN_RESULT_SUCCESS){
				res = HAL_SYS_RESULT_ERROR_CAN;
			}else{
#endif

#ifdef EPC_CONF_TMR_ENABLED
			HAL_TMR_result_e tmr_res = HAL_TmrInit(HAL_TMR_CLOCK_RT);
			tmr_res |= HAL_TmrInit(HAL_TMR_CLOCK_PWR_MEAS);
			if (tmr_res != HAL_TMR_RESULT_SUCCESS){
				res = HAL_SYS_RESULT_ERROR_CRIT_PERIPH;
			}else{
#endif

#ifdef EPC_CONF_ADC_DMA_ENABLED
			if(HAL_AdcInit() != HAL_ADC_RESULT_SUCCESS){
				res = HAL_SYS_RESULT_ERROR_CRIT_PERIPH;
			}else{
#endif

#ifdef EPC_CONF_PWM_ENABLED
			if (HAL_PwmInit() != HAL_PWM_RESULT_SUCCESS){
				res = HAL_SYS_RESULT_ERROR_CRIT_PERIPH;
			}else{
#endif

#ifdef EPC_CONF_STS_ENABLED
			if (EPC_CONF_info.tBody == MID_REG_HW_STS_SENS){
					if (HAL_StsInit () != HAL_STS_RESULT_SUCCESS){
							res |= HAL_SYS_RESULT_ERROR_CRIT_PERIPH;
					}
			}else{

#endif

#ifdef EPC_CONF_WDG_ENABLED
			if (HAL_WdgInit() != HAL_WDG_RESULT_SUCCESS){
				res = HAL_SYS_RESULT_ERROR_CRIT_PERIPH;
			}else{
#endif

// Close initialization }
#ifdef EPC_CONF_WDG_ENABLED
			}
#endif

#ifdef EPC_CONF_STS_ENABLED
		}
#endif

#ifdef EPC_CONF_PWM_ENABLED
		}
#endif

#ifdef EPC_CONF_ADC_DMA_ENABLED
		}
#endif

#ifdef EPC_CONF_TMR_ENABLED
		}
#endif

#ifdef EPC_CONF_CAN_ENABLED
		}
#endif

#ifdef EPC_CONF_GPIO_ENABLED
		}
#endif

		} // end_if System clock initialization
	} // end_if HAL_Init()
	return res;
}

void HAL_SysResume(void){
	HAL_ResumeTick();
}

HAL_SYS_result_e HAL_SysPwrMode(const HAL_SYS_mode_e mode){
	HAL_SYS_result_e res = HAL_SYS_RESULT_SUCCESS;
	if(mode == HAL_SYS_MODE_SLEEP){
		HAL_SuspendTick();
		HAL_PWR_EnterSLEEPMode(0, PWR_SLEEPENTRY_WFI);
	}else{ // HAL_SYS_MODE_NORMAL
	}
	return res;
}

HAL_SYS_result_e HAL_SysReset (void){
	HAL_SYS_result_e res = HAL_SYS_RESULT_SUCCESS;
	// TODO: implement this function
	return res;
}
