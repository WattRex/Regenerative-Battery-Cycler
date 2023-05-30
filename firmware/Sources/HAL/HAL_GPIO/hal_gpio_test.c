/*
 * TestingGpio.c
 *
 *  Created on: 25 may. 2023
 *      Author: Roberto Aldea
 */
/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/


/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_gpio.h"
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
HAL_GPIO_result_e TestPins(HAL_GPIO_output_e pinO, HAL_GPIO_input_e pinI, HAL_GPIO_pin_value_e value)
{
	HAL_GPIO_pin_value_e Ivalue;
	HAL_GPIO_result_e res = HAL_GPIO_RESULT_ERROR;
	if (HAL_GpioSet(pinO, value) == HAL_GPIO_RESULT_SUCCESS)
	{
		if (HAL_GpioGet(pinI, &Ivalue) == HAL_GPIO_RESULT_SUCCESS)
		{
			if (value == Ivalue)
			{
				return HAL_GPIO_RESULT_SUCCESS;
			}
		}
	}
	return res;
}
/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

HAL_GPIO_result_e HAL_GPIO_Test(HAL_GPIO_output_e pinO, HAL_GPIO_input_e pinI)
{
	/* Check if the pins are in the list of inputs and outputs*/
	if  (pinO>=HAL_GPIO_OUT_COUNT | pinO>=HAL_GPIO_IN_COUNT)
		{
		return HAL_GPIO_RESULT_ERROR;
		}
	/* Check if the Output pin is able to change to HIGH and the Input read it*/
	if (TestPins(pinO, pinI, HAL_GPIO_HIGH) == HAL_GPIO_RESULT_ERROR){
		return HAL_GPIO_RESULT_ERROR;
	}
	HAL_Delay(125);
	/* Check if the Output pin is able to change to LOW and the Input read it*/
	if (TestPins(pinO, pinI, HAL_GPIO_LOW) == HAL_GPIO_RESULT_ERROR){
		return HAL_GPIO_RESULT_ERROR;
	}
	return HAL_GPIO_RESULT_SUCCESS;
}
