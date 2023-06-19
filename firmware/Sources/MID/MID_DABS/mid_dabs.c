/*********************************************************************************
* @file           : mid_dabs.c
* @brief          : Implementation of MID_DABS
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "hal_adc.h"
#include "hal_sts.h"
#include "hal_gpio.h"
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
#define MAX_LEDS_STEPS 5
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
	blink_mode_e mode; 		//Blinking mode
	uint8_t steps;			//Number of steps of the mode
	uint8_t ledsStep[MAX_LEDS_STEPS];	//Array with the output of the leds in each step
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
	blink_mode_idle, 2,	{0x00,				//0b00000000
						0x0F,				//0b00001111
						0x00,0x00,0x00		//0b00000000
						}
};
const blink_conf_s waitMode = {
	blink_mode_wait, 3,	{0x00,				//0b00000000
						0x0A, 				//0b00001010
						0x05, 				//0b00000101
						0x00,0x00			//0b00000000
						}
};
const blink_conf_s ccChgMode = {
	blink_mode_cc_chg, 5, {0x00,			//0b00000000
						0x08,				//0b00001000
						0x04,				//0b00000100
						0x02,				//0b00000010
						0x01 				//0b00000001
						}
};
const blink_conf_s ccDchgMode = {
	blink_mode_cc_dchg, 5,	{0x00,			//0b00000000
							0x01,			//0b00000001
							0x02,			//0b00000010
							0x04,			//0b00000100
							0x08 			//0b00001000
							}
};
const blink_conf_s cvChgMode = {
	blink_mode_cv_chg, 5, 	{0x0F,			//0b00001111
							0x0E,			//0b00001110
							0x0D,			//0b00001101
							0x0B,			//0b00001011
							0x07 			//0b00000111
							}
};
const blink_conf_s cvDchgMode = {
	blink_mode_cv_dchg, 5,	{0x0F,			//0b00001111
							0x07,			//0b00000111
							0x0B,			//0b00001011
							0x0D,			//0b00001101
							0x0E 			//0b00001110
							}
};
const blink_conf_s cpChgMode = {
	blink_mode_cp_chg, 5,	{0x00,			//0b00000000
							0x01,			//0b00000001
							0x03,			//0b00000011
							0x07,			//0b00000111
							0x0F 			//0b00001111
							}
};
const blink_conf_s cpDchgMode = {
	blink_mode_cp_dchg, 5,	{0x00,			//0b00000000
							0x08,			//0b00001000
							0x0C,			//0b00001100
							0x0E,			//0b00001110
							0x0F 			//0b00001111
							}
};
const blink_conf_s errHsvoltMode = {
	blink_mode_err_hsvolt, 1,	{0x01,		//0b00000001
								0x00,		//0b00000000
								0x00,		//0b00000000
								0x00,		//0b00000000
								0x00}
};
const blink_conf_s errlsvoltMode = {
	blink_mode_err_lsvolt, 1,	{0x08,		//0b00001000
								0x00,0x00,	//0b00000000
								0x00,0x00	//0b00000000
								}
};
const blink_conf_s errlscurrMode = {
	blink_mode_err_lscurr, 1, {0xC,			//0b00001100
							0x00,0x00,		//0b00000000
							0x00,0x00 		//0b00000000
							}
};
const blink_conf_s errCommMode = {
	blink_mode_err_comm, 1,	{0x0A,			//0b00001010
							0x00,0x00,		//0b00000000
							0x00,0x00		//0b00000000
							}
};
const blink_conf_s errTempMode = {
	blink_mode_err_temp, 1,	{0x03,			//0b00000011
							0x00,0x00,		//0b00000000
							0x00,0x00		//0b00000000
							}
};
const blink_conf_s errIntMode = {
	blink_mode_err_int, 1,	{0x09,			//0b00001001
							0x00,0x00,		//0b00000000
							0x00,0x00		//0b00000000
							}
};
/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
blink_s ledsMode = {
		idleMode, 0, idleMode 				//Initialice in idle mode
};
/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/
/**********************************************************************************/
/*                        Definition of imported variables                        */
/**********************************************************************************/
extern const MID_REG_info_s EPC_CONF_info;
extern const MID_REG_meas_property_s factors;
extern const MID_REG_meas_property_s offset;
extern const MID_REG_meas_property_s max_value;
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
	if (epcmode == MID_REG_MODE_ERROR){	
		if (errors->intErr !=MID_REG_ERROR_NONE){
			*mode = errIntMode;
		}
		else if (errors->hsVoltErr !=MID_REG_ERROR_NONE){
			*mode = errHsvoltMode;
		}
		else if (errors->commErr !=MID_REG_ERROR_NONE){
			*mode = errCommMode;
		}
		else if (errors->lsVoltErr !=MID_REG_ERROR_NONE){
			*mode = errlsvoltMode;
		}
		else if (errors->lsCurrErr !=MID_REG_ERROR_NONE){
			*mode = errlscurrMode;
		}
		else if (errors->tempErr !=MID_REG_ERROR_NONE){
			*mode = errTempMode;
		}
		else {
			res = MID_DABS_RESULT_ERROR;
		}		
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
	MID_DABS_result_e res = MID_DABS_RESULT_SUCCESS;
	uint8_t state = ledsMode.mode.ledsStep[step];
	uint8_t mask= 0x1;
	res |= (MID_DABS_result_e) HAL_GpioSet(HAL_GPIO_OUT_Led0, state & mask);
	res |= (MID_DABS_result_e) HAL_GpioSet(HAL_GPIO_OUT_Led1, (state>>1) & mask);
	res |= (MID_DABS_result_e) HAL_GpioSet(HAL_GPIO_OUT_Led2, (state>>2) & mask);
	res |= (MID_DABS_result_e) HAL_GpioSet(HAL_GPIO_OUT_Led3, (state>>3) & mask);
	return res;
}

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

