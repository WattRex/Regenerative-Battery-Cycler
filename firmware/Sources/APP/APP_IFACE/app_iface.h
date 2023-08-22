/*********************************************************************************
* @file             : app_iface.h
* @brief            : Header file for Application (APP) Communications Interface
* (IFACE) module. Implements the interface between the main management logic and
* the communication module. It handles  incoming messages, periodic updates, and
* callbacks for control mode, configuration, and limit changes.  It communicates
* with the communication module to exchange data with external users.
**********************************************************************************/

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

#ifndef APP_IFACE_H_
#define APP_IFACE_H_
/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "mid_reg.h"

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
 * @enum APP_IFACE_result_e
 * @brief Structure for the result of the APP IFACE operation.
 */
typedef enum
{
	APP_IFACE_RESULT_SUCCESS	= 0x0U,		/**< APP_IFACE success operation result **/
	APP_IFACE_RESULT_ERROR		= 0x01U,	/**< APP_IFACE error on communication operation **/
} APP_IFACE_result_e;

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
 * @fn APP_IFACE_result_e AppIfaceInit()
 * @brief Function to initialize the periodicconfig register,
 * it has to be initialized in run because the definition of limit ranges
 * in EPC_CONF as an struct makes it impossible for the linker to understand that in
 * EPC_CONF this memory zones are signed to the defines in this module.
 * This function also initializes the midcommInit which configures the filters for CAN
 *
 * @return @ref APP_IFACE_RESULT_SUCCESS if the assignment was correctly and filters added correctly,
 * @ref APP_IFACE_RESULT_ERROR otherwise.
 */
APP_IFACE_result_e AppIfaceInit();


/**
 * @fn APP_IFACE_result_e APP_IfaceIncommingMsg(MID_REG_control_s const *  const control,
	MID_REG_meas_property_s const * const meas, MID_REG_error_status_s * status,
	MID_REG_limit_s * limits, MID_REG_control_s *consign)
 * @brief Function invoked each 1ms.
 * Its purpose is to process the incoming messages and update if needed the registers.
 *
 * @param control, pointer to the control register
 * @param meas, pointer to the measures register
 * @param status, pointer to the status register
 * @param limits, pointer to the limit register
 * @param consign, pointer to the consign register
 * @return @ref APP_IFACE_RESULT_SUCCESS if the messages were correct
 * and was able to respond back with the corresponding message,
 * @ref APP_IFACE_RESULT_ERROR otherwise.
 */
APP_IFACE_result_e APP_IfaceIncommingMsg(MID_REG_control_s const *  const control,
	MID_REG_meas_property_s const * const meas, MID_REG_error_status_s * status,
	MID_REG_limit_s * limits, MID_REG_control_s *consign);

/**
 * @fn APP_IFACE_result_e APP_IfaceProcessPeriodic(MID_REG_meas_property_s * const meas,
			MID_REG_error_status_s *  const status)
 * @brief Function invoked each 1ms.
 * It has to check if periodic is enable and send the periodic values required
 * when the period is satisfied
 *
 * @param meas, pointer to the measures register
 * @param status, pointer to the status register
 * @return @ref APP_IFACE_RESULT_SUCCESS if messages send correctly,
 * @ref APP_IFACE_RESULT_ERROR otherwise.
 */
APP_IFACE_result_e APP_IfaceProcessPeriodic(MID_REG_meas_property_s * const meas,
	MID_REG_error_status_s *  const status);

/**
 * @fn APP_IFACE_result_e APP_IfaceNotifyModeChange (MID_REG_control_s const * const control)
 * @brief Function invoked each 1ms.
 * It has to send the actual control the epc has.
 *
 * @param control, pointer to the control register
 * @return @ref APP_IFACE_RESULT_SUCCESS if messages send correctly,
 * @ref APP_IFACE_RESULT_ERROR otherwise.
 */
APP_IFACE_result_e APP_IfaceNotifyModeChange (MID_REG_control_s const * const control);

#endif /* APP_IFACE_H_ */
