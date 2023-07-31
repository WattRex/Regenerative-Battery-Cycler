/*********************************************************************************
* @file           : mid_pwr.c
* @brief          : Implementation of MID_PWR
***********************************************************************************/

/*********************************************************************************
*	
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
*@author           : WattRex <https://github.com/WattRex/>
*@date			   : 2023-07-04
*@version		   : v1.0.0
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
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/

typedef enum{
	SOA_ok = 0x0u,
	SOA_over_pwr,
	SOA_under_pwr
}SOA_e;

typedef int32_t fp_t;
/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/
#define _FP_FACTOR (1 << EPC_CONF_FP_N_FRAC_BITS)
#define _SCALING_FACTOR_MILIS 1000
#define _SCALING_FACTOR_DECIS 10


/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/
// reference: http://www.sunshine2k.de/articles/coding/fp/sunfp.html#ch42
/**
 * @fn dSI_to_FP(value)
 * @brief Converts the value given in deciUnits to the fixed point specified and return it.
 * @param value, Value in deciunits
 */
#define dSI_to_FP(value) ((fp_t) value * _FP_FACTOR / _SCALING_FACTOR_DECIS)
/**
 * @fn mSI_to_FP(value)
 * @brief Converts the value given in miliUnits to the fixed point specified
 * @param value, Value in miliunits
 */
#define mSI_to_FP(value) ((fp_t) value * _FP_FACTOR / _SCALING_FACTOR_MILIS)

/**
 * @fn sum_to_FP(sum1,sum2)
 * @brief Make the sum of 2 values in fixed point, return the result in fp
 * @param sum1, first operand
 * @param sum2, second operand
 */
#define sum_FP(sum1,sum2) (sum1 + sum2)
/**
 * @fn sub_FP(sub1,sub2) 
 * @brief Make the difference of 2 values in fixed point, return the result in fp
 * @param sub1, first operand
 * @param sub2, second operand
 */
#define sub_FP(sub1,sub2) (sub1 - sub2)
/**
 * @fn mul_FP(fac1,fac2)
 * @brief Make the multiplication of 2 values in fixed point, return the result in fp
 * @param fac1, first operand
 * @param fac2, second operand
 */
#define mul_FP(fac1,fac2) ((fp_t)(((int64_t)(fac1) * (int64_t)(fac2)>>EPC_CONF_FP_N_FRAC_BITS)))

/**
 * @fn FP_to_mSI(value)
 * @brief Converts the value given in fixed point to miliUnits
 * @param value, Value in miliunits
 */
#define FP_to_mSI(value) ((int16_t) ( (int64_t)(value) * _SCALING_FACTOR_MILIS >> EPC_CONF_FP_N_FRAC_BITS))
/**
 * @fn FP_to_dSI(value)
 * @brief Converts the value given in fixed point to deciUnits
 * @param value, Value in miliunits
 */
#define FP_to_dSI(value) ((int16_t) ( (int64_t)(value) * _SCALING_FACTOR_DECIS >> EPC_CONF_FP_N_FRAC_BITS))
/**
 * @fn FP_to_SI(value)
 * @brief Converts the value given in fixed point to Units
 * @param value, Value in miliunits
 */
#define FP_to_SI(value)  ((int16_t) ( (int64_t)(value) >> EPC_CONF_FP_N_FRAC_BITS))

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/
extern uint32_t HAL_PWM_period;
/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/

/**
 * @fn static MID_PWR_result_e _calculatePI(const int16_t ref, const int16_t meas, const MID_PWR_Mode_e mode,
		const MID_REG_limit_s limits, int32_t * action)
 * @brief Apply a specefic PI, 
 * @param ref, value to have as reference
 * @param meas, value measured from sensor
 * @param mode, type of PI to apply
 * @param limits, limits to use in the PI
 * @param action_res, pointer to the action to apply
 * @return @ref MID_PWR_RESULT_SUCCESS if calculated correctly,
 * 		@ref MID_PWR_RESULT_BUSY, @ref MID_PWR_RESULT_TIMEOUT or
 * 		@ref MID_PWR_RESULT_ERROR otherwise.
 */
