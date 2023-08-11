/*********************************************************************************
* @file              : mid_reg.h
* @brief             : Header file for Middleware (MID) Registers (REG) module.
* Defines global registers and structures for the control and monitoring of the
* system. It includes typedefs for status, mode, error, hardware  versions, and
* calibrations fot the measurement perfierals.
***********************************************************************************/

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

#ifndef MID_REG_H_
#define MID_REG_H_
/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include <stdint.h>

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
 * @enum MID_REG_status_e
 * @brief Possible values for the output status.
 */
typedef enum
{
	MID_REG_DISABLED = 0x0U,
	MID_REG_ENABLED
}MID_REG_status_e;


/**
 * @enum MID_REG_mode_e
 * @brief Status machine values definition.
 */
typedef enum
{
	MID_REG_MODE_WAIT = 0x0U,
	MID_REG_MODE_CV,
	MID_REG_MODE_CC,
	MID_REG_MODE_CP,
	MID_REG_MODE_IDLE,
	MID_REG_MODE_ERROR
}MID_REG_mode_e;


/**
 * @enum MID_REG_limit_type_e
 * @brief Status machine values definition.
 */
typedef enum
{
	MID_REG_LIMIT_TIME = 0x0U,
	MID_REG_LIMIT_VOLT,
	MID_REG_LIMIT_CURR,
	MID_REG_LIMIT_PWR
}MID_REG_limit_type_e;


/**
 * @enum MID_REG_error_e
 * @brief Error values definition.
 */
typedef enum
{
	MID_REG_ERROR_NONE = 0x0U,
	MID_REG_ERROR_RAISED
}MID_REG_error_e;

/**
 * @enum MID_REG_hw_rev_e
 * @brief Hardware versions review.
 */
typedef enum
{
	MID_REG_HW_REV_A = 0X0U,
	MID_REG_HW_REV_B,
	MID_REG_HW_REV_C
}MID_REG_hw_rev_e;

/**
 * @enum MID_REG_hw_vent_e
 * @brief Hardware vent types.
 */
typedef enum
{
	MID_REG_HW_NO_VENT = 0X0U,
	MID_REG_HW_VENT
}MID_REG_hw_vent_e;

/**
 * @enum MID_REG_hw_connector_e
 * @brief Hardware connector type.
 */
typedef enum
{
	MID_REG_HW_CON_18650 = 0X0U,
	MID_REG_HW_CON_BANANA
}MID_REG_hw_connector_e;

/**
 * @enum MID_REG_hw_tanod_type_e
 * @brief Hardware type of Temp anode.
 */
typedef enum
{
	MID_REG_HW_TANOD_NO_ANODE = 0X0U,
	MID_REG_HW_TANOD_RING_NTC,
	MID_REG_HW_TANOD_PLASTIC_NTC
}MID_REG_hw_tanod_type_e;

/**
 * @enum MID_REG_hw_temp_body_e
 * @brief Hardware temp body type.
 */
typedef enum
{
	MID_REG_HW_NO_STS = 0X0U,
	MID_REG_HW_STS_SENS
}MID_REG_hw_temp_body_e;

/**
 * @enum MID_REG_hw_temp_e
 * @brief Hardware temp type.
 */
typedef enum
{
	MID_REG_HW_NO_SENSOR = 0X0U,
	MID_REG_HW_PLASTIC_NTC
}MID_REG_hw_temp_e;

/**
 * @struct MID_REG_limit_s
 * @brief Structure for the operation limits registers.
 */
typedef struct
{
	uint16_t lsVoltMax;
	uint16_t lsVoltMin;
	int16_t lsCurrMax;
	int16_t lsCurrMin;
	uint16_t hsVoltMax;
	uint16_t hsVoltMin;
	int16_t lsPwrMax;
	int16_t lsPwrMin;
	int16_t tempMax;
	int16_t tempMin;
}MID_REG_limit_s;


/**
 * @struct MID_REG_control_s
 * @brief Structure for the control the value of output, ref and mode.
 */
typedef struct __attribute__((__packed__))
{
	MID_REG_status_e outStatus : 1;
	MID_REG_mode_e mode            : 3;
	MID_REG_limit_type_e limitType : 4;
	int16_t modeRef;
	int32_t limRef;
}MID_REG_control_s;


/**
 * @struct MID_REG_periodic_s
 * @brief Structure for the periodic msgs.
 */
typedef struct __attribute__((__packed__))
{
	MID_REG_status_e usrHeartBeatStatus : 1;
	uint16_t usrHeartBeatPeriod : 15;
	MID_REG_status_e electricMsgStatus : 1;
	uint16_t electricMsgPeriod : 15;
	MID_REG_status_e tempMsgStatus : 1;
	uint16_t tempMsgPeriod : 15;
}MID_REG_periodic_s;

/**
 * @struct MID_REG_info_s
 * @brief Structure for the equip ID and fw, hw versions.
 */
typedef struct __attribute__((__packed__))
{
		uint32_t id : 6;
		uint32_t fwVer : 5;
		MID_REG_hw_rev_e hwRev: 3;
		MID_REG_hw_vent_e vent : 1;
		MID_REG_hw_connector_e connector : 3;
		MID_REG_hw_tanod_type_e tAnodType: 2;
		MID_REG_hw_temp_body_e tBody: 1;
		MID_REG_hw_temp_e tAmb: 1;
		uint32_t reserved: 2;
		uint32_t sn : 8;
}MID_REG_info_s;

/**
 * @struct MID_REG_error_status_s
 * @brief Structure to track different errors.
 */
typedef struct
{
	MID_REG_error_e hsVoltErr : 1;
	MID_REG_error_e lsVoltErr : 1;
	MID_REG_error_e lsCurrErr : 1;
	MID_REG_error_e commErr : 1;
	MID_REG_error_e tempErr : 1;
	MID_REG_error_e intErr : 1;
	uint16_t lastErrVal;
}MID_REG_error_status_s;


/**
 * @struct MID_REG_meas_s
 * @brief Structure to track measures.
 */
typedef struct
{
	uint16_t lsVolt;
	int16_t lsCurr;
	uint16_t hsVolt;
	int16_t tempBody;
	int16_t tempAnod;
	int16_t tempAmb;
}MID_REG_meas_property_s;

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


#endif /* MID_REG_H_ */
