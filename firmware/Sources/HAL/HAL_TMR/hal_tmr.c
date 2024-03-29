/*********************************************************************************
* @file            : hal_tmr.c
* @brief           : Implementation of Hardware Abstraction Layer (HAL) of the
* Timer (TMR). Initializes and controls hardware timers. Handles real-time and
* power measurement clocks. Provides delay and callback functionalities.
***********************************************************************************/

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
#include "epc_st_err.h" //Import EPC_ST_ERR_COUNTER

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_tmr.h"
#include "tim.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/
#define MAX_TICKS_RT 1000

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
/** Array with a @ref HAL_TMR_config_t struct for each available timer **/
static TIM_HandleTypeDef* _htim[HAL_TMR_CLOCK_COUNT];

/**********************************************************************************/
/*                        Definition of imported variables                        */
/**********************************************************************************/
extern uint8_t EPC_ST_ERR_COUNTER;

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

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

__weak void HAL_TMR_RT_Callback(void){}

__weak void HAL_TMR_PWR_MEAS_Callback(void){}

HAL_TMR_result_e HAL_TmrInit (const HAL_TMR_clock_e clock){
	HAL_TMR_result_e res = HAL_TMR_RESULT_SUCCESS;
	switch (clock){
		case HAL_TMR_CLOCK_RT:
			_htim[HAL_TMR_CLOCK_RT]= &htim2;
			EPC_ST_ERR_COUNTER = 0;
			MX_TIM2_Init();
			if (EPC_ST_ERR_COUNTER){
				res = HAL_TMR_RESULT_ERROR;
			}
			break;
		case HAL_TMR_CLOCK_PWR_MEAS:
			_htim[HAL_TMR_CLOCK_PWR_MEAS]= &htim3;
			EPC_ST_ERR_COUNTER = 0;
			MX_TIM3_Init();
			if (EPC_ST_ERR_COUNTER){
				res = HAL_TMR_RESULT_ERROR;
			}
			break;
		default:
			break;
	}
	return res;
}

HAL_TMR_result_e HAL_TmrStart (const HAL_TMR_clock_e clock){
	HAL_TMR_result_e res = HAL_TMR_RESULT_ERROR;
	if(clock < HAL_TMR_CLOCK_COUNT){
		res = HAL_TIM_Base_Start_IT(_htim[clock]);
	}
	return res;
}

HAL_TMR_result_e HAL_TmrStop (const HAL_TMR_clock_e clock){
	HAL_TMR_result_e res = HAL_TMR_RESULT_ERROR;
	if(clock < HAL_TMR_CLOCK_COUNT){
		res = HAL_TIM_Base_Stop_IT(_htim[clock]);
	}
	return res;
}

HAL_TMR_result_e HAL_TmrGet (const HAL_TMR_clock_e clock, uint16_t *value){
	HAL_TMR_result_e res = HAL_TMR_RESULT_ERROR;
	if(clock < HAL_TMR_CLOCK_COUNT){
		*value = __HAL_TIM_GET_COUNTER(_htim[clock]);
	}
	return res;
}

HAL_TMR_result_e HAL_TmrDelay(const HAL_TMR_clock_e clock, const uint16_t delay){
	HAL_TMR_result_e res = HAL_TMR_RESULT_SUCCESS;
	if(clock < HAL_TMR_CLOCK_COUNT){
		uint16_t tickStart, tickNow, diff, wait;
		res |= HAL_TmrGet(clock, &tickStart);
		if(res == HAL_TMR_RESULT_SUCCESS){

			wait = delay;
			if (wait < MAX_TICKS_RT)
			{
				do{
					res |= HAL_TmrGet(clock, &tickNow);
					if (res == HAL_TMR_RESULT_SUCCESS){
						if (tickNow < tickStart){
							diff = MAX_TICKS_RT - tickNow + tickStart;
						} else{
							diff = tickNow - tickStart;
						}
					}else {
						break;
					}
				}while ( diff < wait);
				res = HAL_TMR_RESULT_SUCCESS;
			}
		}
	}
	return res;
}
