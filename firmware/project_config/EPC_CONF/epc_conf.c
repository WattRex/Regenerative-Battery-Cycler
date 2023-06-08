/*********************************************************************************
* @file           : epc_conf.c
* @brief          : Definition of APP_CONF
**********************************************************************************
* @attention
* Research Laboratory in Fluid Dynamics and Combustion Technologies (LIFTEC)
*   Spanish National Research Council (CSIC)
*   c/ María de Luna 10, 50018 Zaragoza, Spain
*
*   All rights reserved. Distribution or duplication without previous
*   written agreement of the owner prohibited.
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
#define _MAX_EPC_PWR_DEF    500  // dW
#define _MIN_EPC_PWR_DEF   -500  // dW
#define _TEMP_MAX           700  // dºC
#define _TEMP_MIN          -200  // dºC
#define _TEMP_MAX_DEF       660  // dºC
#define _TEMP_MIN_DEF      -160  // dºC
#define _MIN_PERIOD         100  // ms

/*		MSGS CONF		*/
#define _USR_HEART_BEAT_PERIOD_DEF 1000  // ms
#define _ELECTRIC_MSG_PERIOD_DEF   1000  // ms
#define _TEMP_MSG_PERIOD_DEF       1000  // ms

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

const MID_REG_periodic_period_s EPC_CONF_periodic_time_min = {
		_USR_HEART_BEAT_PERIOD_DEF,	 // usrHeartBeatPeriod
		_ELECTRIC_MSG_PERIOD_DEF,	 // electricMsgPeriod
		_TEMP_MSG_PERIOD_DEF	     // tempMsgPeriod
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
int32_t EPC_CONF_Ls_Curr[2]     = {0, 0};
int32_t EPC_CONF_Ls_Volt[2]     = {0, 0};
int32_t EPC_CONF_Ls_Volt_Ext[2] = {0, 0};
int32_t EPC_CONF_Hs_Volt[2]     = {0, 0};
int32_t EPC_CONF_Status_3v3[2]  = {0, 0};
int32_t EPC_CONF_Status_5v0[2]  = {0, 0};
int32_t EPC_CONF_Ext_Tmp_1[2]   = {0, 0};
int32_t EPC_CONF_Ext_Tmp_2[2]   = {0, 0};
int32_t EPC_CONF_Ext_Tmp_3[2]   = {0, 0};;
