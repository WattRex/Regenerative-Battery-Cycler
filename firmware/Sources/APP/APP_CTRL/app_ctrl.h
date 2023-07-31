/*********************************************************************************
* @file           : app_ctrl.h
* @brief          : Header file for Application (APP) Power Control (CTRL)
* module. Implements the control logic for power management. It checks and
* applies control  modes, handles limits,    and updates the  power output
* accordingly.
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

#ifndef APP_CTRL_H_
#define APP_CTRL_H_

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
 * @enum APP_CTRL_result_e
 * @brief Structure for the result of the APP CTRL operations.
 */
typedef enum
{
	APP_CTRL_RESULT_SUCCESS 	= 0x0U, 	/**< APP_CTRL success operation result **/
	APP_CTRL_RESULT_ERROR_RAISED	= 0x01U,	/**< APP_CTRL error found**/
	APP_CTRL_RESULT_ERROR_INT	= 0x02U		/**< APP_CTRL error in calculus **/
} APP_CTRL_result_e;

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
 * @fn APP_CTRL_result_e APP_CtrlCheckErrors(MID_REG_error_status_s,
 * MID_REG_meas_property_s, MID_REG_limit_s )
 * @brief Check if there is some value in measures above or below limits and updates
 * the error register
 * @return @ref APP_CTRL_RESULT_SUCCESS if no errors, APP_CTRL_RESULT_ERROR_RAISED if
 * errors found and APP_CTRL_RESULT_ERROR_INT if any error in comparison
 */
APP_CTRL_result_e APP_CtrlCheckErrors (MID_REG_error_status_s *, const MID_REG_meas_property_s *, const MID_REG_limit_s *);

/**
 * @fn APP_CTRL_result_e APP_CtrlUpdate(MID_REG_control_s,
 * MID_REG_meas_property_s, MID_REG_limit_s )
 * @brief Update internal PIs and apply control to PWM. If limit is reached, stop PWM
 * @return @ref APP_CTRL_RESULT_SUCCESS if no errors, APP_CTRL_RESULT_ERROR_INT if
 * errors in calculus or MID_PWR results
 */
APP_CTRL_result_e APP_CtrlUpdate (MID_REG_control_s *, const MID_REG_meas_property_s *, const MID_REG_limit_s *);

/**
 * @fn APP_CTRL_result_e APP_CtrlApplyNewMode(MID_REG_control_s,
 * MID_REG_control_s)
 * @brief Reset ctrl internal variables and set the module to apply the new control mode
 * @return @ref APP_CTRL_RESULT_SUCCESS if no errors, APP_CTRL_RESULT_ERROR_INT if
 * any error
 */
APP_CTRL_result_e APP_CtrlApplyNewMode (const MID_REG_control_s *, MID_REG_control_s *, const MID_REG_meas_property_s *);



#endif /* APP_APP_CTRL_APP_CTRL_H_ */
