/*********************************************************************************
* @file           : mid_pwr.h
* @brief          : Middleware header file for Device ABStraction
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

#ifndef MID_PWR_H_
#define MID_PWR_H_

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
#define MID_PWR_TO_dW 100000// 10^-3(mW) *10^-3 (mW) / 10^-5 -> dW
/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of exported types (typedef, enum, struct, union)         */
/**********************************************************************************/
/**
 * @enum MID_PWR_meas_e
 * @brief Enum of available outputs for MID_PWR.
 *
 */
typedef enum {
	MID_PWR_Disable = 0x00U,
	MID_PWR_Enable = 0x01U
}MID_PWR_Output_e;

/**
 * @enum MID_PWR_Mode_e
 * @brief Enum of available control modes for MID_PWR.
 *
 */
typedef enum{
	MID_PWR_MODE_CC = 0x0u,
	MID_PWR_MODE_CV,
	MID_PWR_MODE_CP,
	MID_PWR_COUNT
}MID_PWR_Mode_e;

/**
 * @enum MID_PWR_result_e
 * @brief Structure of available response values for MID_PWR operations.
 *
 */
typedef enum
{
  MID_PWR_RESULT_SUCCESS = 0x0U,	/**< MID_PWR_RESULT_SUCCESS success operation result */
  MID_PWR_RESULT_ERROR = 0x1U,		/**< MID_PWR_RESULT_ERROR error operation result */
  MID_PWR_RESULT_BUSY = 0x2U,		/**< MID_PWR_RESULT_ERROR busy operation result */
  MID_PWR_RESULT_TIMEOUT = 0x3U,	/**< MID_PWR_RESULT_ERROR timeout operation result */
} MID_PWR_result_e;

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
 * @fn MID_PWR_result_e MID_PwrSetOutput(const MID_PWR_Output_e outputMode)
 * @brief Enable or disable the output pwr.
 * @param outputMode Input variable to use to set the mode 
 * @return @ref MID_PWR_RESULT_SUCCESS if set correctly,
 * 		@ref MID_PWR_RESULT_BUSY, @ref MID_PWR_RESULT_TIMEOUT or
 * 		@ref MID_PWR_RESULT_ERROR otherwise.
 */
MID_PWR_result_e MID_PwrSetOutput(const MID_PWR_Output_e outputMode);

/**
 * @fn MID_PWR_result_e MID_PwrApplyCtrl(const int16_t ref, const uint16_t V_LS, const int16_t I_LS,
 * 									const MID_PWR_Mode_e control_mode, const MID_REG_limit_s limits);
 * @brief This function apply the control type desired, in case is not current it will apply two consecutive PIs,
 *  as the first one will return a reference in current. The current PI will return the duty to apply in the pwm.
 *  All while it checks it is working in the Safe Operating Area, otherwise it will limit the current.
 * @param ref Reference for the PI, in each control mode will refer to a different unit, (Voltage for CV, Power for CP and Current for CC)
 * @param V_Ls, Voltage in the low side of the EPC
 * @param I_ls, Current in the low side of the EPC
 * @param control_mode, Variable to select the control desire to apply, it can be an option out of Control Current, Voltage or Power.
 * @param limits, register where are the limits of the EPC.
 * @return @ref MID_PWR_RESULT_SUCCESS if set correctly,
 * 		@ref MID_PWR_RESULT_BUSY, @ref MID_PWR_RESULT_TIMEOUT or
 * 		@ref MID_PWR_RESULT_ERROR otherwise.
 */
MID_PWR_result_e MID_PwrApplyCtrl(const int16_t ref, const uint16_t V_LS, const int16_t I_LS, const MID_PWR_Mode_e control_mode, const MID_REG_limit_s limits);

/**
 * @fn MID_PWR_result_e MID_PwrCalculateD0(const uint16_t V_HS, const uint16_t V_LS);
 * @brief It will update the internal variable that stores the duty percentage in which the current is 0.
 * @param V_HS Voltage measure in the high side of the EPC
 * @param V_LS Voltage measure in the low side of the EPC
 * @return @ref MID_PWR_RESULT_SUCCESS if set correctly,
 * 		@ref MID_PWR_RESULT_BUSY, @ref MID_PWR_RESULT_TIMEOUT or
 * 		@ref MID_PWR_RESULT_ERROR otherwise.
 */
MID_PWR_result_e MID_PwrCalculateD0(const uint16_t V_HS, const uint16_t V_LS);
#endif /* MID_PWR_H_ */
