/*********************************************************************************
* @file           : test.c
* @brief          : Implementation of testing file
**********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "epc_conf.h"
#include "main.h"

#ifdef EPC_CONF_PWM_ENABLED
	#include "hal_pwm_test.h"
#endif

#ifdef EPC_CONF_GPIO_ENABLED
	#include "hal_gpio_test.h"
#endif

#ifdef EPC_CONF_ADC_DMA_ENABLED
	#include "hal_adc_test.h"
#endif

#ifdef EPC_CONF_STS_ENABLED
	#include "hal_sts_test.h"
#endif

#ifdef EPC_CONF_TMR_ENABLED
	#include "hal_tmr_test.h"
#endif

#ifdef EPC_CONF_WDG_ENABLED
	#include "hal_wdg_test.h"
#endif

#ifdef EPC_CONF_CAN_ENABLED
	#include "hal_can_test.h"
#endif

#ifdef MID_COMM_H_
	#include "mid_comm_test.h"
#endif
/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "test.h"

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

TEST_result_e PWMMainTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_PWM_ENABLED

#endif
	return res;
}

TEST_result_e GpioMainTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_GPIO_ENABLED
	 res = (TEST_result_e) HAL_GpioTest(HAL_GPIO_OUT_OutDisable, HAL_GPIO_IN_ThermalWarn);
#endif
	return res;
}

TEST_result_e STSMainTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_STS_ENABLED
	res = (TEST_result_e) HAL_StsTest();
#endif
	return res;
}

TEST_result_e AdcMainTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_ADC_DMA_ENABLED
	#ifdef EPC_CONF_TMR_ENABLED
		TestAdcs();
	#endif
#endif
	return res;

}

TEST_result_e TimersMainTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_TMR_ENABLED
	HAL_TmrStart(HAL_TMR_CLOCK_PWR_MEAS);
	res |= TestRTTmr();
	HAL_TmrStop(HAL_TMR_CLOCK_PWR_MEAS);
	HAL_TmrStart(HAL_TMR_CLOCK_RT);
	res |= TestPwrMeasTmr();
	HAL_TmrStop(HAL_TMR_CLOCK_RT);
#endif
	return res;
}

TEST_result_e WDGMainTest(void){
	TEST_result_e res = TEST_RESULT_ERROR;
	#ifdef EPC_CONF_WDG_ENABLED
		#ifdef EPC_CONF_TMR_ENABLED
			#ifdef EPC_CONF_GPIO_ENABLED
				res |= TestWdg();
			#endif
		#endif
	#endif

	return res;
}

TEST_result_e CanMainTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_CAN_ENABLED
	res = (TEST_result_e) HAL_CanTest();
#endif
	return res;
}

TEST_result_e HalMainTest(void){
	TEST_result_e test_res = TEST_RESULT_SUCCESS;
	#ifndef EPC_CONF_WDG_ENABLED
		test_res |= PWMMainTest();
		test_res |= GpioMainTest();
		test_res |= CanMainTest();
		test_res |= STSMainTest();
		#ifdef EPC_CONF_ADC_DMA_ENABLED
			test_res |= AdcMainTest();
		#else
			test_res |= TimersMainTest();
		#endif
//		HAL_Delay(1000);
	#else
		test_res |= WDGMainTest();
	#endif
	return test_res;
}

TEST_result_e MidMainTest(void){
	TEST_result_e test_res = TEST_RESULT_SUCCESS;
		test_res |= CommMainTest();
		HAL_Delay(1000);
	return test_res;
}

TEST_result_e TEST_main(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
//	res |= HalMainTest();
	res |= MidMainTest();
	return res;
}

