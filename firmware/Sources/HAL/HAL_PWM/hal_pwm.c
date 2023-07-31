/*********************************************************************************
* @file           : hal_pwm.c
* @brief          : Implementation of HAL PWM
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
#include "stm32f3xx_hal.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_pwm.h"
#include "hrtim.h"
#include "epc_st_err.h" //Import EPC_ST_ERR_COUNTER
/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include <stdint.h>

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
static HRTIM_CompareCfgTypeDef pCompareCfg = {0};
uint32_t * max_steps;
/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/
uint32_t HAL_PWM_period;
/**********************************************************************************/
/*                        Definition of imported variables                        */
/**********************************************************************************/
extern HRTIM_HandleTypeDef hhrtim1;
extern uint8_t EPC_ST_ERR_COUNTER;
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

HAL_PWM_result_e HAL_PwmInit(void){
	HAL_PWM_result_e res = HAL_PWM_RESULT_ERROR;
	EPC_ST_ERR_COUNTER = 0;
	MX_HRTIM1_Init();
	if (EPC_ST_ERR_COUNTER==0){
		HAL_PWM_period = (hhrtim1.Instance->sTimerxRegs[0].PERxR);

		res = HAL_PWM_RESULT_SUCCESS;
	}
	return res;
}


HAL_PWM_result_e HAL_PwmSetDuty(const uint32_t duty){
	// Get the period of the timer, as will be the maximum value to compare

	uint32_t pwm_duty;
	if (duty>=HAL_PWM_period){
		// The maximum duty to apply is the period configured -1
		pwm_duty = HAL_PWM_period -1;

	}
	//If duty between max and min values
	else if (duty>=HAL_PWM_MIN_PWM){
		pwm_duty = duty;
	}
	else{
		// Minimum duty to apply to the pwm is 96 by hardware with the actual configuration.
		pwm_duty = HAL_PWM_MIN_PWM;
	}
	
	// Write the value to compare in the register.
	pCompareCfg.CompareValue = pwm_duty;
//	pCompareCfg.CompareValue = 5007;
	// Apply the compare configuration to the dessire timer unit in this case HRTIM-A1
	HAL_PWM_result_e res = HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1, &pCompareCfg);;
	return res;
}

HAL_PWM_result_e HAL_PwmStart (void){

	HAL_PWM_result_e res = HAL_PWM_RESULT_ERROR;
	res = HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_TIMER_A);
	if (res == HAL_PWM_RESULT_SUCCESS){
		res = HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1);
	}
	return res;
}

HAL_PWM_result_e HAL_PwmStop (void){
	HAL_PWM_result_e res = HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1);
	return res;
}
