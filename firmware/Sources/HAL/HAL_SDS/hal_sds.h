/*********************************************************************************
* @file           : hal_sys.h
* @brief          : HAL header file for SYS
***********************************************************************************/

#ifndef HAL_SDS_H_
#define HAL_SDS_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "i2c.h"
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
 * @enum HAL_SDS_result_t
 * @brief Structure for the result of the SDS operation.
 */
typedef enum
{
	HAL_SDS_RESULT_SUCCESS = 0x00U, 	/**< HAL_SYS success operation result **/
	HAL_SDS_RESULT_ERROR = 0x01U,	/**< HAL_SYS error on GPIO operation **/
	HAL_SDS_RESULT_BUSY  = 0x02U,	/**< HAL_SYS error on ADC operation  **/
	HAL_SDS_RESULT_TIMEOUT  = 0x03U,	/**< HAL_SYS error on SDS operation  **/
}HAL_SDS_result_e;


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
 * @fn HAL_SDS_result_t HAL_SdsInit()
 * @brief Configure and initializes the SDS
 *
 * @return
 * 		@ref HAL_SDS_RESULT_SUCCESS if initialized correctly,
 * 		@ref HAL_SDS_RESULT_ERROR otherwise
 */
HAL_SDS_result_e HAL_SdsInit(void);

/**
 * @fn HAL_SDS_result_t HAL_SdsReadTemperature(uint16_t* temp)
 * @brief Transfer the data
 * @return
 * 		@ref HAL_SDS_RESULT_SUCCESS if initialized correctly,
 * 		@ref HAL_SDS_RESULT_ERROR otherwise
 */
HAL_SDS_result_e HAL_SdsReadTemperature(uint16_t* temp);

#endif /* HAL_SDS_H_ */
 
