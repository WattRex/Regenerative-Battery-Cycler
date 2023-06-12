/*********************************************************************************
* @file           : app_iface.c
* @brief          : Implementation of APP IFACE
**********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include <stdlib.h>

#include "app_iface.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include "mid_reg.h"

/**********************************************************************************/
/*                      Definition of imported constant data                      */
/**********************************************************************************/
extern const MID_REG_limit_s EPC_CONF_limit_range; //used to check new limits
extern const MID_REG_periodic_period_s EPC_CONF_periodic_time_min; //used to check new limits and init APP_IFACE_periodic

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/

MID_REG_periodic_s APP_IFACE_periodic = {};

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/

/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

/*This register has to be initialized in run because the definition of limit ranges
 * in EPC_CONF as an struct makes it impossible for the linker to understand that in
 * EPC_CONF this memory zones are signed to the defines in this module.*/
APP_IFACE_result_e AppIfacePeriodicRegister () {

	/*		APP_IFACE_periodic  	*/
	APP_IFACE_periodic.period.usrHeartBeat = EPC_CONF_periodic_time_min.usrHeartBeat;
	APP_IFACE_periodic.period.electricMsg  = EPC_CONF_periodic_time_min.electricMsg;
	APP_IFACE_periodic.period.tempMsg      = EPC_CONF_periodic_time_min.tempMsg;
	APP_IFACE_periodic.status.usrHeartBeat	= MID_REG_DISABLED;
	APP_IFACE_periodic.status.electricMsg	= MID_REG_DISABLED;
	APP_IFACE_periodic.status.tempMsg		= MID_REG_DISABLED;

	return APP_IFACE_RESULT_SUCCESS;
}
