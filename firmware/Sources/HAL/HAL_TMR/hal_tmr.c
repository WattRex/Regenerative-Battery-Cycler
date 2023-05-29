/*********************************************************************************
* @file           : hal_tmr.c
* @brief          : Implementation of HAL TMR
**********************************************************************************
* @attention
* Research Laboratory in Fluid Dynamics and Combustion Technologies (LIFTEC)
*   Spanish National Research Council (CSIC)
*   c/ María de Luna 10, 50018 Zaragoza, Spain
*
*   All rights reserved. Distribution or duplication without previous
*   written agreement of the owner prohibited.
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "main.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_tmr.h"
#include "tim.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/
#define MAX_TICKS_RT 1000
/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/
/** Pointers to callback used for timers IT **/
typedef  void (*_Tmr_pCallback_t)();

/**
 * @struct HAL_TMR_config_t
 * @brief Struct used to store timer handler and callback IT pointer.
 */
typedef struct{
	TIM_HandleTypeDef * Handler;	/**< Timer Handler **/
	_Tmr_pCallback_t CallbackITHandler; /**< Pointer to the callback invoked on IT **/
}_Tmr_config_t;

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
/** Array with a @ref HAL_TMR_config_t struct for each available timer **/
static _Tmr_config_t _htim[HAL_TMR_CLOCK_COUNT];

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/

/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

__weak void HAL_TMR_TIM2_Callback(void){}

/**
 * @fn void TIM2_IRQHandler(void)
 * @brief First IT routine invoked when the timer 2 counter overflows. It clears the
 * overflow flags and invoke the user defined callback.
 */
//void TIM2_IRQHandler(void)
//{
//	TIM_HandleTypeDef *handler = &_htim[HAL_TMR_CLOCK_RT].Handler;
//	/** @arg TIM Update event **/
//	if (__HAL_TIM_GET_FLAG(handler, TIM_FLAG_UPDATE) != RESET)
//	{
//		if (__HAL_TIM_GET_IT_SOURCE(handler, TIM_IT_UPDATE) != RESET)
//		{
//			__HAL_TIM_CLEAR_IT(handler, TIM_IT_UPDATE);
//			/** @arg Run custom IT callback **/
//			_htim[HAL_TMR_CLOCK_RT].CallbackITHandler();
//		}
//	}
//}

HAL_TMR_result_t HAL_TmrInit (const HAL_TMR_clock_t clock){
	HAL_TMR_result_t res = HAL_TMR_RESULT_SUCCESS;
	switch (clock){
		case HAL_TMR_CLOCK_RT:
			_htim[HAL_TMR_CLOCK_RT].Handler = &htim2;
			error_raised = 0;
			MX_TIM2_Init();
			if (error_raised){
				res = HAL_TMR_RESULT_ERROR;
			}
			break;
		case HAL_TMR_CLOCK_PWR_MEAS:
			_htim[HAL_TMR_CLOCK_PWR_MEAS].Handler = &htim3;
			error_raised = 0;
			MX_TIM3_Init();
			if (error_raised){
				res = HAL_TMR_RESULT_ERROR;
			}
			break;
		default:
			break;
	}
	return res;
}

HAL_TMR_result_t HAL_TmrStart (const HAL_TMR_clock_t clock){
	HAL_TMR_result_t res = HAL_TMR_RESULT_ERROR;
	if(clock < HAL_TMR_CLOCK_COUNT){
		res = HAL_TIM_Base_Start_IT(_htim[clock].Handler);
	}
	return res;
}

HAL_TMR_result_t HAL_TmrStop (const HAL_TMR_clock_t clock){
	HAL_TMR_result_t res = HAL_TMR_RESULT_ERROR;
	if(clock < HAL_TMR_CLOCK_COUNT){
		res = HAL_TIM_Base_Stop_IT(_htim[clock].Handler);
	}
	return res;
}

HAL_TMR_result_t HAL_TmrGet (const HAL_TMR_clock_t clock, uint16_t *value){
	HAL_TMR_result_t res = HAL_TMR_RESULT_ERROR;
	if(clock < HAL_TMR_CLOCK_COUNT){
		*value = __HAL_TIM_GET_COUNTER(_htim[clock].Handler);
	}
	return res;
}

HAL_TMR_result_t HAL_TmrDelay(const HAL_TMR_clock_t clock, const uint16_t delay){
	HAL_TMR_result_t res = HAL_TMR_RESULT_ERROR;
	if(clock == HAL_TMR_CLOCK_RT){
		uint16_t tickStart, tickNow, diff, wait;
		HAL_TmrGet(clock, &tickStart);
		wait = delay;
//		wait *= 10;

		if (wait < MAX_TICKS_RT)
		{
			do{
				HAL_TmrGet(clock, &tickNow);
				if (tickNow < tickStart){
					diff = MAX_TICKS_RT - tickNow + tickStart;
				} else{
					diff = tickNow - tickStart;
				}
			}while ( diff < wait);
			res = HAL_TMR_RESULT_SUCCESS;
		}
	}
	return res;
}
