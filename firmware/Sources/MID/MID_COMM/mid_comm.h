/*********************************************************************************
* @file           : mid_comm.h
* @brief          : Header file for Middleware (MID) Communication (COMM) module.
* It handles  communication through CAN bus and defines functions for sending and
* receiving messages, managing control   modes, periodic  configurations, request
* limits, and various measurements defined in the comm protocol.
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
* @date			   : 2023-08-24
* @version		   : v1.0.1
***********************************************************************************/

#ifndef MID_COMM_H_
#define MID_COMM_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "mid_reg.h"

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
 * @enum MID_COMM_result_e
 * @brief Structure for the result of the communication operation.
 */
typedef enum
{
	MID_COMM_RESULT_SUCCESS 			= 0x00U,	/**< MID_COMM success operation result **/
	MID_COMM_RESULT_ERROR   			= 0x01U,	/**< MID_COMM error operation result **/
	MID_COMM_RESULT_BUSY				= 0x02U,	/**< MID_COMM busy operation result **/
	MID_COMM_RESULT_NO_MESSAGES			= 0x03U,	/**< MID_COMM no messages to read from can **/
	MID_COMM_RESULT_TIMEOUT				= 0x04U,	/**< MID_COMM timeout operation result **/
	MID_COMM_RESULT_FORMAT_ERROR		= 0x05U,	/**< MID_COMM error format message **/
}MID_COMM_result_e;

/**
 * @enum MID_COMM_request_e
 * @brief Structure with the available timers.
 */
typedef enum
{
	MID_COMM_REQUEST_INFO 				= 0x00U,	/**< MID_COMM Request for info register **/
	MID_COMM_REQUEST_CONTROL 			= 0x01U,	/**< MID_COMM Request for control register **/
	MID_COMM_REQUEST_STATUS  			= 0x02U,	/**< MID_COMM Request for error status register **/
	MID_COMM_REQUEST_ELECT_MEAS  		= 0x03U,	/**< MID_COMM Request for electrical measures **/
	MID_COMM_REQUEST_TEMP_MEAS 			= 0x04U,	/**< MID_COMM Request for temperature measures **/
	MID_COMM_REQUEST_HEARTBEAT  		= 0x05U,	/**< MID_COMM Request received with heartbeat **/
	MID_COMM_REQUEST_LIMITS_LS_VOLT 	= 0x06U,	/**< MID_COMM Request for LS voltage limits **/
	MID_COMM_REQUEST_LIMITS_LS_CURR 	= 0x07U,	/**< MID_COMM Request for LS current limits **/
	MID_COMM_REQUEST_LIMITS_HS_VOLT		= 0x08U,	/**< MID_COMM Request for HS voltage limits **/
	MID_COMM_REQUEST_LIMITS_PWR 		= 0x09U,	/**< MID_COMM Request for power limits **/
	MID_COMM_REQUEST_LIMITS_TEMP		= 0x0AU,	/**< MID_COMM Request for power limits **/
	MID_COMM_REQUEST_COUNT
}MID_COMM_request_e;

/**
 * @enum MID_COMM_result_e
 * @brief Structure for the result of the CAN operation.
 * TODO: @roberto eliminar el MID_COMM_REQUEST y cambiar por este
 */
typedef enum
{

	MID_COMM_MSG_ID_MODE				= 0x00U,			/**< MID_COMM Message ID to send control mode register **/
	MID_COMM_MSG_ID_REQ					= 0x01U,			/**< MID_COMM Message ID to send info register **/
	MID_COMM_MSG_ID_LS_VOLT_LIMIT		= 0x02U,			/**< MID_COMM Message ID to send actual LS VOLT limits **/
	MID_COMM_MSG_ID_LS_CURR_LIMIT		= 0x03U,			/**< MID_COMM Message ID to send actual LS CURR limits **/
	MID_COMM_MSG_ID_HS_VOLT_LIMIT		= 0x04U,			/**< MID_COMM Message ID to send actual HS VOLT limits **/
	MID_COMM_MSG_ID_PWR_LIMIT			= 0x05U,			/**< MID_COMM Message ID to send actual LS PWR limits **/
	MID_COMM_MSG_ID_TEMP_LIMIT			= 0x06U,			/**< MID_COMM Message ID to send actual TEMP limits **/
	MID_COMM_MSG_ID_PERIODIC			= 0x07U,			/**< MID_COMM Message ID to send info register **/
	MID_COMM_MSG_ID_INFO 				= 0x0AU,			/**< MID_COMM Message ID to send info register **/
	MID_COMM_MSG_ID_STATUS				= 0x0BU,			/**< MID_COMM Message ID to send error status register **/
	MID_COMM_MSG_ID_ELECT_MEAS			= 0x0CU,			/**< MID_COMM Message ID to send electrical measurements register **/
	MID_COMM_MSG_ID_TEMP_MEAS			= 0x0DU,			/**< MID_COMM Message ID to send temperatures measurements register **/

} MID_COMM_msg_id_e;


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
/**
 * @fn void MID_CommCallbackControlMode(MID_REG_control_s * const data)
 * @brief Abstract function to be defined by user, it will manage the data received
 *
 * @param data Pointer to the data received
 */
