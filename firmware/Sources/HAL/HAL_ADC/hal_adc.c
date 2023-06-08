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

// Inserts a key in arr[] of given capacity. n is current
// size of arr[]. This function returns n+1 if insertion
// is successful, else n.
static uint16_t insertSorted(const uint16_t n, uint16_t key)
{
    // Cannot insert more elements if n is already
    // more than or equal to capacity
		uint16_t new_size = n;
		if (n < _N_SAMPLES_PWR) {
			new_size += 1;
			if (n == 0){
				_meas_pwr[0] = key;
			} else{
				int16_t i = n - 1;
				for (; (i >= 0 && _meas_pwr[i] > key); i--)
					_meas_pwr[i + 1] = _meas_pwr[i];

				_meas_pwr[i + 1] = key;
			}
    }

    return new_size;
}


// Function for calculating median
static uint16_t getPwrMedian(uint16_t start_sensor_idx)
{
	// Insert data ordered
	uint16_t meas_idx = start_sensor_idx;
	uint8_t stride = 3, i;
	for(i = 0; i < _N_SAMPLES_PWR;){
		i = insertSorted(i, _ADC2_results[meas_idx]);
		meas_idx += stride;
	}

	// check for even case
  uint16_t res = 0;
	if (i % 2 != 0)
		res = _meas_pwr[i / 2];
	else
		res = (_meas_pwr[(i - 1) / 2] + _meas_pwr[i / 2]) / 2;
  return res;
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
		*value = getPwrMedian(idx);
	}else if (HAL_ADC_TEMP_ANOD <= port && port <= HAL_ADC_INT_TEMP){
		HAL_ADC_Start(&hadc1);
		uint8_t sensor_idx = port - HAL_ADC_TEMP_ANOD + _idx_cplt_ADC1;
		*value = _ADC1_results[sensor_idx];
	}else{
		res = HAL_ADC_RESULT_ERROR;
	}
	return res;
}
