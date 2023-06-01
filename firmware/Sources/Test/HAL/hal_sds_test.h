/*********************************************************************************
* @file           : hal_sys.h
* @brief          : HAL header file for I2C TEST
***********************************************************************************/

#ifndef HAL_I2C_TEST_H_
#define HAL_I2C_TEST_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "hal_sds.h"
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
 * @fn HAL_I2C_result_t HAL_I2cTest()
 * @brief Try to read 5 times in a row from the sensor,
 * if any read gets error it stops and return a error result
 *
 * @return
 * 		@ref HAL_I2C_RESULT_SUCCESS if initialized correctly,
 * 		@ref HAL_I2C_RESULT_ERROR otherwise
 */
HAL_SDS_result_e HAL_SdsTest(void);

#endif /* HAL_I2C_TEST_H_ */
 