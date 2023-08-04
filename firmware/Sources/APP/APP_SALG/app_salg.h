/*********************************************************************************
* @file             : app_salg.c
* @brief            : Header file for Application (APP) System Algorithms (SALG)
* module.  It handles control   actions,   error  handling,    and communication
* processing.   The  module  is   responsible   for  calling   power algorithms,
* measurements, and controlling the output based on predefined limits and modes.
* The code includes initialization functions, interrupt callbacks, and  a status
* machine to handle periodic tasks.
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

#ifndef APP_SALG_H_
#define APP_SALG_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/

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
 * @enum APP_SALG_result_e
 * @brief Structure for the result of the APP SALG operation.
 */
typedef enum
{
	APP_SALG_RESULT_SUCCESS = 0x0U, 	/**< APP_SALG success operation result **/
	APP_SALG_RESULT_ERROR		= 0x01U,			/**< APP_SALG critical error on communication **/
	APP_SALG_RESULT_BUSY 		= 0x2U,			/**< APP_SALG busy operation result */
	APP_SALG_RESULT_TIMEOUT = 0x3U,		/**< APP_SALG timeout operation result */
} APP_SALG_result_e;

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
void APP_SalgIntError();

APP_SALG_result_e APP_SalgInit();

APP_SALG_result_e APP_SalgStatusMachine();

#endif /* APP_SALG_H_ */
