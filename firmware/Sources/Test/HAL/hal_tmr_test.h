/*********************************************************************************
* @file           : hal_tmr_test.h
* @brief          : HAL header file for timers test
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
 * @brief Start the RT timer and uses the HAL_TmrGet to get multiple samples in order
 * to check that it works correctly. It must be incremental measures or overflow.
 * After waits 1000ms and count the generated interrupts
 * @note: If GPIO is used, toggle pin PB0
 * @param Delay specifies the delay time length, in milliseconds.
 * @return @ref HAL_TMR_RESULT_SUCCESS if test is passed,
 * @ref HAL_TMR_RESULT_ERROR otherwise.
 */
HAL_TMR_result_e TestPwrMeasTmr(void);
#endif /* HAL_TMR_TEST_H_ */
