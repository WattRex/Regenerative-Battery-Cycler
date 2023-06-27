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
#define MIN_PWM 96
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
uint32_t HAL_PWM_period;
/**********************************************************************************/
/*                        Definition of imported variables                        */
/**********************************************************************************/
extern HRTIM_HandleTypeDef hhrtim1;
extern uint8_t EPC_ST_ERR_COUNTER;
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
	HAL_PWM_result_e res = HAL_PWM_RESULT_ERROR;
	EPC_ST_ERR_COUNTER = 0;
	MX_HRTIM1_Init();
	if (EPC_ST_ERR_COUNTER==0){
		HAL_PWM_period = (hhrtim1.Instance->sTimerxRegs[0].PERxR);
		res = HAL_PWM_RESULT_SUCCESS;
	}
	return res;
}


HAL_PWM_result_e HAL_PwmSetDuty(const uint32_t duty){
	// Get the period of the timer, as will be the maximum value to compare
	uint32_t pwm_duty;
	if (duty>=HAL_PWM_period){
		// The maximum duty to apply is the period configured -1
		pwm_duty = HAL_PWM_period -1;
	}
	//If duty between max and min values
	else if (duty>=MIN_PWM){
		pwm_duty = duty;
	}
	else{
		// Minimum duty to apply to the pwm is 96 by hardware with the actual configuration.
		pwm_duty = MIN_PWM;
	}
	
	// Write the value to compare in the register.
	pCompareCfg.CompareValue = pwm_duty;
	// Apply the compare configuration to the dessire timer unit in this case HRTIM-A1
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
