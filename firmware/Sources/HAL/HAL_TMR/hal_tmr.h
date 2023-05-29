/*********************************************************************************
* @file           : hal_tmr.h
* @brief          : HAL header file for timers
**********************************************************************************
* @attention
* Research Laboratory in Fluid Dynamics and Combustion Technologies (LIFTEC)
*   Spanish National Research Council (CSIC)
*   c/ María de Luna 10, 50018 Zaragoza, Spain
*
*   All rights reserved. Distribution or duplication without previous
*   written agreement of the owner prohibited.
***********************************************************************************/
#ifndef HAL_TMR_H_
#define HAL_TMR_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include "stdint.h"

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of exported types (typedef, enum, struct, union)         */
/**********************************************************************************/

/**
 * @enum HAL_TMR_result_t
 * @brief Structure for the result of the TMR operation.
 */
typedef enum
{
	HAL_TMR_RESULT_SUCCESS 	= 0x00U,	/**< HAL_TMR success operation result **/
	HAL_TMR_RESULT_ERROR   	= 0x01U,	/**< HAL_TMR error operation result **/
	HAL_TMR_RESULT_BUSY			= 0x02U,	/**< HAL_TMR busy operation result **/
	HAL_TMR_RESULT_TIMEOUT	= 0x03U,	/**< HAL_TMR timeout operation result **/
}HAL_TMR_result_t;

/**
 * @enum HAL_TMR_clock_t
 * @brief Structure with the available timers.
 */
typedef enum
{
	HAL_TMR_CLOCK_RT = 0x00U,				/**< HAL_TMR Timer 2 used for real time tasks **/
	HAL_TMR_CLOCK_PWR_MEAS = 0x01U,	/**< HAL_TMR Timer 3 used to trigger ADC measures **/
	HAL_TMR_CLOCK_HR = 0x02U,				/**< HAL_TMR High resolution **/
	HAL_TMR_CLOCK_COUNT
}HAL_TMR_clock_t;

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

/** */
/**
 * @fn void HAL_TMR_TIM2_Callback(void)
 * @brief Callback function invoked when a timer 2 interrupt occurs due to counter overflow.
 * User must implement this function for for customized operation.
 */
void HAL_TMR_TIM2_Callback(void);

/**
 * @fn HAL_TMR_result_t HAL_TmrInit(HAL_TMR_clock_t, HAL_TMR_pCallback_t)
 * @brief Initializes the configured clocks using the manufacturer provided functions.
 * Register an user callback to be used instead of the weak predefined callback
 *
 * @param clock Identifier of the timer to be initialized
 * @param pCallback Pointer to the callback function. If pCallback is NULL no callback
 * will be invoked on IT.
 * @return
 * 		@ref HAL_TMR_RESULT_SUCCESS if initialized correctly,
 * 		@ref HAL_TMR_RESULT_ERROR otherwise
 */
HAL_TMR_result_t HAL_TmrInit (const HAL_TMR_clock_t clock);

/**
 * @fn HAL_TMR_result_t HAL_TmrStart(HAL_TMR_clock_t)
 * @brief Starts the selected timer and enable IT if appropriate.
 *
 * @param clock  selected timer
 * @return @ref HAL_TMR_RESULT_SUCCESS if started correctly,
 * @ref HAL_TMR_RESULT_ERROR otherwise
 */
HAL_TMR_result_t HAL_TmrStart (const HAL_TMR_clock_t clock);

/**
 * @fn HAL_TMR_result_t HAL_TmrStop(HAL_TMR_clock_t)
 * @brief Stop the selected timer and disable IT if appropriate.
 *
 * @param clock selected timer
 * @return @ref HAL_TMR_RESULT_SUCCESS if stopped correctly,
 * @ref HAL_TMR_RESULT_ERROR otherwise
 */
HAL_TMR_result_t HAL_TmrStop (const HAL_TMR_clock_t clock);

/**
 * @fn HAL_TMR_result_t HAL_TmrGet(HAL_TMR_clock_t, uint16_t*)
 * @brief Read the number of ticks counted by the timer from
 * the last re/start or overflow interrupt.
 *
 * @param clock selected timer
 * @param value pointer to the timer ticks
 * @return @ref HAL_TMR_RESULT_SUCCESS if started correctly,
 * @ref HAL_TMR_RESULT_ERROR otherwise
 */
HAL_TMR_result_t HAL_TmrGet (const HAL_TMR_clock_t clock, uint16_t *value);

/**
 * @fn HAL_TMR_result_t HAL_TmrDelay(const HAL_TMR_clock_t, const uint32_t)
 * @brief This function provides minimum delay (>>>> in 0.1 milliseconds <<<<) based
 *        on variable incremented.
 * @note In the default implementation , SysTick timer is the source of time base.
 *       It is used to generate interrupts at regular time intervals where uwTick
 *       is incremented.
 * @param Delay specifies the delay time length, in milliseconds.
 * @return @ref HAL_TMR_RESULT_SUCCESS if delay applied correctly,
 * @ref HAL_TMR_RESULT_ERROR otherwise.
 */
HAL_TMR_result_t HAL_TmrDelay(const HAL_TMR_clock_t clock, const uint16_t delay);

#endif /* HAL_TMR_H_ */ 
