/*********************************************************************************
* @file           : hal_pwm_test.h
* @brief          : HAL header file for PWM test
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
