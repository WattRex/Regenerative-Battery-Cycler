/*********************************************************************************
* @file           : hal_wdg.h
* @brief          : HAL header file for Watchdog
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

#ifndef HAL_WDG_H_
#define HAL_WDG_H_

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
 * @enum HAL_WDG_result_e
 * @brief Structure for the result of the WDG operation.
 */
typedef enum
{
	HAL_WDG_RESULT_SUCCESS 	= 0x00U,	/**< HAL_WDG success operation result **/
	HAL_WDG_RESULT_ERROR   	= 0x01U,	/**< HAL_WDG error operation result **/
	HAL_WDG_RESULT_BUSY		= 0x02U,	/**< HAL_WDG busy operation result **/
	HAL_WDG_RESULT_TIMEOUT	= 0x03U	/**< HAL_WDG timeout operation result **/
}HAL_WDG_result_e;

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
 * @fn HAL_WDG_result_e HAL_WdgInit()
 * @brief Configure and initializes the watchdog for reset ever 500s if it is not
 * refreshed.
 *
 * @return
 * 		@ref HAL_WDG_RESULT_SUCCESS if initialized correctly,
 * 		@ref HAL_WDG_RESULT_ERROR otherwise
 */
HAL_WDG_result_e HAL_WdgInit(void);

/**
 * @fn HAL_WDG_result_e HAL_WdgRefresh()
 * @brief Refresh the watchdog counter.
 * @return
 * 		@ref HAL_WDG_RESULT_SUCCESS if initialized correctly,
 * 		@ref HAL_WDG_RESULT_ERROR otherwise
 */
HAL_WDG_result_e HAL_WdgRefresh(void);

#endif /* HAL_WDG_H_ */
