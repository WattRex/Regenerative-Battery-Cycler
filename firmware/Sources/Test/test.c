/*********************************************************************************
* @file           : test.c
* @brief          : Implementation of testing file
**********************************************************************************

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

#ifdef EPC_CONF_I2C_ENABLED
	#include "hal_i2c_test.h"
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

TEST_result_e PWMTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_PWM_ENABLED

#endif
	return res;
}

TEST_result_e GpioTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_GPIO_ENABLED
	 res = (TEST_result_e) HAL_GpioTest(HAL_GPIO_OUT_OutDisable, HAL_GPIO_IN_ThermalWarn);
#endif
	return res;
}

TEST_result_e SlowAdcTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_ADC_DMA_ENABLED

#endif
	return res;
}

TEST_result_e FastAdcTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_ADC_DMA_ENABLED

#endif
	return res;
}

TEST_result_e I2CTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_I2C_ENABLED

#endif
	return res;
}

TEST_result_e TimersTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_TMR_ENABLED

#endif
	return res;
}

TEST_result_e WDGTest(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_WDG_ENABLED

#endif
	return res;
}

TEST_result_e CanTest(void){
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

TEST_result_e HalTest(void){
	TEST_result_e test_res = TEST_RESULT_SUCCESS;
	test_res |= PWMTest();
	test_res |= GpioTest();
	test_res |= SlowAdcTest();
	test_res |= FastAdcTest();
	test_res |= I2CTest();
	test_res |= TimersTest();
	test_res |= WDGTest();
	test_res |= CanTest();

	HAL_Delay(1000);
	return test_res;
}

TEST_result_e TEST_main(void){
	return HalTest();
}

