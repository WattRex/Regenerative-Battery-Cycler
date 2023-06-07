/*********************************************************************************
* @file           : hal_adc_test.c
* @brief          : Implementation of HAL TMR
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "main.h"
#include "hal_tmr.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_adc_test.h"

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

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/
volatile uint8_t adc_temp_finish = 0, adc_pwr_finish = 0;

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

HAL_ADC_result_e TestAdcs(void){
	HAL_ADC_result_e res = HAL_ADC_RESULT_SUCCESS;
	HAL_TmrStart(HAL_TMR_CLOCK_RT);
	HAL_TmrStart(HAL_TMR_CLOCK_PWR_MEAS);
	n_ints_rt = 0;
	uint16_t ls_curr, ls_volt, hs_volt;
	uint16_t temp1, temp2, int_temp;
	while(n_ints_rt < 4){	}
	res |= HAL_AdcGetValue(HAL_ADC_LS_CURR, &ls_curr);
	res |= HAL_AdcGetValue(HAL_ADC_LS_VOLT, &ls_volt);
	res |= HAL_AdcGetValue(HAL_ADC_HS_VOLT, &hs_volt);

	res |= HAL_AdcGetValue(HAL_ADC_EXT_TEMP1, &temp1);
	res |= HAL_AdcGetValue(HAL_ADC_EXT_TEMP2, &temp2);
	res |= HAL_AdcGetValue(HAL_ADC_INT_TEMP, &int_temp);

	while(n_ints_rt % 2 == 0){	};
	HAL_TmrStop(HAL_TMR_CLOCK_RT);
	HAL_TmrStop(HAL_TMR_CLOCK_PWR_MEAS);

	res |= HAL_AdcGetValue(HAL_ADC_EXT_TEMP1, &temp1);
	res |= HAL_AdcGetValue(HAL_ADC_EXT_TEMP2, &temp2);
	res |= HAL_AdcGetValue(HAL_ADC_INT_TEMP, &int_temp);

	return res;
}
