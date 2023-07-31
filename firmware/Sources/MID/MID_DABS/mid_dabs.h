/*********************************************************************************
* @file           : mid_dabs.h
* @brief          : Middleware header file for Device ABStraction
  This module will be in charge of updating the register with the measured 
  data without actually knowing how it is gathered. 
  Also it has the aim of updating the leds status according to the working mode and errors.
***********************************************************************************/

/*********************************************************************************
*	
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
*@author           : WattRex <https://github.com/WattRex/>
*@date			   : 2023-07-04
*@version		   : v1.0.0
***********************************************************************************/

#ifndef MID_DABS_H_
#define MID_DABS_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "mid_reg.h"
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
 * @enum MID_DABS_meas_e
 * @brief Enum of available measures for MID_DABS operations.
 *
 */
typedef enum {
	MID_DABS_MEAS_ELECTRIC = 0x00U,
	MID_DABS_MEAS_TEMP = 0x01U
}MID_DABS_meas_e;

/**
 * @enum MID_DABS_result_e
 * @brief Structure of available response values for MID_DABS operations.
 *
 */
typedef enum
{
  MID_DABS_RESULT_SUCCESS = 0x0U,	/**< MID_DABS_RESULT_SUCCESS success operation result */
  MID_DABS_RESULT_ERROR = 0x1U,		/**< MID_DABS_RESULT_ERROR error operation result */
  MID_DABS_RESULT_BUSY = 0x2U,		/**< MID_DABS_RESULT_ERROR busy operation result */
  MID_DABS_RESULT_TIMEOUT = 0x3U,	/**< MID_DABS_RESULT_ERROR timeout operation result */
} MID_DABS_result_e;

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
 * @fn MID_DABS_result_e MID_DabsUpdateMeas(const MID_DABS_meas_e type,
 * 									MID_REG_meas_property_s * measreg)
 * @brief Get measurements from the type specified, electrical or temperatures, 
 *  from the adc and converts them into the specific values.
 *
 * @param type, specific type of measurement to update.
 * @param measreg, Pointer to the register where the measures are stored.
 * @return @ref MID_DABS_RESULT_SUCCESS if measured correctly,
 * 		@ref MID_DABS_RESULT_BUSY, @ref MID_DABS_RESULT_TIMEOUT or
 * 		@ref MID_DABS_RESULT_ERROR otherwise.
 */
MID_DABS_result_e MID_DabsUpdateMeas(const MID_DABS_meas_e type,
							MID_REG_meas_property_s * measreg);

/**
 * @fn MID_DABS_result_e MID_DabsUpdateLeds(MID_REG_mode_e ctrlMode, int16_t curr,
 * 								MID_REG_error_status_s * errors)
 * @brief Update Leds to show the state/mode of the epc
 *
 * @param ctrlMode, Mode in which the epc is working on, could be CC, CV, y CP.
 * @param curr, Actual measurement of the current in the low side.
 * @param errors, Register where the different type of errors are stored.
 * @return @ref MID_DABS_RESULT_SUCCESS if update successfully,
 * 		@ref MID_DABS_RESULT_BUSY, @ref MID_DABS_RESULT_TIMEOUT or
 * 		@ref MID_DABS_RESULT_ERROR otherwise.
 */
MID_DABS_result_e MID_DabsUpdateLeds(MID_REG_mode_e ctrlMode, int16_t curr,
								MID_REG_error_status_s * errors);

#endif /* MID_DABS_H_ */
