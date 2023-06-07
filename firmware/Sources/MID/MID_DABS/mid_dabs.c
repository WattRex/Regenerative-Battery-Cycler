/*********************************************************************************
* @file           : mid_dabs.c
* @brief          : Implementation of MID_DABS
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
//#include "hal_adc.h"
#include "hal_sts.h"
#include "hal_gpio.h"
#include "hal_tmr.h"
#include "epc_conf.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "mid_dabs.h"

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
typedef enum {
	blink_mode_idle = 0x00U,
	blink_mode_wait = 0x01U,
	blink_mode_cc_chg = 0x02U,
	blink_mode_cc_dchg = 0x03U,
	blink_mode_cv_chg = 0x04U,
	blink_mode_cv_dchg = 0x05U,
	blink_mode_cp_chg = 0x06U,
	blink_mode_cp_dchg = 0x07U,
	blink_mode_err_hsvolt = 0x08U,
	blink_mode_err_lsvolt = 0x09U,
	blink_mode_err_lscurr = 0x0AU,
	blink_mode_err_comm = 0x0BU,
	blink_mode_err_temp = 0x0CU,
	blink_mode_err_int = 0x0DU
}blink_mode_e;

typedef struct{
	blink_mode_e mode; 	//Blinking mode
	uint8_t steps;		//Number of steps of the mode
	uint8_t ledsStep[5];//Array with the output of the leds in each step
}blink_conf_s;

typedef struct{
	blink_conf_s mode;		// Actual mode of the leds
	uint8_t step;			// Actual step of the mode
	blink_conf_s prevMode;	//Previous mode of the leds
}blink_s;
/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/
static MID_DABS_result_e CheckBlinkStatus(MID_REG_mode_e epcmode, int16_t lscurr,
		MID_REG_errorStatus_s * errors, blink_conf_s * mode);

static MID_DABS_result_e SetLeds(uint8_t state);
/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/
// Modes the leds can be
const blink_conf_s idleMode = {
	blink_mode_idle, 2,	{0x00,0x0F,0x00,0x00,0x00}
};
const blink_conf_s waitMode = {
	blink_mode_wait, 3,	{0x00,0x0A, 0x05,0x00,0x00}
};
const blink_conf_s ccChgMode = {
	blink_mode_cc_chg, 5, {0x00,0x08,0x04,0x02,0x01}
};
const blink_conf_s ccDchgMode = {
	blink_mode_cc_dchg, 5,	{0x00,0x01,0x02,0x04,0x08}
};
const blink_conf_s cvChgMode = {
	blink_mode_cv_chg, 5, {0x0F,0x0E,0x0D,0x0B,0x07}
};
const blink_conf_s cvDchgMode = {
	blink_mode_cv_dchg, 5,	{0x0F,0x07,0x0B,0x0D,0x0E}
};
const blink_conf_s cpChgMode = {
	blink_mode_cp_chg, 5,	{0x00,0x01,0x03,0x07,0x0F}
};
const blink_conf_s cpDchgMode = {
	blink_mode_cp_dchg, 5,	{0x00,0x08,0x0C,0x0E,0x0F}
};
const blink_conf_s errHsvoltMode = {
	blink_mode_err_hsvolt, 1,	{0x01,0x00,0x00,0x00,0x00}
};
const blink_conf_s errlsvoltMode = {
	blink_mode_err_lsvolt, 1,	{0x08,0x00,0x00,0x00,0x00}
};
const blink_conf_s errlscurrMode = {
	blink_mode_err_lscurr, 1, {0xC,0x00,0x00,0x00,0x00}
};
const blink_conf_s errCommMode = {
	blink_mode_err_comm, 1,	{0x0A,0x00,0x00,0x00,0x00}
};
const blink_conf_s errTempMode = {
	blink_mode_err_temp, 1,	{0x03,0x00,0x00,0x00,0x00}
};
const blink_conf_s errIntMode = {
	blink_mode_err_int, 1,	{0x09,0x00,0x00,0x00,0x00}
};
/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
blink_s ledsMode = {
		idleMode, 0, idleMode //Initialice in idle mode
};
/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/
/**********************************************************************************/
/*                        Definition of imported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/
/**
 * @fn MID_DABS_result_e CheckBlinkStatus(MID_REG_mode_e epcmode, int16_t lscurr,
		MID_REG_errorStatus_s errors, blink_conf_s * mode)
 * @brief Get the leds mode associated to the mode in which is currently working the epc.
 *
 * @param epcmode MID_REG_mode_e, is the mode the epc is working
 * @param lscurr, is the actual measurement of the current in the low side,
 * 			depending on the value will be charging or discharging.
 * @param errors, give access to the errors register to now if there are any error.
 * @param mode, Output of the function to give the mode for the leds.
 * @return @ref MID_DABS_RESULT_SUCCESS if all data gathered correctly,
 * 		@ref MID_DABS_RESULT_BUSY, @ref MID_DABS_RESULT_TIMEOUT or
 * 		@ref MID_DABS_RESULT_ERROR otherwise.
 */
