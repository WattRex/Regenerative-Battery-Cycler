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
#define _N_FRAC_BITS 16
#define _FP_FACTOR (1 << _N_FRAC_BITS)
#define _SCALING_FACTOR_MILIS 1000
#define _SCALING_FACTOR_DECIS 10

/**********************************************************************************/
/*                    Definition of local function like macros                    */
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
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/
static MID_PWR_result_e _calculatePI(const int16_t ref, const int16_t meas,
		const MID_PWR_Mode_e mode, const MID_REG_limit_s limits, int32_t * action);

static SOA_e _checkSOA(const int16_t I, const uint16_t V, const MID_REG_limit_s limits);
/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
static uint16_t kp[3] = {6,0,0}, ki[3] = {5,0,0}; //TODO: EPC_CONF
static int32_t  integral_value[3] = {0, 0, 0}; //I, V, P PI values
static uint8_t  saturation_flag[3] = {0,0,0};	//I, V, P PI saturation flags
static uint32_t duty, d0 = 0; //action duty goes from 0 to 100000 (in m%)

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of imported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/
// TODO: add documentation
// reference: http://www.sunshine2k.de/articles/coding/fp/sunfp.html#ch42
static void convert_dSI_to_FP(const int16_t value, fp_t * const res){
	*res = (fp_t) value * _FP_FACTOR / _SCALING_FACTOR_DECIS;
}
static void convert_mSI_to_FP(const int16_t value, fp_t * const res){
	*res = (fp_t) value * _FP_FACTOR / _SCALING_FACTOR_MILIS;
}

static void sum_FP(fp_t const * const sum1, fp_t const * const sum2, fp_t * const res){
	*res = *sum1 + *sum2;
}

static void mult_FP(fp_t const * const fac1, fp_t const * const fac2, fp_t * const res){
	int64_t mul = (int64_t)(*fac1) * (int64_t)(*fac2);
	*res = (fp_t) ( mul >> _N_FRAC_BITS );
}

static void convert_FP_to_mSI(fp_t const * const value, int16_t * const res){
	*res = (int16_t) ( (int64_t)(*value) * _SCALING_FACTOR_MILIS >> _N_FRAC_BITS);
}
static void convert_FP_to_dSI(fp_t const * const value, int16_t * const res){
	*res = (int16_t) ( (int64_t)(*value) * _SCALING_FACTOR_DECIS >> _N_FRAC_BITS);
}

// TODO: move it to test
void TestFP(void){
	int16_t ls_volt = 8500, hs_volt = 0; // hs_volt should be hs_volt = (ls_volt + ls_volt)*1.5 = 25.5 M = 25500 mV
	fp_t fp_val, fp_sum, fp_fact, fp_mult;

	convert_mSI_to_FP(ls_volt, &fp_val);
	sum_FP(&fp_val, &fp_val, &fp_sum);
	convert_FP_to_mSI(&fp_sum, &hs_volt);

	convert_mSI_to_FP(1500, &fp_fact);
	mult_FP(&fp_sum, &fp_fact, &fp_mult);

	convert_FP_to_mSI(&fp_mult, &hs_volt);
}


//TODO: rewrite
static SOA_e _checkSOA(const int16_t I, const uint16_t V, const MID_REG_limit_s limits){
	SOA_e res = SOA_ok;
	int16_t power = (int16_t)(((int32_t)I * (int32_t)V) /100000); // 10^-3(mW) *10^-3 (mW) / 10^-5 -> dW
	if (power > limits.lsPwrMax)
		res = SOA_over_pwr;
	else if (power < limits.lsPwrMin)
		res = SOA_under_pwr;
	return res;
}

//TODO: rewrite
/**
 * @fn MID_PWR_result_t SetLeds()
 * @brief Set the leds to the state indicated by the input
 * @param state, 8bit input but only needed the last 4 bits as there are only 4 leds
 * @return @ref MID_PWR_RESULT_SUCCESS if measured correctly,
 * 		@ref MID_PWR_RESULT_BUSY, @ref MID_PWR_RESULT_TIMEOUT or
 * 		@ref MID_PWR_RESULT_ERROR otherwise.
 */
static MID_PWR_result_e _calculatePI(const int16_t ref, const int16_t meas, const MID_PWR_Mode_e mode,
		const MID_REG_limit_s limits, int32_t * action){

	// Get values for the specific PI 
	int32_t upper_limit, lower_limit; //int32 because of duty
	int32_t error = ref - meas;

	// set limits for saturation
	if (mode != MID_PWR_MODE_CC){ //out for pwr or v PI is allways current
		upper_limit = limits.lsCurrMax ;
		lower_limit = limits.lsCurrMin ;
	}else{ // for i PI actions is the deltaDuty to apply
		upper_limit = HAL_PWM_MAX_DUTY - d0;
		lower_limit= - d0;
	}

	// check if already saturated
	if(saturation_flag[mode]){
		integral_value[mode] += error;
	}

	//set new action
	*action = kp[mode] * error + ki[mode] * integral_value[mode];

	// check action and saturate if needed
	if(*action > upper_limit){
		*action = upper_limit;
		saturation_flag[mode] = 1;
	}else if(*action < lower_limit){
		*action = lower_limit;
		saturation_flag[mode] = 1;
	}else{
		saturation_flag[mode] = 0;
	}

	return MID_PWR_RESULT_SUCCESS;
}

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

MID_PWR_result_e MID_PwrSetOutput(const MID_PWR_Output_e outputMode){
	MID_PWR_result_e res = MID_PWR_RESULT_ERROR;
	res = (MID_PWR_result_e) HAL_GpioSet(HAL_GPIO_OUT_OutDisable, outputMode);
	return res;
}

MID_PWR_result_e MID_PwrApplyCtrl(const int16_t ref, const uint16_t V_LS, const int16_t I_LS, const MID_PWR_Mode_e control_mode, const MID_REG_limit_s limits){
	MID_PWR_result_e res = MID_PWR_RESULT_ERROR;
	int32_t curr_ref, delta_duty;
	int16_t actual_power;
	switch (control_mode) { //first PI, if needed (in Pwr and V refs)
		case MID_PWR_MODE_CP:
			actual_power = (int16_t)(((int32_t)I_LS * (int32_t)V_LS) /100); // dW
			res = _calculatePI(ref, actual_power, MID_PWR_MODE_CP, limits, &curr_ref);
			break;
		case MID_PWR_MODE_CV:
			res = _calculatePI(ref, V_LS, MID_PWR_MODE_CV, limits, &curr_ref);
			break;
		case MID_PWR_MODE_CC: //not first PI needed.
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
		res = _calculatePI(curr_ref, I_LS, MID_PWR_MODE_CC, limits, &delta_duty);
		if (res == MID_PWR_RESULT_SUCCESS){
			duty = delta_duty + d0;
			res = (MID_PWR_result_e) HAL_PwmSetDuty(duty);
		}
	}

	return res;
}

MID_PWR_result_e MID_PwrCalculateD0(const uint16_t V_HS, const uint16_t V_LS){
	MID_PWR_result_e res = MID_PWR_RESULT_ERROR;
	uint32_t new_d0 = V_LS * HAL_PWM_MAX_DUTY / V_HS;
	if (new_d0 <= HAL_PWM_MAX_DUTY && new_d0 >= 0){
		d0 = new_d0;
		res = MID_PWR_RESULT_SUCCESS;
	}
	return res;
}
