/*********************************************************************************
* @file           : hal_tmr_test.h
* @brief          : HAL header file for timers test
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

#ifndef HAL_TMR_TEST_H_
#define HAL_TMR_TEST_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "hal_tmr.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of exported types (typedef, enum, struct, union)         */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/
extern volatile uint32_t n_ints_rt;

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                   Declaration of exported function prototypes                  */
/**********************************************************************************/


/**
 * @fn HAL_TMR_result_e TestRTTmr(void)
 * @brief Start the RT timer and uses the HAL_TmrGet to get multiple samples in order
 * to check that it works correctly. It must be incremental measures or overflow.
 * After waits 1000ms and count the generated interrupts
 * @note: If GPIO is used, toggle pin PA9
 * @param Delay specifies the delay time length, in milliseconds.
 * @return @ref HAL_TMR_RESULT_SUCCESS if test is passed,
 * @ref HAL_TMR_RESULT_ERROR otherwise.
 */
HAL_TMR_result_e TestRTTmr(void);

/**
 * @fn HAL_TMR_result_e TestPwrMeasTmr(void)
 * @brief Start the PwrMeas timer and uses the HAL_TmrGet to get multiple samples in order
 * to check that it works correctly. It must be incremental measures or overflow.
 * After waits 1000ms and count the generated interrupts
 * @note: If GPIO is used, toggle pin PB0
 * @param Delay specifies the delay time length, in milliseconds.
 * @return @ref HAL_TMR_RESULT_SUCCESS if test is passed,
 * @ref HAL_TMR_RESULT_ERROR otherwise.
 */
HAL_TMR_result_e TestPwrMeasTmr(void);
#endif /* HAL_TMR_TEST_H_ */