MID_DABS_result_e MID_DabsUpdateMeas(const MID_DABS_meas_e type, MID_REG_meas_property_s * measreg){
	MID_DABS_result_e res = MID_DABS_RESULT_SUCCESS;
	uint16_t data_adc = 0;
	int16_t temp_sensor = 0;
	switch(type){
		case MID_DABS_MEAS_ELECTRIC:
			res = (MID_DABS_result_e) HAL_AdcGetValue(HAL_ADC_HS_VOLT, &data_adc);;
			if (res == MID_DABS_RESULT_SUCCESS){
				measreg->hsVolt = (uint16_t)(((uint32_t)(data_adc*factors.hsVolt)/max_value.hsVolt)+offset.hsVolt);
			}
			res = (MID_DABS_result_e) HAL_AdcGetValue(HAL_ADC_LS_VOLT, &data_adc);;
			if (res == MID_DABS_RESULT_SUCCESS){
				measreg->lsVolt = (uint16_t)(((uint32_t)(data_adc*factors.lsVolt)/max_value.lsVolt)+offset.lsVolt);
			}
			res = (MID_DABS_result_e) HAL_AdcGetValue(HAL_ADC_LS_CURR, &data_adc);;
			if (res == MID_DABS_RESULT_SUCCESS){
				measreg->lsCurr =(int16_t) (((uint32_t)(data_adc*(uint16_t)factors.lsCurr)/max_value.lsCurr)+offset.lsCurr);
			}
			break;
		case MID_DABS_MEAS_TEMP:
			// Check if the hardware version has I2C
			if ((EPC_CONF_info.hwVer %2)==0){ // Odd will have i2c Even won´t
				res = (MID_DABS_result_e) HAL_StsReadTemperature(&temp_sensor);
				if (res == MID_DABS_RESULT_SUCCESS){
					measreg->tempBody = temp_sensor;
				}
			}else{
				// If not I2C the register will always have a 0
				measreg->tempBody=0;
			}
			res = (MID_DABS_result_e) HAL_AdcGetValue(HAL_ADC_TEMP_ANOD, &data_adc);
			if (res == MID_DABS_RESULT_SUCCESS){
				measreg->tempAnod = (int16_t) (((uint32_t)(data_adc*factors.tempAnod)/max_value.tempAnod)+offset.tempAnod);
			}
			res = (MID_DABS_result_e) HAL_AdcGetValue(HAL_ADC_TEMP_AMB, &data_adc);
			if (res == MID_DABS_RESULT_SUCCESS){
				measreg->tempAmb = (int16_t) (((uint32_t)(data_adc*factors.tempAmb)/max_value.tempAmb)+offset.tempAmb);
			}
			break;
	}
	return res;
}


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
		if(ledsMode.mode.steps != 1){
			res = SetLeds(ledsMode.step);
			ledsMode.prevMode = ledsMode.mode;
		}		
	}
	return res;
}

