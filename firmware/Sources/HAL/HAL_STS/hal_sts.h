/*********************************************************************************
* @file           : hal_sts.h
* @brief          : HAL header file for STS
***********************************************************************************/

#ifndef HAL_STS_H_
#define HAL_STS_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include "stdint.h"
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
 * @enum HAL_STS_result_t
 * @brief Structure for the result of the STS operation.
 */
typedef enum
{
	HAL_STS_RESULT_SUCCESS = 0x00U, 	/**< HAL_SYS success operation result **/
	HAL_STS_RESULT_ERROR = 0x01U,	/**< HAL_SYS error on GPIO operation **/
	HAL_STS_RESULT_BUSY  = 0x02U,	/**< HAL_SYS error on ADC operation  **/
	HAL_STS_RESULT_TIMEOUT  = 0x03U,	/**< HAL_SYS error on STS operation  **/
}HAL_STS_result_e;


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
/*                   Declaration of local function prototypes                  */
/**********************************************************************************/

/**********************************************************************************/
/*                   Declaration of exported function prototypes                  */
/**********************************************************************************/

/**
 * @fn HAL_STS_result_t HAL_SdsInit()
 * @brief Configure and initializes the STS
 *
 * @return
 * 		@ref HAL_STS_RESULT_SUCCESS if initialized correctly,
 * 		@ref HAL_STS_RESULT_ERROR otherwise
 */
HAL_STS_result_e HAL_StsInit(void);

/**
 * @fn HAL_STS_result_t HAL_SdsReadTemperature(uint16_t* temp)
 * @brief Transfer the data
 * @return
 * 		@ref HAL_STS_RESULT_SUCCESS if initialized correctly,
 * 		@ref HAL_STS_RESULT_ERROR otherwise
 */
HAL_STS_result_e HAL_StsReadTemperature(int16_t* temp);

#endif /* HAL_STS_H_ */
 
