/*********************************************************************************
* @file           : hal_gpio.c
* @brief          : Implementation of Hardware Abstraction Layer (HAL) of the
* GPIO  (General  Purpose   Input/Output).    Provides  functions    for GPIO
* initialization,  setting  output  pins,  and  reading input  pins. Includes
* configurations for available input and output GPIO pins.
***********************************************************************************/

/*********************************************************************************
*	Copyright (C) 2023  WattRex <https://github.com/WattRex/>
*
*	This program  is free software: you  can redistribute it and/or modify it under
*	the terms of the GNU Affero General  Public  License  as published  by the Free
*	Software  Foundation, either version 3 of the License, or (at  your option) any
*	later  version.  This program  is   distributed  in  the hope that  it  will be
*	useful,but   WITHOUT  ANY  WARRANTY;   without  even  the implied   warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General
*	Public License for more details. You should   have  received a copy  of the GNU
*	Affero   General  Public License  along   with  this  program.     If  not, see
*	<https://www.gnu.org/licenses/>.
*	
*	This file is part of PowerTower, Regenerative Battery Cycler in
*	<https://github.com/WattRex/Regenerative-Battery-Cycler/>
*
* @author          : WattRex <https://github.com/WattRex/>
* @date			   : 2023-07-04
* @version		   : v1.0.0
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_gpio.h"
#include "gpio.h"
#include "epc_st_err.h" //Import EPC_ST_ERR_COUNTER

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
/*                        Definition of imported variables                        */
/**********************************************************************************/
extern uint8_t EPC_ST_ERR_COUNTER;

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
	HAL_GPIO_result_e res = HAL_GPIO_RESULT_SUCCESS;
	EPC_ST_ERR_COUNTER = 0;
	MX_GPIO_Init();
	if (EPC_ST_ERR_COUNTER){
		res = HAL_GPIO_RESULT_ERROR;
	}
	return res;
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