static MID_PWR_result_e _calculatePI(const int16_t ref, const int16_t meas,
		const MID_PWR_Mode_e mode, const MID_REG_limit_s limits, int16_t * action_res);

/**
 * @fn static SOA_e _checkSOA(const int16_t I, const uint16_t V, const MID_REG_limit_s limits)
 * @brief Check the device is working under the safe operating area, all the measures must refer to the low side of the EPC.
 * @param I, Value of the current.
 * @param V, Value of the voltage
 * @param limits, register in which are stored the maximum and minimum values of power. 
 * @return @ref SOA_ok if not traspassing the limits,
 * 		@ref SOA_over_pwr, the upper limit has been surpassed.
 * 	 	@ref SOA_under_pwr, the lower limit has been surpassed.
 */
static SOA_e _checkSOA(const int16_t I, const uint16_t V, const MID_REG_limit_s limits);

/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/
#define Q16_SCALE_FACTOR 65536 // 2^16
/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
static fp_t  last_error[3] = {0, 0, 0}; //I, V, P PI values
static fp_t  integral[3] = {0, 0, 0}; //I, V, P PI values
static uint16_t duty, d0 = 0; //action duty goes from 0 to 9215

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of imported variables                        */
/**********************************************************************************/
extern uint32_t HAL_PWM_period;
/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/

static SOA_e _checkSOA(const int16_t I, const uint16_t V, const MID_REG_limit_s limits){
	SOA_e res = SOA_ok;
	int16_t power = (int16_t)(((int32_t)I * (int32_t)V) /MID_PWR_TO_dW); // 10^-3(mW) *10^-3 (mW) / 10^-5 -> dW
	if (power > limits.lsPwrMax)
		res = SOA_over_pwr;
	else if (power < limits.lsPwrMin)
		res = SOA_under_pwr;
	return res;
}

static MID_PWR_result_e _calculatePI(const int16_t ref, const int16_t meas, const MID_PWR_Mode_e mode,
		const MID_REG_limit_s limits, int16_t * action_res){

	// Get values for the specific PI 
	int16_t upper_limit, lower_limit; //int32 because of duty
	fp_t kp,ki;
	static fp_t fp_ref, fp_input;
	static fp_t error;
	static fp_t accion, proporcional = 0;
	fp_t up_limit_I = 2097152000;
	fp_t low_limit_I = -2097152000;

	// set limits for saturation
	if (mode != MID_PWR_MODE_CC){ //out for pwr or v PI is allways current
		upper_limit = (limits.lsCurrMax) ;
		lower_limit = (limits.lsCurrMin) ;
		if (mode == MID_PWR_MODE_CV){
			kp= EPC_CONF_PWR_KP_V;
			ki= EPC_CONF_PWR_KI_V;
			fp_ref = mSI_to_FP(ref);
			fp_input = mSI_to_FP(meas);

		}else{
			kp= EPC_CONF_PWR_KP_P;
			ki= EPC_CONF_PWR_KI_P;
			fp_ref = dSI_to_FP(ref);
			fp_input = dSI_to_FP(meas);
		}
	}else if (mode == MID_PWR_MODE_CC){ // for i PI actions is the Duty to apply
		upper_limit = (HAL_PWM_period -1);
		lower_limit = HAL_PWM_MIN_PWM;
		kp= EPC_CONF_PWR_KP_I;
		ki= EPC_CONF_PWR_KI_I;
		fp_ref = mSI_to_FP(ref);
		fp_input = mSI_to_FP(meas);
	}


	// error = (double)(reference - input);
	error = sub_FP(fp_ref,fp_input);

	// proporcional = kp_I * error;
	proporcional = mul_FP(kp,error);

	// integral = integral + ki_I * last_error;
	fp_t temp;
	temp = mul_FP(ki,last_error[mode]);
	integral[mode] = sum_FP(integral[mode],temp);


    if(integral[mode] >= up_limit_I){
    	integral[mode] = up_limit_I;
    }else if(integral[mode] <= low_limit_I){
    	integral[mode] = low_limit_I;
    }

    last_error[mode] = error;
    // accion = proporcional + integral[mode];
    accion = sum_FP(proporcional,integral[mode]);


    if (mode == MID_PWR_MODE_CC){
    	*action_res = FP_to_SI(accion);
    }else{
    	*action_res = FP_to_mSI(accion);
    }
    if(*action_res >= upper_limit){
    	*action_res = upper_limit;
    }else if(*action_res <= lower_limit){
    	*action_res = lower_limit;
        }
	return MID_PWR_RESULT_SUCCESS;
}

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

