/*********************************************************************************
* @file           : hal_sts.h
* @brief          : Header file for Hardware Abstraction Layer (HAL) of the STS
* (Temperature Sensor).  Provides functions   for initializing  the temperature
* sensor   and  reading the   temperature   data   from  the  sensor  using I2C
* communication.  The sensor is configured to  measure  temperature with  a low
* repeatability of deci degrees Celsius.
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

#ifndef HAL_STS_H_
#define HAL_STS_H_

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
 
