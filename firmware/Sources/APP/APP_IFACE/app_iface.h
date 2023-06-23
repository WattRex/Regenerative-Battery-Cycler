/*********************************************************************************
* @file           : app_iface.h
* @brief          : APP header file for IFACE
**********************************************************************************/

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
APP_IFACE_result_e AppIfacePeriodicRegister ();

// It is invoked each 1 ms
APP_IFACE_result_e APP_IfaceIncommingMsg(MID_REG_control_s const *  const control,
	MID_REG_meas_property_s const * const meas, MID_REG_error_status_s * status,
	MID_REG_limit_s * limits, MID_REG_control_s *consign);

// It is invoked each 1 ms
APP_IFACE_result_e APP_IfaceProcessPeriodic(MID_REG_meas_property_s * const meas,
	MID_REG_error_status_s *  const status);

// It is invoked each 1 ms
APP_IFACE_result_e APP_IfaceNotifyModeChange (MID_REG_control_s const * const control);

#endif /* APP_IFACE_H_ */
