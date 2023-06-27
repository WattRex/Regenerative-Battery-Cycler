/*********************************************************************************
* @file           : epc_conf.c
* @brief          : Definition of APP_CONF
**********************************************************************************/

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
#define _MSG_PERIODIC_DEFAULT		0	 // Disable
#define _USR_HEART_BEAT_PERIOD_DEF 1000  // ms
#define _ELECTRIC_MSG_PERIOD_DEF   1000  // ms
#define _TEMP_MSG_PERIOD_DEF       1000  // ms

/*		ID CONF		*/
#define _ID			0x01
#define _FW_VER		0x01
#define _HW_VER		0x01 //0x01 with i2c temp, 0x02 without i2c temp
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
		_MAX_HS_VOLT, 	// hsVoltMax
		_MIN_HS_VOLT,   // hsVoltMin
		_MAX_LS_VOLT,   // lsVoltMax
		_MIN_LS_VOLT,   // lsVoltMin
		_MAX_LS_CURR,   // lsCurrMax
        _MIN_LS_CURR,   // lsCurrMin
		_MAX_EPC_PWR,   // lsPwrMax
        _MIN_EPC_PWR,   // lsPwrMin
		_TEMP_MAX,      // tempMax
        _TEMP_MIN       // tempMin
};

const MID_REG_periodic_s EPC_CONF_periodic_time_min = {
		_MSG_PERIODIC_DEFAULT,		 // usrHeartBeat Disable
		_USR_HEART_BEAT_PERIOD_DEF,	 // usrHeartBeatPeriod
		_MSG_PERIODIC_DEFAULT,		 // electricMsgPeriod Disable
		_ELECTRIC_MSG_PERIOD_DEF,	 // electricMsgPeriod
		_MSG_PERIODIC_DEFAULT,		 // tempMsgPeriod Disable
		_TEMP_MSG_PERIOD_DEF	     // tempMsgPeriod
};


const MID_REG_info_s EPC_CONF_info = { //TODO: assign this from EPC_CONF
		_ID,		// id
		_FW_VER,	// fwVer
		_HW_VER,	// hwVer
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
	5000,	//lsVolt max-min
	33000,	//lsCurr max-min
	// Despite the lsCurr is a int16 and max value is 32767, 
	// internally will be done a cast to uint16 as the factor will allways be positive
	15000, 	// hsVolt max-min
	900,	//tempBody max-min
	900,	//tempAnod max-min
	900		//tempAmb max-min
};

const MID_REG_meas_property_s EPC_CONF_MEAS_offset = {
	0,	//lsVolt
	-16500,	//lsCurr
	0, 	// hsVolt
	-200,	//tempBody
	-200,	//tempAnod
	-200	//tempAmb
};
