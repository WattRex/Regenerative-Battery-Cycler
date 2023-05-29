/*********************************************************************************
* @file           : app_salg.h
* @brief          : APP header file for SALG
**********************************************************************************
* @attention
* Research Laboratory in Fluid Dynamics and Combustion Technologies (LIFTEC)
*   Spanish National Research Council (CSIC)
*   c/ María de Luna 10, 50018 Zaragoza, Spain
*
*   All rights reserved. Distribution or duplication without previous
*   written agreement of the owner prohibited.
***********************************************************************************/

#ifndef APP_SALG_H_
#define APP_SALG_H_
/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "epc_conf.h"
#include "hal_sys.h"
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
 * @enum APP_SALG_result_t
 * @brief Structure for the result of the APP SALG operation.
 */
typedef enum
{
	APP_SALG_RESULT_SUCCESS = 0x0U, 		/**< APP_SALG success operation result **/
	APP_SALG_RESULT_ERROR_INIT 	= 0x01U,	/**< APP_SALG critical error on peripheral initialization **/
	APP_SALG_RESULT_ERROR_COMM 	= 0x02U,	/**< APP_SALG error on communication process, CAN or UART **/
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

APP_SALG_result_e APP_SalgInit();

APP_SALG_result_e APP_SalgStatusMachine();

#endif /* APP_SALG_H_ */
