/*********************************************************************************
* @file           : hal_tmr.c
* @brief          : Implementation of HAL TMR
***********************************************************************************/

/*********************************************************************************
*	
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
*@author           : WattRex <https://github.com/WattRex/>
*@date			   : 2023-07-04
*@version		   : v1.0.0
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "main.h"
#include "hal_gpio.h"
#include "hal_tmr_test.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_wdg_test.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/
#define N_SAMPLES 10
#define DELAY_TIME 1000 // ms

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
static volatile uint32_t rest_ints = 0;
extern volatile uint32_t n_ints_rt;

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

HAL_WDG_result_e TestWdg(void){
	HAL_WDG_result_e res = HAL_WDG_RESULT_SUCCESS;

	uint8_t exp_ints[3] = {1, 2, 7}, stage = 0;
	HAL_GPIO_pin_value_e pin_val = HAL_GPIO_HIGH;
	HAL_GpioSet(HAL_GPIO_OUT_Led2, pin_val);

	// Start timers and refresh whatchdog
	res |= HAL_WdgRefresh();
	if (HAL_TmrStart(HAL_TMR_CLOCK_RT) !=  HAL_TMR_RESULT_SUCCESS){
		while(stage < 3){
			rest_ints = n_ints_rt;
			if (rest_ints >=  exp_ints[stage]){
				// Toggle gpio
				pin_val = 1 - pin_val;
				HAL_GpioSet(HAL_GPIO_OUT_Led2, pin_val);
				stage += 1;
				res |= HAL_WdgRefresh();
			}
		}
	}else{
		res = HAL_WDG_RESULT_ERROR;
	}
	return res;
}

