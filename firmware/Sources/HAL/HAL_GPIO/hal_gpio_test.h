/*
 * TestingGpio.h
 *
 *  Created on: 25 may. 2023
 *      Author: Roberto Aldea
 */

#ifndef TESTINGGPIO_H_
#define TESTINGGPIO_H_

#include "hal_gpio.h"
/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/
HAL_GPIO_result_e TestPins(HAL_GPIO_output_e pinO, HAL_GPIO_input_e pinI, HAL_GPIO_pin_value_e value);
/**********************************************************************************/
/*                    	 Declaration of exported functions                  	  */
/**********************************************************************************/
HAL_GPIO_result_e HAL_GPIO_Test(HAL_GPIO_output_e pinO, HAL_GPIO_input_e pinI);


#endif /* TESTINGGPIO_H_ */
