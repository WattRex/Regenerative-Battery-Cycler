/*********************************************************************************
* @file           : hal_adc.c
* @brief          : Implementation of HAL ADC
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "dma.h"
#include "stdlib.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_adc.h"
#include "adc.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/
#define _ADC1_BUFFER_SIZE 6
#define _N_SAMPLES_PWR 10
#define _ADC2_BUFFER_SIZE 60
/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
/* Variable containing ADC conversions results */
static __IO uint16_t   _ADC1_results[_ADC1_BUFFER_SIZE];
static __IO uint16_t   _ADC2_results[_ADC2_BUFFER_SIZE];

static volatile uint8_t _idx_cplt_ADC1 = _ADC1_BUFFER_SIZE/2;
static volatile uint8_t _idx_cplt_ADC2 = _ADC2_BUFFER_SIZE/2;

static	uint16_t _meas_pwr[_N_SAMPLES_PWR];

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
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

static uint16_t findMedian4(const uint16_t a, const uint16_t b, const uint16_t c, const uint16_t d){
	uint16_t res;

	if ( (a <= b && b <= c && c <= d) || (d <= c && c <= b && b <= a) ){
		res = b;
	}
	else if ( (b <= a && a <= c && c <= d) || (d <= c && c <= a && a <= b) ){
		res = a;
	}
	else if ( (b <= c && c <= a && a <= d) || (d <= a && a <= c && c <= b) ){
		res = c;
	}
	else{
		res = d;
	}
	return res;

}

static uint16_t findMedian3(const uint16_t a, const uint16_t b, const uint16_t c){
	uint16_t res;
	if ( (a <= b && b <= c) || (c <= b && b <= a)) {
		res = b;
	}
	else if ( (b <= a && a <= c) || (c <= a && a <= b)) {
		res = a;
	}	else{
		res = c;
	}
	return res;
}

static uint16_t getEstim(uint16_t start_sensor_idx){
		uint16_t meas_idx = start_sensor_idx;
		uint8_t stride = 3;
//		uint16_t i, res = 0;
//		for(i = 0; i < _N_SAMPLES_PWR; i += 1){
//			res += _ADC2_results[meas_idx];
//			_meas_pwr[i] = _ADC2_results[meas_idx];
//			meas_idx += stride;
//		}
//		return res;
////		i = 0;
		meas_idx = start_sensor_idx;
		uint16_t m1 = findMedian3(_ADC2_results[meas_idx], _ADC2_results[meas_idx + stride], _ADC2_results[meas_idx + 2*stride]);
		meas_idx += 3*stride;
		uint16_t m2 = findMedian3(_ADC2_results[meas_idx], _ADC2_results[meas_idx + stride], _ADC2_results[meas_idx + 2*stride]);
		meas_idx += 3*stride;
		uint16_t m3 = findMedian4(_ADC2_results[meas_idx], _ADC2_results[meas_idx + stride],
				_ADC2_results[meas_idx + 2*stride], _ADC2_results[meas_idx + 3*stride]);

//		return findMedian3(m1,  m2,  m3);
		return ( m1 + m2 + m3) / 3;
}

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/
void HAL_AdcCallbackDMAChl1Cplt(void){
	_idx_cplt_ADC1 = _ADC1_BUFFER_SIZE/2 - _idx_cplt_ADC1;
}

void HAL_AdcCallbackDMAChl2Cplt(void){
	_idx_cplt_ADC2 = _ADC2_BUFFER_SIZE/2 - _idx_cplt_ADC2;
}

HAL_ADC_result_e HAL_AdcInit (void)
{
	HAL_ADC_result_e res = HAL_ADC_RESULT_SUCCESS;

	EPC_ST_ERR_COUNTER = 0;
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_ADC2_Init();

	if (EPC_ST_ERR_COUNTER){
		res = HAL_ADC_RESULT_ERROR;
	}else{
		res |= HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
		res |= HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	  if (res == HAL_ADC_RESULT_SUCCESS){
	  	res |= HAL_ADC_Start_DMA(&hadc1, (uint32_t *)_ADC1_results, _ADC1_BUFFER_SIZE);
	  	res |= HAL_ADC_Start_DMA(&hadc2, (uint32_t *)_ADC2_results, _ADC2_BUFFER_SIZE);
		}
	}

	return res;
}


HAL_ADC_result_e HAL_AdcGetValue (const HAL_ADC_port_e port, uint16_t* value)
{
	HAL_ADC_result_e res = HAL_ADC_RESULT_SUCCESS;
	if (port <= HAL_ADC_HS_VOLT){
		uint8_t idx = port + _idx_cplt_ADC2;
//		*value = getPwrMedian(idx);
		*value = getEstim(idx);
	}else if (HAL_ADC_TEMP_ANOD <= port && port <= HAL_ADC_INT_TEMP){
		HAL_ADC_Start(&hadc1);
		uint8_t sensor_idx = port - HAL_ADC_TEMP_ANOD + _idx_cplt_ADC1;
		*value = _ADC1_results[sensor_idx];
	}else{
		res = HAL_ADC_RESULT_ERROR;
	}
	return res;
}
