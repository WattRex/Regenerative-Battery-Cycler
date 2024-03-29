/*********************************************************************************
* @file           : hal_gpio_test.c
* @brief          : HAL header file for GPIO TEST
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
#include "hal_gpio_test.h"

#include "main.h"

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
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/


/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/
/**
 * @fn void TestPins(HAL_GPIO_output_e pinO, HAL_GPIO_input_e pinI, HAL_GPIO_pin_value_e value)
 * @brief Writes the value given in the output pin and verifies that the input pin
 * reads the same value as the one writen, using the functions developed.
 * @param pinO GPIO output pin to set.
 * @param pinI GPIO output pin to get.
 * @param value GPIO pin value to write and read.
 * @return @ref HAL_GPIO_RESULT_SUCCESS if initialize correctly,
 * @ref HAL_GPIO_RESULT_ERROR otherwise.
 */
static HAL_GPIO_result_e TestPins(HAL_GPIO_output_e pinO, HAL_GPIO_input_e pinI, HAL_GPIO_pin_value_e value)
{
	HAL_GPIO_pin_value_e Ivalue;
	HAL_GPIO_result_e res = HAL_GPIO_RESULT_ERROR;
	if (HAL_GpioSet(pinO, value) == HAL_GPIO_RESULT_SUCCESS)
	{
		if (HAL_GpioGet(pinI, &Ivalue) == HAL_GPIO_RESULT_SUCCESS)
		{
			if (value == Ivalue)
			{
				res = HAL_GPIO_RESULT_SUCCESS;
			}
		}
	}
	return res;
}
/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

HAL_GPIO_result_e HAL_GpioTest(HAL_GPIO_output_e pinO, HAL_GPIO_input_e pinI)
{
	HAL_GPIO_result_e res = HAL_GPIO_RESULT_SUCCESS;
	/* Check if the pins are in the list of inputs and outputs*/
	if  (pinO>=HAL_GPIO_OUT_COUNT || pinI>=HAL_GPIO_IN_COUNT){
		res = HAL_GPIO_RESULT_ERROR;
	}else {

		/* Check if the Output pin is able to change to HIGH and the Input read it*/
		if (TestPins(pinO, pinI, HAL_GPIO_HIGH) == HAL_GPIO_RESULT_ERROR){
			res = HAL_GPIO_RESULT_ERROR;
		}
		HAL_Delay(125);
		/* Check if the Output pin is able to change to LOW and the Input read it*/
		if (TestPins(pinO, pinI, HAL_GPIO_LOW) == HAL_GPIO_RESULT_ERROR){
			res = HAL_GPIO_RESULT_ERROR;
		}

	}

	return res;
}
