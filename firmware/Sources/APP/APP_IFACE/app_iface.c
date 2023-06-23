/*********************************************************************************
* @file           : app_iface.c
* @brief          : Implementation of APP IFACE
**********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "app_iface.h"
#include "mid_comm.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include "mid_reg.h"

/**********************************************************************************/
/*                      Definition of imported constant data                      */
/**********************************************************************************/
extern const MID_REG_limit_s EPC_CONF_limit_range; //used to check new limits
extern const MID_REG_periodic_s EPC_CONF_periodic_time_min; //used to check new limits and init APP_IFACE_periodic

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
	APP_IFACE_periodic.usrHeartBeatPeriod = EPC_CONF_periodic_time_min.usrHeartBeatPeriod;
	APP_IFACE_periodic.electricMsgPeriod  = EPC_CONF_periodic_time_min.electricMsgPeriod;
	APP_IFACE_periodic.tempMsgPeriod      = EPC_CONF_periodic_time_min.tempMsgPeriod;
	APP_IFACE_periodic.usrHeartBeatStatus	= MID_REG_DISABLED;
	APP_IFACE_periodic.electricMsgStatus	= MID_REG_DISABLED;
	APP_IFACE_periodic.tempMsgStatus		= MID_REG_DISABLED;

	return APP_IFACE_RESULT_SUCCESS;
}
	
APP_IFACE_result_e APP_IfaceIncommingMsg(MID_REG_control_s *  const control,
	MID_REG_meas_property_s * const meas, MID_REG_error_status_s * const status,
	MID_REG_limit_s * limits, MID_REG_control_s *consign){
	APP_IFACE_result_e res = APP_IFACE_RESULT_SUCCESS;

	return res;
}

APP_IFACE_result_e APP_IfaceProcessPeriodic(MID_REG_meas_property_s * const meas,
	MID_REG_error_status_s *  const status){
	APP_IFACE_result_e res = APP_IFACE_RESULT_SUCCESS;

	return res;
}

APP_IFACE_result_e APP_IfaceNotifyModeChange (MID_REG_control_s const * const control){
	APP_IFACE_result_e res = APP_IFACE_RESULT_SUCCESS;
	res |= MID_CommSendControlMode(&control);
	return res;
}
