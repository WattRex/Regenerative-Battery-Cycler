/*********************************************************************************
* @file           : hal_gpio.c
* @brief          : Implementation of HAL GPIO
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
#include "stm32f3xx_hal.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_gpio.h"
#include "gpio.h"
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

/**
 * @struct GPIO_pinout_config_t
 * @brief Tuple of GPIO pin and GPIO peripheral port: GPIO[A-F]
 */
typedef struct
{
	const  uint16_t pin;   		/**< GPIO pin*/
	GPIO_TypeDef *peripheral;	/**< GPIO Peripheral GPIOx[A-F]*/
}GPIO_pinout_config_t;

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

/**
 * Configuration struct for available output GPIO pins (@ref HAL_GPIO_output_e)
 */
const GPIO_pinout_config_t _GPIO_output_pins[]={
		// uC right side
		{Out_Disable_Pin, Out_Disable_GPIO_Port},			/**< @ref HAL_GPIO__OUT_Out_Disable - PA9 	**/

		// uC bottom side
		{Led0_Pin, Led0_GPIO_Port},			/**< @ref HAL_GPIO_OUT_Led0 - PC4	**/
		{Led1_Pin, Led1_GPIO_Port},			/**< @ref HAL_GPIO_OUT_Led1 - PC5	**/
		{Led2_Pin, Led2_GPIO_Port},			/**< @ref HAL_GPIO_OUT_Led2 - PB0	**/
		{Led3_Pin, Led3_GPIO_Port}				/**< @ref HAL_GPIO_OUT_Led3 - PB1	**/
};

/**
 * Configuration struct for available input GPIO pins (@ref HAL_GPIO_input_e)
 */
const GPIO_pinout_config_t _GPIO_input_pins[]={
		{Thermal_Warn_Pin, Thermal_Warn_GPIO_Port},	/**< @ref HAL_GPIO_IN_ThermalWarn - PA10 **/
		{Status_3v3_Pin, Status_3v3_GPIO_Port},	/**< @ref HAL_GPIO_IN_Status3v3 - PB14 **/
		{Status_5v0_Pin, Status_5v0_GPIO_Port}	/**< @ref HAL_GPIO_IN_Status5v0 - PB15 **/
};


/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

HAL_GPIO_result_e HAL_GpioInit(void){
	error_raised = 0;
	MX_GPIO_Init();
	if (error_raised == 1){
		return HAL_GPIO_RESULT_ERROR;
	}
	return HAL_GPIO_RESULT_SUCCESS;
}


HAL_GPIO_result_e HAL_GpioSet(HAL_GPIO_output_e pin, HAL_GPIO_pin_value_e value){

	HAL_GPIO_result_e res = HAL_GPIO_RESULT_ERROR;
	if(pin < HAL_GPIO_OUT_COUNT){
		HAL_GPIO_WritePin(_GPIO_output_pins[pin].peripheral, _GPIO_output_pins[pin].pin, value);
		res = HAL_GPIO_RESULT_SUCCESS;
	}
	return res;
}

HAL_GPIO_result_e HAL_GpioGet (HAL_GPIO_input_e pin, HAL_GPIO_pin_value_e *value){

	HAL_GPIO_result_e res = HAL_GPIO_RESULT_ERROR;
	if(pin < HAL_GPIO_IN_COUNT){
		*value = HAL_GPIO_ReadPin(_GPIO_input_pins[pin].peripheral, _GPIO_input_pins[pin].pin);
		res = HAL_GPIO_RESULT_SUCCESS;
	}
	return res;
}
