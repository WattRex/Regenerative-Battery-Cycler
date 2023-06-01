/*********************************************************************************
* @file           : hal_gpio_test.h
* @brief          : HAL header file for GPIO test
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
