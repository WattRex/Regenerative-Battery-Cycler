/*********************************************************************************
* @file           : hal_sys.h
* @brief          : HAL header file for SYS
**********************************************************************************/

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

#ifndef HAL_SYS_H_
#define HAL_SYS_H_

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
 * @enum HAL_SYS_mode_e
 * @brief Structure for the defined micro power modes.
 */
typedef enum
{
	HAL_SYS_MODE_NORMAL = 0x0U,	/**< HAL_SYS_MODE_NORMAL Normal power mode **/
	HAL_SYS_MODE_SLEEP,			/**< HAL_SYS_MODE_SLEEP Sleep power mode **/
	HAL_SYS_MODE_COUNT			/**< HAL_SYS_MODE_COUNT */
}HAL_SYS_mode_e;


/**
 * @enum HAL_SYS_result_e
 * @brief Structure of available response values for HAL_SYS operations.
 */
typedef enum
{
	HAL_SYS_RESULT_SUCCESS 						= 0x0U, 	/**< HAL_SYS success operation result **/
	HAL_SYS_RESULT_ERROR_CRIT 				= 0x01U,	/**< HAL_SYS critical error result **/
	HAL_SYS_RESULT_ERROR_CAN  				= 0x02U,	/**< HAL_SYS error on communication process, CAN **/
	HAL_SYS_RESULT_ERROR_CRIT_PERIPH 	= 0x03U,	/**< HAL_SYS error on operation with critical peripherals **/
}HAL_SYS_result_e;


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
 * @fn HAL_SYS_result_e HAL_SysInit(void)
 * @brief Reset all peripherals, configures CPU, AHB and APB buses clocks to 8MHz
 * and invokes the corresponding initialization functions of the used peripherals.
 * If any initialization fails, a recovery process is initiated.
 * @return 	@ref HAL_SYS_RESULT_SUCCESS, if the initialization was successful and
 * @ref HAL_SYS_RESULT_ERROR, @ref HAL_SYS_RESULT_BUSY or @ref HAL_SYS_result_TIMEOUT
 * if initialization and recovery of any peripheral failed.
 */
HAL_SYS_result_e HAL_SysInit(void);

/**
 * @fn void HAL_SysResume(void)
 * @brief Resume the uC after a low power mode
 * */
void HAL_SysResume(void);

/**
 * @fn HAL_SYS_result_e HAL_SysPwrMode(HAL_SYS_mode_e)
 * @brief The micro enters on power save mode.
 *
 * @param mode Power mode used
 * @return @ref HAL_SYS_RESULT_SUCCESS if power mode changed correctly and
 * @ref HAL_SYS_RESULT_ERROR otherwise.
 */
HAL_SYS_result_e HAL_SysPwrMode(HAL_SYS_mode_e mode);

/**
 * @fn HAL_SYS_result_e HAL_SysReset(void)
 * @brief Performs an hard or soft reset on the micro and peripherals.
 *
 * @return @ref HAL_SYS_RESULT_ERROR if action cannot be applied.
 */
HAL_SYS_result_e HAL_SysReset (void);

#endif /* HAL_SYS_H_ */
 