static MID_DABS_result_e CheckBlinkStatus(MID_REG_mode_e epcmode, int16_t lscurr,
		MID_REG_errorStatus_s * errors, blink_conf_s * mode){
	MID_DABS_result_e res = MID_DABS_RESULT_SUCCESS;
	if (errors->hsVoltErr !=MID_REG_ERROR_NONE){
		*mode = errHsvoltMode;
	}
	else if (errors->lsVoltErr !=MID_REG_ERROR_NONE){
		*mode = errlsvoltMode;
	}
	else if (errors->lsCurrErr !=MID_REG_ERROR_NONE){
		*mode = errlscurrMode;
	}
	else if (errors->commErr !=MID_REG_ERROR_NONE){
		*mode = errCommMode;
	}
	else if (errors->tempErr !=MID_REG_ERROR_NONE){
		*mode = errTempMode;
	}
	else if (errors->intErr !=MID_REG_ERROR_NONE){
		*mode = errIntMode;
	}
	// After checking there are no errors, check the actual mode.
	else{
		if (epcmode == MID_REG_MODE_IDLE){
			*mode = idleMode;
		}
		else if (epcmode == MID_REG_MODE_WAIT){
			*mode = waitMode;
		}
		else if (epcmode == MID_REG_MODE_CV && lscurr>=0){
			*mode = cvChgMode;
		}
		else if (epcmode == MID_REG_MODE_CV && lscurr<0){
			*mode = cvDchgMode;
		}
		else if (epcmode == MID_REG_MODE_CC && lscurr>=0){
			*mode = ccChgMode;
		}
		else if (epcmode == MID_REG_MODE_CC && lscurr<0){
			*mode = ccDchgMode;
		}
		else if (epcmode == MID_REG_MODE_CP && lscurr>=0){
			*mode = cpChgMode;
		}
		else if (epcmode == MID_REG_MODE_CP && lscurr<0){
			*mode = cpDchgMode;
		}
		else {
			res = MID_DABS_RESULT_ERROR;
		}
	}
	return res;
}

/**
 * @fn MID_DABS_result_t SetLeds()
 * @brief Set the leds to the state indicated by the input
 * @param state, 8bit input but only needed the last 4 bits as there are only 4 leds
 * @return @ref MID_DABS_RESULT_SUCCESS if measured correctly,
 * 		@ref MID_DABS_RESULT_BUSY, @ref MID_DABS_RESULT_TIMEOUT or
 * 		@ref MID_DABS_RESULT_ERROR otherwise.
 */
static MID_DABS_result_e SetLeds(uint8_t step){
	MID_DABS_result_e res = MID_DABS_RESULT_ERROR;
	uint8_t state = ledsMode.mode.ledsStep[step];
	uint8_t mask= 0x1;
	res = (MID_DABS_result_e) HAL_GpioSet(HAL_GPIO_OUT_Led0, state & mask);
	res = (MID_DABS_result_e) HAL_GpioSet(HAL_GPIO_OUT_Led1, (state>>1) & mask);
	res = (MID_DABS_result_e) HAL_GpioSet(HAL_GPIO_OUT_Led2, (state>>2) & mask);
	res = (MID_DABS_result_e) HAL_GpioSet(HAL_GPIO_OUT_Led3, (state>>3) & mask);
	return res;
}

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

//MID_DABS_result_e MID_DabsUpdateMeas(const MID_DABS_meas_e type, MID_REG_meas_s * measreg){
//	MID_DABS_result_e res = MID_DABS_RESULT_SUCCESS;
//	switch(type){
//		case MID_DABS_MEAS_ELECTRIC:
//			uint16_t data;
//			res = (MID_DABS_result_e) HAL_StsReadTemperature(&temp);
//			if (res == MID_DABS_RESULT_SUCCESS){
//				*measreg->hsVolt = data;
//			}
//			res = (MID_DABS_result_e) HAL_StsReadTemperature(&temp);
//			if (res == MID_DABS_RESULT_SUCCESS){
//				*measreg->tempBody = data;
//			}
//			int16_t data;
//			res = (MID_DABS_result_e) HAL_StsReadTemperature(&temp);
//			if (res == MID_DABS_RESULT_SUCCESS){
//				*measreg->tempBody = data;
//			}
//			break;
//		case MID_DABS_MEAS_TEMP:
//			int16_t temp;
//			// Check if the hardware version has I2C
//			if (MID_REG_info_s.hwVer > 16){
//				res = (MID_DABS_result_e) HAL_StsReadTemperature(&temp);
//				if (res == MID_DABS_RESULT_SUCCESS){
//					*measreg->tempBody = temp;
//				}
//			}else{
//				// If not I2C the register will always have a 0
//				*measreg->tempBody=0;
//			}
//			res = (MID_DABS_result_e) HAL_AdcGet(HAL_ADC_PORT_Ext_Temp1, &temp);
//			if (res == MID_DABS_RESULT_SUCCESS){
//				*measreg->tempBody = temp;
//			}
//			res = (MID_DABS_result_e) HAL_AdcGet(HAL_ADC_PORT_Ext_Temp2, &temp);
//			if (res == MID_DABS_RESULT_SUCCESS){
//				*measreg->tempBody = temp;
//			}
//			break;
//	}
//	return res;
//}


MID_DABS_result_e MID_DabsUpdateLeds(MID_REG_mode_e ctrlMode,
		int16_t curr, MID_REG_errorStatus_s * errors){
	MID_DABS_result_e res = MID_DABS_RESULT_ERROR;
	blink_conf_s inputMode;
	//Check the mode of the EPC and the mode the leds should be in
	res = CheckBlinkStatus(ctrlMode, curr, errors, &inputMode);
	if (res == MID_DABS_RESULT_SUCCESS){
		if (ledsMode.prevMode.mode == inputMode.mode){
			ledsMode.step++;
			ledsMode.step = ledsMode.step % ledsMode.mode.steps;
		}
		else{
			ledsMode.mode = inputMode;
			ledsMode.step = 0;
		}
		res = SetLeds(ledsMode.step);
		ledsMode.prevMode = ledsMode.mode;
	}
	return res;
}