MID_PWR_result_e MID_PwrSetOutput(const MID_PWR_Output_e outputMode){
	MID_PWR_result_e res = MID_PWR_RESULT_ERROR;
	res = (MID_PWR_result_e) HAL_GpioSet(HAL_GPIO_OUT_OutDisable, outputMode);
	if (outputMode == MID_PWR_Enable && res == MID_PWR_RESULT_SUCCESS){
		last_error[0] = 0;
		last_error[1] = 0;
		last_error[2] = 0;
		integral[0] = d0 * _FP_FACTOR;
		integral[1] = 0;
		integral[2] = 0;
		if (res == MID_PWR_RESULT_SUCCESS){
			res |= (MID_PWR_result_e) HAL_PwmSetDuty(d0);
			res |= HAL_PwmStart();
		}
	}
	else if (outputMode == MID_PWR_Disable && res == MID_PWR_RESULT_SUCCESS){
		res |= HAL_PwmStop();
	}
	return res;
}

MID_PWR_result_e MID_PwrApplyCtrl(const int16_t ref, const uint16_t V_LS, const int16_t I_LS, const MID_PWR_Mode_e control_mode, const MID_REG_limit_s limits){
	MID_PWR_result_e res = MID_PWR_RESULT_ERROR;
	int16_t curr_ref, actual_power;
	int16_t new_duty;
	switch (control_mode) { //first PI, if needed (in Pwr and V refs)
		case MID_PWR_MODE_CP:
			actual_power = (int16_t)(((int32_t)I_LS * (int32_t)V_LS)  /MID_PWR_TO_dW); // dW
			res = _calculatePI(ref, actual_power, MID_PWR_MODE_CP, limits, &curr_ref);
			break;
		case MID_PWR_MODE_CV:
			res = _calculatePI(ref, V_LS, MID_PWR_MODE_CV, limits, &curr_ref);
			break;
		case MID_PWR_MODE_CC: //First PI not needed.
			curr_ref = ref;
			res = MID_PWR_RESULT_SUCCESS;
			break;
		default:
			res = MID_PWR_RESULT_ERROR;
	}
	if (res == MID_PWR_RESULT_SUCCESS){

		// I action at this point is allways under the limits. The pwr and V PI saturate the action
		// and I ref from APP_CTRL is allways in limit

		SOA_e SOA_status = _checkSOA(curr_ref, V_LS, limits);
		if (SOA_status == SOA_over_pwr){
			curr_ref = (int32_t)(limits.lsPwrMax*100) / V_LS;
		}
		else if (SOA_status == SOA_under_pwr){
			curr_ref = (int32_t)(limits.lsPwrMin*100) / V_LS;
		}
		// calculate current PI		
		//Ignore warning as action for current PI will be a value of duty between 0-9215
		res = _calculatePI(curr_ref, I_LS, MID_PWR_MODE_CC, limits, &new_duty);
		if (res == MID_PWR_RESULT_SUCCESS){
			duty = new_duty;
			res = (MID_PWR_result_e) HAL_PwmSetDuty((uint32_t)duty);
		}
	}
	return res;
}

MID_PWR_result_e MID_PwrCalculateD0(const uint16_t V_HS, const uint16_t V_LS){
	MID_PWR_result_e res = MID_PWR_RESULT_ERROR;
	uint32_t new_d0 = (V_LS * ((HAL_PWM_period-1)-HAL_PWM_MIN_PWM)) / V_HS;
	if (new_d0 <= (HAL_PWM_period-1) && new_d0 >= 0){
		d0 = new_d0;
		res = MID_PWR_RESULT_SUCCESS;
	}
	return res;
}
