/*********************************************************************************
* @file                 : epc_conf.c
* @brief                :  Implementation of   Electronic  Power Converter (EPC)
* Configuration (CONF) module.  It  contains the definition and configuration of
* APP_CONF, including limits, message periods, hardware version, and measurement
* properties.
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
#define _CAN_ID		0x00		// ID
#define _FW_VER		0x01		// FW VERSION
#define _S_N		0x01		// Serial Number

/*		HW CONF		*/
#define _HW_REVIEW 		MID_REG_HW_REV_A			// Review
#define _HW_VENT		MID_REG_HW_NO_VENT			//  Vent
#define _HW_CONNECTOR	MID_REG_HW_CON_18650		// Connector
#define _HW_ANODE		MID_REG_HW_TANOD_NO_ANODE	// T anode type
#define _HW_STS			MID_REG_HW_NO_STS			// T body
#define _HW_AMB			MID_REG_HW_NO_SENSOR		// T amb
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

const MID_REG_info_s EPC_CONF_info = { //TODO: assign this from EPC_CONF
		_CAN_ID,		// id
		_FW_VER,		// fwVer
		_HW_REVIEW,		// Review
		_HW_VENT,		// Vent
		_HW_CONNECTOR,	// Connector
		_HW_ANODE,		// T anode type
		_HW_STS,		// T body
		_HW_AMB,		// T amb
		0,				// reserved
		_S_N			// sn
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
    4095, 	//hsVolt
	0,	//tempBody NOT USED, digital sensor
	0,	//tempAnod NOT USED, look-up table
	0	//tempAmb  NOT USED, look-up table
};

const MID_REG_meas_property_s EPC_CONF_MEAS_factors = {
	6000,	//lsVolt max-min (Low side Voltage range 0-6V)
	33000,	//lsCurr max-min (Low side Current range +17 -16A)
	// Despite the lsCurr is a int16 and max value is 32767, 
	// internally will be done a cast to uint16 as the factor will allways be positive
	15000, 	//hsVolt max-min
	0,	//tempBody NOT USED, digital sensor
	0,	//tempAnod NOT USED, look-up table
	0	//tempAmb  NOT USED, look-up table
};

const MID_REG_meas_property_s EPC_CONF_MEAS_offset = {
	0,		//lsVolt
	-16000,		//lsCurr
	0, 		//hsVolt
	0,	//tempBody NOT USED, digital sensor
	0,	//tempAnod NOT USED, look-up table
	0	//tempAmb  NOT USED, look-up table
};

// Look up table for the NTC sensors
const int16_t EPC_CONF_temp_lut[410] = {
	 748,744,741,738,735,732,728,725,722,719,
	 716,713,710,707,704,701,698,695,692,690,
	 687,684,681,678,675,673,670,667,664,662,
	 659,656,654,651,649,646,643,641,638,636,
	 633,631,628,626,623,621,618,616,613,611,
	 609,606,604,601,599,597,594,592,590,587,
	 585,583,581,578,576,574,572,569,567,565,
	 563,561,558,556,554,552,550,548,546,543,
	 541,539,537,535,533,531,529,527,525,523,
	 521,519,516,514,512,510,508,506,504,502,
	 500,499,497,495,493,491,489,487,485,483,
	 481,479,477,475,473,471,470,468,466,464,
	 462,460,458,456,455,453,451,449,447,445,
	 443,442,440,438,436,434,432,431,429,427,
	 425,423,422,420,418,416,414,413,411,409,
	 407,406,404,402,400,399,397,395,393,391,
	 390,388,386,384,383,381,379,378,376,374,
	 372,371,369,367,365,364,362,360,358,357,
	 355,353,352,350,348,346,345,343,341,340,
	 338,336,334,333,331,329,328,326,324,323,
	 321,319,317,316,314,312,311,309,307,305,
	 304,302,300,299,297,295,294,292,290,288,
	 287,285,283,282,280,278,276,275,273,271,
	 270,268,266,264,263,261,259,258,256,254,
	 252,251,249,247,245,244,242,240,238,237,
	 235,233,231,230,228,226,224,223,221,219,
	 217,215,214,212,210,208,207,205,203,201,
	 199,197,196,194,192,190,188,187,185,183,
	 181,179,177,175,174,172,170,168,166,164,
	 162,160,158,156,155,153,151,149,147,145,
	 143,141,139,137,135,133,131,129,127,125,
	 123,121,119,117,115,113,111,109,106,104,
	 102,100,98,96,94,92,89,87,85,83,81,78,76,
	 74,72,69,67,65,62,60,58,55,53,51,48,46,43,
	 41,39,36,34,31,29,26,23,21,18,16,13,10,8,
	 5,2,-1,-3,-6,-9,-12,-15,-18,-21,-24,-27,
	 -30,-33,-36,-39,-42,-45,-48,-52,-55,-58,
	 -62,-65,-69,-72,-76,-79,-83,-87,-90,-94,
	 -98,-102,-106,-110,-114,-119,-123,-127,
	 -132,-136,-141,-146,-150,-155,-160,-165,-171
	};
