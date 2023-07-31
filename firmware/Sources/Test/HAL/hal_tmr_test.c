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
#include "hal_tmr.h"
#include "gpio.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_tmr_test.h"

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
static volatile uint32_t n_ints_pwr_meas = 0, gen_ints = 0;
static uint16_t ticks[N_SAMPLES];
volatile uint32_t n_ints_rt = 0;

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
static HAL_TMR_result_e TestOneTmr(const HAL_TMR_clock_e clock){
	HAL_TMR_result_e res = HAL_TMR_RESULT_SUCCESS;
	uint32_t expect_ints = 0;
	uint16_t offset_ints = 10;

	if (clock == HAL_TMR_CLOCK_RT){
		expect_ints = 10*DELAY_TIME;
		offset_ints = 10;
	}else if (clock == HAL_TMR_CLOCK_PWR_MEAS){
		expect_ints = 100*DELAY_TIME;
		offset_ints = 100;
	}

	if (HAL_TmrStart(clock) !=  HAL_TMR_RESULT_SUCCESS ){
		res = HAL_TMR_RESULT_ERROR;
	} else {

		for(uint8_t i = 0; i< N_SAMPLES; i++){
			HAL_TmrGet(clock, &ticks[i]);
			// Wait until ticks have changed
			while(i>0 && ticks[i] == ticks[i-1]){
				HAL_TmrGet(clock, &ticks[i]);
			}
		}

		n_ints_rt = 0;
		n_ints_pwr_meas = 0;
		HAL_Delay(DELAY_TIME);
		if (clock == HAL_TMR_CLOCK_RT){
			gen_ints = n_ints_rt;
		}else if (clock == HAL_TMR_CLOCK_PWR_MEAS){
			gen_ints = n_ints_pwr_meas;
		}
		res = HAL_TmrStop(clock);

		if(res != HAL_TMR_RESULT_SUCCESS || (gen_ints < expect_ints - offset_ints) || (gen_ints > expect_ints + offset_ints) ){
			res = HAL_TMR_RESULT_ERROR;
		} else {
			n_ints_rt = 98765;
			HAL_Delay(DELAY_TIME);
			if(n_ints_rt != 98765){
				res = HAL_TMR_RESULT_ERROR;
			}
		}
	}
	return res;
}

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

#ifdef EPC_CONF_TESTING
	void HAL_TMR_RT_Callback(void)
	{
		n_ints_rt += 1;
	#ifdef EPC_CONF_GPIO_ENABLED
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
	#endif
	}

	void HAL_TMR_PWR_MEAS_Callback(void)
	{
		n_ints_pwr_meas += 1;
	#ifdef EPC_CONF_GPIO_ENABLED
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	#endif
	}
#endif


HAL_TMR_result_e TestRTTmr(void){
	return TestOneTmr(HAL_TMR_CLOCK_RT);
}

HAL_TMR_result_e TestPwrMeasTmr(void){
	return TestOneTmr(HAL_TMR_CLOCK_PWR_MEAS);
}

