/*********************************************************************************
* @file           : mid_reg.c
* @brief          : Definition of global registers
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "mid_reg.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/
#define _MAX_EPC_PWR 500
#define _MIN_EPC_PWR -500
#define _TEMP_MAX 660
#define _TEMP_MIN -160
#define _MIN_PERIOD 100
/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/
const MID_REG_limit_s MID_REG_limit_range = {
    14100, 	// hsVoltMax
    5300,   // hsVoltMin
    5100,   // lsVoltMax
    400,    // lsVoltMin
    15500,  // lsCurrMax
    -15500, // lsCurrMin
    800,    // lsPwrMax
    -800,   // lsPwrMin
    700,    // tempMax
    -200    // tempMin
};

MID_REG_limit_s MID_REG_limit = {
	MID_REG_limit_range.hsVoltMax, 	// hsVoltMax
	MID_REG_limit_range.hsVoltMin,  // hsVoltMin
	MID_REG_limit_range.lsVoltMax,  // lsVoltMax
	MID_REG_limit_range.lsVoltMin,  // lsVoltMin
	MID_REG_limit_range.lsCurrMax,  // lsCurrMax
    MID_REG_limit_range.lsCurrMin,  // lsCurrMin
	_MAX_EPC_PWR,    				// lsPwrMax
	_MIN_EPC_PWR, 	 				// lsPwrMin
	_TEMP_MAX,    					// tempMax
    _TEMP_MIN    					// tempMin
};

MID_REG_control_s MID_REG_control = {
	MID_REG_DISABLED, 	// outStatus
	MID_REG_MODE_IDLE, 	// mode
	MID_REG_LIMIT_TIME, // limitType
	0,					// modeRef
	0					// limRef
};

const MID_REG_periodic_period_s MID_REG_periodic_time_min = {
		1000,	// usrHeartBeatPeriod
		1000,	// electricMsgPeriod
		1000	// tempMsgPeriod
};

MID_REG_periodic_s MID_REG_periodic = {
	{MID_REG_periodic_time_min.usrHeartBeat,	// usrHeartBeatPeriod
	MID_REG_periodic_time_min.electricMsg,		// electricMsgPeriod
	MID_REG_periodic_time_min.tempMsg},			// tempMsgPeriod
	{MID_REG_DISABLED,							// usrHeartBeatStatus
	MID_REG_DISABLED,							// electricMsgStatus
	MID_REG_DISABLED}							// tempMsgStatus
};

const MID_REG_info_s MID_REG_info = { //TODO: assign this from EPC_CONF
		0,	// id
		0,	// fwVer
		0	// hwVer
};

MID_REG_errorStatus_s MID_REG_errorStatus = {
		MID_REG_ERROR_NONE,	// hsVoltErr
		MID_REG_ERROR_NONE,	// lsVoltErr
		MID_REG_ERROR_NONE,	// lsCurrErr
		MID_REG_ERROR_NONE,	// commErr
		MID_REG_ERROR_NONE,	// tempErr
		MID_REG_ERROR_NONE,	// intErr
		0					// lastErrVal
};

MID_REG_meas_s MID_REG_meas = {
		0,	// hsVolt
		0,	// lsVolt
		0,	// lsCurr
		0,	// tempBody
		0,	// tempAnod
		0	// tempAmb
};

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
