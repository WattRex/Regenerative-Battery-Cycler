/*********************************************************************************
* @file           : hal_pwm.c
* @brief          : Implementation of HAL PWM
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "stm32f3xx_hal.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_pwm.h"
#include "hrtim.h"
#include "epc_st_err.h" //Import EPC_ST_ERR_COUNTER
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
static HRTIM_CompareCfgTypeDef pCompareCfg = {0};
/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/
extern HRTIM_HandleTypeDef hhrtim1;

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

HAL_PWM_result_e HAL_PwmInit(void){
	HAL_PWM_result_e res = HAL_PWM_RESULT_SUCCESS;
	EPC_ST_ERR_COUNTER = 0;
	MX_HRTIM1_Init();
	if (EPC_ST_ERR_COUNTER){
		res = HAL_PWM_RESULT_ERROR;
	}
	return res;
}


HAL_PWM_result_e HAL_PwmSetDuty(const uint32_t duty){
	uint32_t max = hhrtim1.Instance->sTimerxRegs[0].PERxR;
	uint32_t pwm_duty;
	if (duty>100000){
		pwm_duty = 9215;
	}
	else{
		pwm_duty = duty * max/100000 - 1;
	}
	if (pwm_duty < 96 || pwm_duty>9215){
		pwm_duty = 96;
	}
	pCompareCfg.CompareValue = pwm_duty;
	HAL_PWM_result_e res = HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1, &pCompareCfg);;
	return res;
}

HAL_PWM_result_e HAL_PwmStart (void){

	HAL_PWM_result_e res = HAL_PWM_RESULT_ERROR;
	res = HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_TIMER_A);
	if (res == HAL_PWM_RESULT_SUCCESS){
		res = HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1);
	}
	return res;
}

HAL_PWM_result_e HAL_PwmStop (void){
	HAL_PWM_result_e res = HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1);
	return res;
}