void MID_CommCallbackControlMode(MID_REG_control_s const * const data);

/**
 * @fn void MID_CommCallbackConfigPeriodicConfig(MID_REG_periodic_s * data)
* @brief Abstract function to be defined by user, it will manage the periodic data
 *
 * @param data Pointer to the data received
 */
void MID_CommCallbackConfigPeriodicConfig(MID_REG_periodic_s const * const data);

/**
 * @fn void MID_CommCallbackRequest(const MID_COMM_request_e req)
* @brief Abstract function to be defined by user
 * Actions depending on request will be defined by user.
 *
 * @param req Type of request that has been done
 */
void MID_CommCallbackRequest(const MID_COMM_request_e req);

/**
 * @fn void MID_CommCallbackLimit(const MID_COMM_msg_id_e lim_type, const uint16_t valueMin, const uint16_t valueMax)
* @brief Abstract function to be defined by user, it will manage the data received to set new limits
 *
 * @param lim_type Type of limit to be modify
 * @param valueMin new minimum value
 * @param valueMax new maximum value
 */
void MID_CommCallbackLimit(const MID_COMM_msg_id_e lim_type, const uint16_t valueMin, const uint16_t valueMax);

/**
 * @fn MID_COMM_result_e MID_CommInit(void)
 * @brief Configure the filters for CAN

 * @return MID_COMM_RESULT_SUCCESS if filters were configured correctly,
 * MID_COMM_RESULT_ERROR otherwise
 */
MID_COMM_result_e MID_CommInit(void);

/**
 * @fn MID_COMM_result_e MID_CommProcessIncommingData(void);
 * @brief Read the incoming messages and process it until no messages are left,
 * depending on the message will do a callback to the specific function if all parameters are correct
 *
 * @return MID_COMM_RESULT_SUCCESS if message was ok and actions were done correctly,
 * MID_COMM_RESULT_BUSY if the peripheral is not ready,
 * MID_COMM_RESULT_TIMEOUT if the CAN_TIMEOUT timeout has expired and
 * MID_COMM_RESULT_NO_MESSAGES if the CAN hasn´t received any messages
 * MID_COMM_RESULT_ERROR otherwise
 */
MID_COMM_result_e MID_CommProcessIncommingData(void);

/**
 * @fn MID_COMM_result_e MID_CommSendReqLimits (const MID_COMM_request_e req, MID_REG_limit_s * const limits)
 * @brief Send the specific limit requested from the limit register given.
 *
 * @param req Limit requested to send
 * @param limits Pointer to the struct where are the limits that are wanted to be send. 
 * @return MID_COMM_RESULT_SUCCESS if message was send correctly,
 * MID_COMM_RESULT_BUSY if the peripheral is not ready or send register full,
 * MID_COMM_RESULT_TIMEOUT if the CAN_TIMEOUT timeout has expired and
 * MID_COMM_RESULT_ERROR otherwise
 */
MID_COMM_result_e MID_CommSendReqLimits (const MID_COMM_request_e req, MID_REG_limit_s const * const limits);

