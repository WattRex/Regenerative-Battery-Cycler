/*********************************************************************************
* @file           : mid_pwr.c
* @brief          : Implementation of MID_PWR
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "hal_pwm.h"
#include "hal_gpio.h"
#include "epc_conf.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "mid_pwr.h"
#include "mid_reg.h"

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
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/
typedef enum{
	pi_CC = 0x0u,
	pi_CV,
	pi_CP
}pi_select_e;

typedef enum{
	SOA_save = 0x0u,
	SOA_up,
	SOA_down
}SOA_e;
/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/
static MID_PWR_result_e _calculatePI(const uint16_t ref, const uint16_t meas, const pi_select_e mode, const MID_REG_limit_s limits, uint16_t * action);

static SOA_e _checkSOA(const int16_t I, const uint16_t V, const XXX limits);
/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
static uint16_t kp_values = {800,0,0}, ki_values = {500,0,0};
static int32_t integral_values = {0, 0, 0};
static uint8_t saturado_values = {0,0,0};
static uint32_t duty, d0;
/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/
/**********************************************************************************/
/*                        Definition of imported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/

static SOA_e _checkSOA(const int16_t I, const uint16_t V, const MID_REG_limit_s limits){
	SOA_e res = SOA_save;
	int32_t power = I * V;
	if (power > limits.lsPwrMax)
		res = SOA_up;
	else if (power < limits.lsPwrMin)
		res = SOA_down;
	return res;
}

/**
 * @fn MID_PWR_result_t SetLeds()
 * @brief Set the leds to the state indicated by the input
 * @param state, 8bit input but only needed the last 4 bits as there are only 4 leds
 * @return @ref MID_PWR_RESULT_SUCCESS if measured correctly,
 * 		@ref MID_PWR_RESULT_BUSY, @ref MID_PWR_RESULT_TIMEOUT or
 * 		@ref MID_PWR_RESULT_ERROR otherwise.
 */
static MID_PWR_result_e _calculatePI(const uint16_t ref, const uint16_t meas, const pi_select_e mode, const MID_REG_limit_s limits, uint16_t * action){
	// Get values for the specific PI 
	uint8_t saturado = saturado_values[mode];
	uint16_t kp = kp_values[mode], ki = ki_values[mode];
	uint32_t integral = integral_values[mode];
	uint16_t up_limit, low_limit;
	if (mode != pi_CC){
		up_limit = limits.lsCurrMax ;
		low_limit= limits.lsCurrMin ;
	}else{
		up_limit = 100000-d0;
		low_limit= 0+d0;
	}
	MID_PWR_result_e res = MID_PWR_RESULT_ERROR;
	int32_t error = ref - meas;
	if(saturado){
		integral += error;
	}
	*action = kp * error + ki* integral;

	if(*action >= up_limit){
		*action = up_limit;
		saturado = 1;
	}else if(*action <= low_limit){
		*action = low_limit;
		saturado = 1;
	}else{
		saturado = 0;
	}
	//Reasign the values calculated
	saturado_values[mode] = saturado;
	integral_values[mode] = integral;
	return res;
}

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

MID_PWR_result_e MID_PwrSetOutput(const MID_PWR_Output_e outputMode){
	MID_PWR_result_e res = MID_PWR_RESULT_ERROR;
	return res;
}

MID_PWR_result_e MID_PwrApplyPI(const int16_t ref, const uint16_t V_LS, const int16_t I_LS, const MID_PWR_Control_Mode_e control_mode, const MID_REG_limit_s limits){
	MID_PWR_result_e res = MID_PWR_RESULT_ERROR;
	uint16_t action, new_duty;
	int32_t actual_power;
	switch (control_mode)
	{
	case MID_PWR_Control_Mode_CP:
		actual_power = V_LS * I_LS;
		res = _calculatePI(ref, actual_power, pi_CP, limits, &action);
		break;
	case MID_PWR_Control_Mode_CV:
		res = _calculatePI(ref, V_LS, pi_CV, limits, &action);
		break;
	case MID_PWR_Control_Mode_CC:
		action = ref;
		res = MID_PWR_RESULT_SUCCESS;
		break;
	}
	if (res == MID_PWR_RESULT_SUCCESS){
		if (_checkSOA(action, V_LS, limits) == SOA_up || action > limits.imax){
			action = limits.lsCurrMax;
		}
		else if (_checkSOA(action, V_LS, limits) == SOA_down || action > limits.imin){
			action = limits.lsCurrMin;
		}
		res = _calculatePI(action, I_LS, pi_CC, limits, &new_duty);
		if (res == MID_PWR_RESULT_SUCCESS){
			duty = new_duty + d0;
			res = (MID_PWR_result_e) HAL_PwmSetDuty(duty);
		}
	}

	return res;
}

MID_PWR_result_e MID_PwrCalculateD0(const uint16_t V_HS, const uint16_t V_LS){
	MID_PWR_result_e res = MID_PWR_RESULT_ERROR;
	uint32_t actual_d0 = V_LS *1000/ V_HS;
	if (actual_d0<=100000 && actual_d0>=0){
		d0 = actual_d0;
		res = MID_PWR_RESULT_SUCCESS;
	}
	return res;
}