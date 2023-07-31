/*********************************************************************************
* @file           : epc_conf.c
* @brief          : Definition of APP_CONF
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

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "mid_reg.h"
/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "epc_conf.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/

/*		LIMITS RANGE		*/
#define _MAX_HS_VOLT      14100  // V
#define _MIN_HS_VOLT       5300  // V
#define _MAX_LS_VOLT       5100  // V
#define _MIN_LS_VOLT        400  // V
#define _MAX_LS_CURR      15500  // A 
#define _MIN_LS_CURR     -15500  // A 
#define _MAX_EPC_PWR        800  // dW
#define _MIN_EPC_PWR       -800  // dW
#define _TEMP_MAX           700  // dºC
#define _TEMP_MIN          -200  // dºC
#define _MIN_PERIOD         100  // ms

/*		MSGS CONF		*/
#define _MSG_PERIODIC_DEFAULT		0		// Disable
#define _USR_HEART_BEAT_PERIOD_MIN 10  		// ms
#define _ELECTRIC_MSG_PERIOD_MIN   10  		// ms
#define _TEMP_MSG_PERIOD_MIN       10  		// ms

/*		ID CONF		*/
#define _CAN_ID		0x03
#define _FW_VER		0x01
#define _S_N		0x01


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

const MID_REG_limit_s EPC_CONF_limit_range = {
		_MAX_LS_VOLT,   // lsVoltMax
		_MIN_LS_VOLT,   // lsVoltMin
		_MAX_LS_CURR,   // lsCurrMax
        _MIN_LS_CURR,   // lsCurrMin
		_MAX_HS_VOLT, 	// hsVoltMax
		_MIN_HS_VOLT,   // hsVoltMin
		_MAX_EPC_PWR,   // lsPwrMax
        _MIN_EPC_PWR,   // lsPwrMin
		_TEMP_MAX,      // tempMax
        _TEMP_MIN       // tempMin
};

const MID_REG_periodic_s EPC_CONF_periodic_time_min = {
		_MSG_PERIODIC_DEFAULT,		 // usrHeartBeat Disable
		_USR_HEART_BEAT_PERIOD_MIN,	 // usrHeartBeatPeriod
		_MSG_PERIODIC_DEFAULT,		 // electricMsgPeriod Disable
		_ELECTRIC_MSG_PERIOD_MIN,	 // electricMsgPeriod
		_MSG_PERIODIC_DEFAULT,		 // tempMsgPeriod Disable
		_TEMP_MSG_PERIOD_MIN	     // tempMsgPeriod
};

const MID_REG_hw_version_s EPC_CONF_hw_version = { //TODO: assign this from EPC_CONF
		MID_REG_HW_REV_A,					// Review
		MID_REG_HW_NO_VENT,					//  Vent
		MID_REG_HW_CON_18650,				// Connector
		MID_REG_HW_TANOD_RING_NTC,		// T anode type
		MID_REG_HW_STS_SENS,				// T body
		MID_REG_HW_PLASTIC_NTC				// T amb
};

const MID_REG_info_s EPC_CONF_info = { //TODO: assign this from EPC_CONF
		_CAN_ID,		// id
		_FW_VER,	// fwVer
		EPC_CONF_hw_version,	// hwVer
		_S_N		// sn
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

/** Tuple of factor and offset */

const MID_REG_meas_property_s EPC_CONF_MEAS_max_value = {
    4095,	//lsVolt
    4095,	//lsCurr
	4095, 	// hsVolt
    4095,	//tempBody
    4095,	//tempAnod
    4095	//tempAmb
};

const MID_REG_meas_property_s EPC_CONF_MEAS_factors = {
	6000,	//lsVolt max-min (Low side Voltage range 0-6V)
	32500,	//lsCurr max-min (Low side Current range +16.5 -16A)
	// Despite the lsCurr is a int16 and max value is 32767, 
	// internally will be done a cast to uint16 as the factor will allways be positive
	15000, 	// hsVolt max-min
	900,	//tempBody max-min (Range -20ºC to +70ºC)
	-900,	//tempAnod max-min (Range -20ºC to +70ºC)
	-900		//tempAmb max-min  (Range -20ºC to +70ºC)
};

const MID_REG_meas_property_s EPC_CONF_MEAS_offset = {
	0,		//lsVolt
	-16000,	//lsCurr -16500
	0, 		// hsVolt
	-200,	//tempBody
	700,	//tempAnod
	700	//tempAmb
};