/**
 * @fn MID_COMM_result_e MID_CommSendInfo(void)
 * @brief Send the information about the device.
 * The id, the fw and hw version and the serial number
 *
 * @return MID_COMM_RESULT_SUCCESS if message was send correctly,
 * MID_COMM_RESULT_BUSY if the peripheral is not ready or send register full,
 * MID_COMM_RESULT_TIMEOUT if the CAN_TIMEOUT timeout has expired and
 * MID_COMM_RESULT_ERROR otherwise
 */
MID_COMM_result_e MID_CommSendInfo(void);

/**
 * @fn MID_COMM_result_e MID_CommSendElectMeas (MID_REG_meas_property_s * const meas)
 * @brief Send the electric measurements from sensors in the following order:
 * HS_VOLT, LS_VOLT, LS_CURR
 *
 * @param meas Pointer to the measure register
 * @return MID_COMM_RESULT_SUCCESS if message was send correctly,
 * MID_COMM_RESULT_BUSY if the peripheral is not ready or send register full,
 * MID_COMM_RESULT_TIMEOUT if the CAN_TIMEOUT timeout has expired and
 * MID_COMM_RESULT_ERROR otherwise
 */
MID_COMM_result_e MID_CommSendElectMeas (MID_REG_meas_property_s const * const meas);

/**
 * @fn MID_COMM_result_e MID_CommSendTempMeas (MID_REG_meas_property_s * const meas)
 * @brief Send the temperature measurements from sensors in the following order:
 * TEMP_BODY, TEMP_ANOD, TEMP_AMB
 * In case the hardware doesn`t have measurements from the Body it will return always a 0.
 *
 * @param meas Pointer to the measure register
 * @return MID_COMM_RESULT_SUCCESS if message was send correctly,
 * MID_COMM_RESULT_BUSY if the peripheral is not ready or send register full,
 * MID_COMM_RESULT_TIMEOUT if the CAN_TIMEOUT timeout has expired and
 * MID_COMM_RESULT_ERROR otherwise
 */
MID_COMM_result_e MID_CommSendTempMeas (MID_REG_meas_property_s const * const meas);

/**
 * @fn MID_COMM_result_e MID_CommSendStatus ( MID_REG_errorStatus_s * const status)
 * @brief Send the error status of the device, in the following order.
 * hs_volt_error, ls_volt_error, ls_curr_error 	0 NO ERROR 1 ERROR
 * comm_error, temp_error, internal_error		0 NO ERROR 1 ERROR
 * last_error value.
 * 
 *
 * @param status Pointer to the error registers
 * @return MID_COMM_RESULT_SUCCESS if message was send correctly,
 * MID_COMM_RESULT_BUSY if the peripheral is not ready or send register full,
 * MID_COMM_RESULT_TIMEOUT if the CAN_TIMEOUT timeout has expired and
 * MID_COMM_RESULT_ERROR otherwise
 */
MID_COMM_result_e MID_CommSendStatus ( MID_REG_error_status_s const * const status);

/**
 * @fn MID_COMM_result_e MID_CommSendControlMode (MID_REG_control_s * const status)
 * @brief Send the information about the control status,
 * The output status, the working mode, the limit type,
 * The mode reference and the limit reference.
 *
 * @param status Pointer to the control register
 * @return MID_COMM_RESULT_SUCCESS if message was send correctly,
 * MID_COMM_RESULT_BUSY if the peripheral is not ready or send register full,
 * MID_COMM_RESULT_TIMEOUT if the CAN_TIMEOUT timeout has expired and
 * MID_COMM_RESULT_ERROR otherwise
 */
MID_COMM_result_e MID_CommSendControlMode (MID_REG_control_s const * const status);

/**
 * @fn MID_COMM_result_e MID_CommSendPeriodic ( MID_REG_periodic_s * periodic)
 * @brief Sends the periodic message to verify everything is correct, 
 * providing information about the periodicity of the messages and the status 
 *
 * @param periodic Pointer to the periodic struct to be send.
 * @return MID_COMM_RESULT_SUCCESS if message was send correctly,
 * MID_COMM_RESULT_BUSY if the peripheral is not ready or send register full,
 * MID_COMM_RESULT_TIMEOUT if the CAN_TIMEOUT timeout has expired and
 * MID_COMM_RESULT_ERROR otherwise
 */
MID_COMM_result_e MID_CommSendPeriodic (MID_REG_periodic_s const * const periodic);

#endif /* MID_COMM_H_ */ 
