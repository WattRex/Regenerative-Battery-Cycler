/*********************************************************************************
* @file           : hal_adc.h
* @brief          : Header file for Hardware Abstraction Layer (HAL) of the ADC
* (Analog-to-Digital Converter).  Defines ADC  result   codes  and  ADC channel
* enumerations.   Provides functions    for ADC initialization   and retrieving
* measurements from  specific ADC channels  using DMA (Direct Memory Access) in
* circular mode.
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
* @version		   : v1.0.1
***********************************************************************************/

#ifndef HAL_ADC_H_
#define HAL_ADC_H_
/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/

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
/*            Definition of exported types (typedef, enum, struct, union)         */
/**********************************************************************************/

/**
 * @enum HAL_ADC_result_e
 * @brief Structure for the result of the ADC operation.
 */
typedef enum
{
	HAL_ADC_RESULT_SUCCESS 	= 0x00U, 	/**< HAL_ADC success operation result **/
	HAL_ADC_RESULT_ERROR	 	= 0x01U,	/**< HAL_ADC error operation result **/
	HAL_ADC_RESULT_BUSY			= 0x02U,	/**< HAL_ADC busy operation result **/
	HAL_ADC_RESULT_TIMEOUT	= 0x03U,	/**< HAL_ADC timeout operation result **/
} HAL_ADC_result_e;


/**
 * @enum HAL_ADC_port_e
 * @brief ADC channels.
 */
typedef enum
{
	HAL_ADC_LS_CURR,			/** ADC2_IN1 - PA4 **/
	HAL_ADC_LS_VOLT,			/** ADC2_IN2 - PA5 **/
	HAL_ADC_HS_VOLT,			/** ADC2_IN4 - PA6 **/

	HAL_ADC_TEMP_ANOD,		/** ADC1_IN1 - PA1 **/
	HAL_ADC_TEMP_AMB,		/** ADC1_IN2 - PA0 **/
	HAL_ADC_INT_TEMP,		/** ADC1 Chan Temp **/

	HAL_ADC_PORT_COUNT 		/**< HAL_ADC_COUNT */
}HAL_ADC_port_e;

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
 * @fn void HAL_TMR_RT_Callback(void)
 * @brief Callback function invoked when the timer RT interrupt occurs due to a counter overflow.
 * User must implement this function for for customized operation.
 */
void HAL_AdcCallbackDMAChl1Cplt(void);
void HAL_AdcCallbackDMAChl2Cplt(void);

/**
 * @fn  HAL_ADC_result_e HAL_AdcInit(void)
 * @brief Initializes and configures ADC1 and ADC2 with the settings and options
 * provides by the processor expert. It uses regular rank with discontinuous measures and
 * a circular sequencer. Each ADC measures 3 channels and is triggered by RT timer (ADC1) and PwrMeas timer (ADC2).
 * To store data uses the DMA in circular mode.
 * @return @ref HAL_ADC_RESULT_SUCCESS if ADCs have been initialized correctly,
 * @ref HAL_ADC_RESULT_ERROR otherwise.
 */
HAL_ADC_result_e HAL_AdcInit (void);

/**
 * @fn HAL_ADC_result_e HAL_AdcGet(HAL_ADC_port_e, uint16_t*)
 * @brief Retrieve the measure of the specified ADC channel
 * @param value Result value of the conversion. 12b resolution. [0-4095]
 * @return @ref HAL_ADC_RESULT_SUCCESS if measure can be be acquired,
 * @ref HAL_ADC_RESULT_ERROR otherwise.
 */
HAL_ADC_result_e HAL_AdcGetValue (const HAL_ADC_port_e port, uint16_t* value);

#endif /* HAL_ADC_H_ */
