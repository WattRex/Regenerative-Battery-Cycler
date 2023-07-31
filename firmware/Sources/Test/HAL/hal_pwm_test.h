/*********************************************************************************
* @file           : hal_pwm_test.h
* @brief          : HAL header file for PWM test
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

#ifndef HAL_PWM_TEST_H_
#define HAL_PWM_TEST_H_

#include "hal_pwm.h"
/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/

/**********************************************************************************/
/*                    	 Declaration of exported functions                  	  */
/**********************************************************************************/

/**
 * @fn HAL_PWM_result_e HAL_PwmTest()
 * @brief Sets a duty of the 50% for 5s after that it stops for 2.5s and change the duty to 75% and 25% for 2.5s each and ends.
 * @return @ref HAL_PWM_RESULT_SUCCESS if initialize correctly,
 * @ref HAL_PWM_RESULT_ERROR otherwise.
 */
HAL_PWM_result_e HAL_PwmTest(void);


#endif /* HAL_PWM_TEST_H_ */
