/*********************************************************************************
* @file            : hal_pwm.h
* @brief           : Header file for Hardware Abstraction Layer (HAL) of the PWM
* (Pulse Width Modulation). Provides functions for initializing the PWM, setting
* PWM  duty cycle, starting, and stopping   the  PWM  waveform  using  the HRTIM
* (High-Resolution Timer).
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

#ifndef HAL_PWM_H_
#define HAL_PWM_H_
/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include <stdint.h>
/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/
#define HAL_PWM_MIN_PWM 96 
/* This value depends on the prescaler of the HRTIM, go to documentation for more info */ 

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of exported types (typedef, enum, struct, union)         */
/**********************************************************************************/

/**
 * @enum HAL_PWM_result_e
 * @brief Structure for the result of the PWM operation.
 */
typedef enum
{
	HAL_PWM_RESULT_SUCCESS = 0x0U, /**< HAL_PWM success operation result **/
	HAL_PWM_RESULT_ERROR, 			/**< HAL_PWM error operation result **/
	HAL_PWM_RESULT_BUSY,			/**< HAL_PWM Busy operation result **/
	HAL_PWM_RESULT_TIMEOUT			/**< HAL_PWM timeout operation result **/

}HAL_PWM_result_e;

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/
extern uint32_t HAL_PWM_period;
/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/
#define HAL_PWM_MAX_DUTY 100000 //steps of duty
/**********************************************************************************/
/*                   Declaration of exported function prototypes                  */
/**********************************************************************************/

/**
 * @fn HAL_PWM_result_e HAL_PwmInit(void)
 * @brief Configures the PWM
 * @return @ref HAL_PWM_RESULT_SUCCESS if initialize correctly,
 * @ref HAL_PWM_RESULT_ERROR otherwise.
 */
HAL_PWM_result_e HAL_PwmInit(void);


/**
 * @fn HAL_PWM_result_e HAL_PwmSetDuty(const uint32_t duty)
 * @brief Set the pwm duty, it has to be a value between 0 and 255
 *
 * @param duty Duty of the PWM.
 * @return @ref HAL_PWM_RESULT_SUCCESS if the assignment was correctly,
 * @ref HAL_PWM_RESULT_ERROR otherwise.
 */
HAL_PWM_result_e HAL_PwmSetDuty(const uint32_t duty);


/**
 * @fn HAL_PWM_result_e HAL_PwmStart (void)
 * @brief Start the pwm output
 *
 * @return @ref HAL_PWM_RESULT_SUCCESS if the pwm has started correctly,
 * @ref HAL_PWM_RESULT_ERROR otherwise.
 */
HAL_PWM_result_e HAL_PwmStart (void);


/**
 * @fn HAL_PWM_result_e HAL_PwmStop (void)
 * @brief Stop the pwm output
 *
 * @return @ref HAL_PWM_RESULT_SUCCESS if the pwm has started correctly,
 * @ref HAL_PWM_RESULT_ERROR otherwise.
 */
HAL_PWM_result_e HAL_PwmStop (void);
#endif /* HAL_PWM_H_ */
