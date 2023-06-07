/*********************************************************************************
* @file           : hal_adc.h
* @brief          : HAL header file for ADC
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

	HAL_ADC_EXT_TEMP1,		/** ADC1_IN1 - PA5 **/
	HAL_ADC_EXT_TEMP2,		/** ADC1_IN2 - PA4 **/
	HAL_ADC_INT_TEMP,			/** ADC1 Chan Temp **/

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
void HAL_Adc1_Callback(void);
void HAL_Adc2_Callback(void);

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
