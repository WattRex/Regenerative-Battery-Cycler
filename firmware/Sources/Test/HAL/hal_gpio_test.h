/*********************************************************************************
* @file           : hal_gpio_test.h
* @brief          : HAL header file for GPIO test
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

#ifndef HAL_GPIO_TEST_H_
#define HAL_GPIO_TEST_H_

#include "hal_gpio.h"
/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/

/**********************************************************************************/
/*                    	 Declaration of exported functions                  	  */
/**********************************************************************************/

/**
 * @fn void HAL_GpioTest(HAL_GPIO_output_e pinO, HAL_GPIO_input_e pinI)
 * @brief Writes a HIGH value in the choosen output pin once it has been verified the input pin reads the same,
 * changes the value writen to LOW and verifies again the input reads it.
 * @param pinO GPIO output pin to set.
 * @param pinI GPIO output pin to get.
 * @return @ref HAL_GPIO_RESULT_SUCCESS if initialize correctly,
 * @ref HAL_GPIO_RESULT_ERROR otherwise.
 */
HAL_GPIO_result_e HAL_GpioTest(HAL_GPIO_output_e pinO, HAL_GPIO_input_e pinI);


#endif /* HAL_GPIO_TEST_H_ */
