/*********************************************************************************
* @file           : hal_pwm_test.c
* @brief          : Implementation for HAL PWM TEST
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


/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_pwm_test.h"
#include "stm32f3xx_hal.h"
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

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of imported variables                        */
/**********************************************************************************/
extern uint32_t HAL_PWM_period;

/**********************************************************************************/
/*                      Definition of exported constant data                      */
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

HAL_PWM_result_e HAL_PwmTest(void)
{
	HAL_PWM_result_e res = HAL_PWM_RESULT_ERROR;
	uint32_t duty= HAL_PWM_period/2; // Duty at 50%
	
	if (HAL_PwmSetDuty(duty)==HAL_PWM_RESULT_SUCCESS){
		res = HAL_PwmStart();
		if (res == HAL_PWM_RESULT_SUCCESS){
			HAL_Delay(5000);
			res = HAL_PwmStop();
			if (res == HAL_PWM_RESULT_SUCCESS){
				HAL_Delay(2500);
				duty =  HAL_PWM_period *3/4; // Duty 75%
				res = HAL_PwmSetDuty(duty);
				if (res == HAL_PWM_RESULT_SUCCESS){
					res =HAL_PwmStart();
					HAL_Delay(2500);
					if (res == HAL_PWM_RESULT_SUCCESS){
						duty =  HAL_PWM_period /4; // Duty 25%
						res = HAL_PwmSetDuty(duty);
						HAL_Delay(2500);
						if (res == HAL_PWM_RESULT_SUCCESS){
							res = HAL_PwmStop();
						}
					}
				}
			}
		}
	}
	return res;
}
