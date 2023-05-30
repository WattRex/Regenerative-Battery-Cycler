/*********************************************************************************
* @file           : test.c
* @brief          : Implementation of testing file
**********************************************************************************
* @attention
* Research Laboratory in Fluid Dynamics and Combustion Technologies (LIFTEC)
*   Spanish National Research Council (CSIC)
*   c/ María de Luna 10, 50018 Zaragoza, Spain
*
*   All rights reserved. Distribution or duplication without previous
*   written agreement of the owner prohibited.
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "epc_conf.h"

#ifdef EPC_CONF_PWM_ENABLED
	#include "hal_pwm.h"
#endif

#ifdef EPC_CONF_GPIO_ENABLED
	#include "hal_gpio_test.h"
#endif

#ifdef EPC_CONF_ADC_DMA_ENABLED
	#include "hal_adc.h"
#endif

#ifdef EPC_CONF_I2C_ENABLED
	#include "hal_i2c.h"
#endif

#ifdef EPC_CONF_TMR_ENABLED
	#include "hal_tmr.h"
#endif

#ifdef EPC_CONF_WDG_ENABLED
	#include "hal_wdg.h"
#endif

#ifdef EPC_CONF_CAN_ENABLED
	#include "hal_can.h"
#endif

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "Test.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include <stdint.h>

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
#ifdef EPC_CONF_PWM_ENABLED
#endif

#ifdef EPC_CONF_GPIO_ENABLED
	#include "hal_gpio_test.h"
#endif

#ifdef EPC_CONF_ADC_DMA_ENABLED
#endif

#ifdef EPC_CONF_I2C_ENABLED

#endif

#ifdef EPC_CONF_TMR_ENABLED
#endif

#ifdef EPC_CONF_WDG_ENABLED
#endif

#ifdef EPC_CONF_CAN_ENABLED
		HAL_CAN_result_e res;
		uint8_t dataR = 0;
		uint8_t sizeR = 0;
		uint32_t idR = 0;
#endif

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

TEST_result_e Test_PWM(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_PWM_ENABLED

#endif
	return res;
}

TEST_result_e Test_GPIO(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_GPIO_ENABLED
	 res = (TEST_result_e) HAL_GpioTest(HAL_GPIO_OUT_OutDisable, HAL_GPIO_IN_ThermalWarn);
#endif
	return res;
}

TEST_result_e Test_SlowAdc(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_ADC_DMA_ENABLED

#endif
	return res;
}

TEST_result_e Test_FastAdc(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_ADC_DMA_ENABLED

#endif
	return res;
}

TEST_result_e Test_I2C(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_I2C_ENABLED

#endif
	return res;
}

TEST_result_e Test_Timers(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_TMR_ENABLED

#endif
	return res;
}

TEST_result_e Test_WDG(void){
	TEST_result_e res = TEST_RESULT_SUCCESS;
#ifdef EPC_CONF_WDG_ENABLED

#endif
	return res;
}

TEST_result_e Test_Can(void){
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

TEST_result_e Test_HAL(void){
	TEST_result_e test_res = TEST_RESULT_SUCCESS;
	test_res |= Test_PWM();
	test_res |= Test_GPIO();
	test_res |= Test_SlowAdc();
	test_res |= Test_FastAdc();
	test_res |= Test_I2C();
	test_res |= Test_Timers();
	test_res |= Test_WDG();
	test_res |= Test_Can();
	return test_res;
}
