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

TEST_result_e SlowAdcMainTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_ADC_DMA_ENABLED

#endif
	return res;
}

TEST_result_e FastAdcMainTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_ADC_DMA_ENABLED

#endif
	return res;
}

TEST_result_e STSTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_STS_ENABLED
	res = (TEST_result_e) HAL_StsTest();
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

//		if (res == HAL_CAN_RESULT_SUCCESS){
//			res = HAL_CanReceive (&idR, &dataR, &sizeR);
//		}

//		if (res == HAL_CAN_RESULT_SUCCESS){
//			uint8_t data = 33;
//			uint32_t id = 0x099;
//			res = HAL_CanTransmit (id, &data, 1);
//			}

#endif
	return res;
}

TEST_result_e HalMainTest(void){
	TEST_result_e test_res = TEST_RESULT_SUCCESS;
<<<<<<< Updated upstream
	#ifndef EPC_CONF_WDG_ENABLED
		test_res |= PWMMainTest();
		test_res |= GpioMainTest();
		test_res |= SlowAdcMainTest();
		test_res |= FastAdcMainTest();
		test_res |= I2CMainTest();
		test_res |= TimersMainTest();
		test_res |= CanMainTest();
=======
	test_res |= PWMTest();
	test_res |= GpioTest();
	test_res |= SlowAdcTest();
	test_res |= FastAdcTest();
	test_res |= STSTest();
	test_res |= TimersTest();
	test_res |= WDGTest();
	test_res |= CanTest();
>>>>>>> Stashed changes

		HAL_Delay(1000);
	#else
		test_res |= WDGMainTest();
	#endif
	return test_res;
}

TEST_result_e TEST_main(void){
	return HalMainTest();
}

