/*********************************************************************************
* @file           : hal_gpio.h
* @brief          : HAL header file for GPIO
**********************************************************************************
* @attention
* Research Laboratory in Fluid Dynamics and Combustion Technologies (LIFTEC)
*   Spanish National Research Council (CSIC)
*   c/ María de Luna 10, 50018 Zaragoza, Spain
*
*   All rights reserved. Distribution or duplication without previous
*   written agreement of the owner prohibited.
***********************************************************************************/

#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_
/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/

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
/*            Definition of exported types (typedef, enum, struct, union)         */
/**********************************************************************************/

/**
 * @enum HAL_GPIO_pin_value_e
 * @brief Structure for the available values for GPIO pins.
 */
typedef enum
{
	HAL_GPIO_LOW = 0x0U,	/**< HAL_GPIO low/reset value **/
	HAL_GPIO_HIGH   		/**< HAL_GPIO high/set value  **/
}HAL_GPIO_pin_value_e;


/**
 * @enum HAL_GPIO_result_e
 * @brief Structure for the result of the GPIO operation.
 */
typedef enum
{
	HAL_GPIO_RESULT_SUCCESS = 0x0U, /**< HAL_GPIO success operation result **/
	HAL_GPIO_RESULT_ERROR 			/**< HAL_GPIO error operation result **/
}HAL_GPIO_result_e;


/**
 * @enum HAL_GPIO_output_e
 * @brief GPIO pins configured as output.
 */
typedef enum
{
	// uC right side
	HAL_GPIO_OUT_OutDisable = 0,		/**<   	DRMOS- OUT Disable - PA9	**/

	// uC bottom side
	HAL_GPIO_OUT_Led0,		/**<   	STATUS LED 0 GPIO - PC4  **/
	HAL_GPIO_OUT_Led1,		/**<  	STATUS LED 1 GPIO - PC5  **/
	HAL_GPIO_OUT_Led2,		/**<  	STATUS LED 2 GPIO - PB0 **/
	HAL_GPIO_OUT_Led3,		/**<  	STATUS LED 3 GPIO - PB1 **/

	// uC left side

	// uC top side


	HAL_GPIO_OUT_COUNT				/**< 	HAL_GPIO_OUT_COUNT */
}HAL_GPIO_output_e;


/**
 * @enum HAL_GPIO_input_e
 * @brief GPIO pins configured as input.
 */
typedef enum
{
	HAL_GPIO_IN_ThermalWarn,		/**<  DRMOS - Thermal Warn - PA10 **/
	HAL_GPIO_IN_Status3v3,			/**<  DC/DC 3v3 Status	 - PB14 **/
	HAL_GPIO_IN_Status5v0,			/**<  DC/DC 5v0 Status - PB15	**/
	HAL_GPIO_IN_COUNT				/**<  HAL_GPIO_IN_COUNT */
}HAL_GPIO_input_e;

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                   Declaration of exported function prototypes                  */
/**********************************************************************************/

/**
 * @fn void HAL_GpioInit(void)
 * @brief Configures the GPIO input/output pins used to read input signals and
 * control the MUX.
 * @return @ref HAL_GPIO_RESULT_SUCCESS if initialize correctly,
 * @ref HAL_GPIO_RESULT_ERROR otherwise.
 */
HAL_GPIO_result_e HAL_GpioInit(void);


/**
 * @fn HAL_GPIO_result_e HAL_GpioSet(HAL_GPIO_output_e, HAL_GPIO_pin_value_e*)
 * @brief Set the value for the indicated GPIO pin.
 *
 * @param pin GPIO output pin to set.
 * @param value Value [@ref HAL_GPIO_LOW, @ref HAL_GPIO_HIGH] assigned to the GPIO pin.
 * @return @ref HAL_GPIO_RESULT_SUCCESS if the assignment was correctly,
 * @ref HAL_GPIO_RESULT_ERROR otherwise.
 */
HAL_GPIO_result_e HAL_GpioSet(HAL_GPIO_output_e pin, HAL_GPIO_pin_value_e value);


/**
 * @fn HAL_GPIO_pin_value_e HAL_GpioGet(HAL_GPIO_input_t, HAL_GPIO_pin_value_e*)
 * @brief Read the value from the indicated GPIO pin.
 *
 * @param pin GPIO input pin used to perform the read operation.
 * @param value Result read from the GPIO pin.
 * @return @ref HAL_GPIO_RESULT_SUCCESS if the read was correctly,
 * @ref HAL_GPIO_RESULT_ERROR otherwise.
 */
HAL_GPIO_result_e HAL_GpioGet (HAL_GPIO_input_e pin, HAL_GPIO_pin_value_e *value);

#endif /* HAL_GPIO_H_ */
