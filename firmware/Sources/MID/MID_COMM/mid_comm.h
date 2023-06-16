/*********************************************************************************
* @file           : mid_comm.h
* @brief          : MID header file for communication module
***********************************************************************************/
#ifndef MID_COMM_H_
#define MID_COMM_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "hal_can.h"
#include "mid_reg.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include "stdint.h"

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
	MID_COMM_RESULT_SUCCESS = 0x00U,	/**< MID_COMM success operation result **/
	MID_COMM_RESULT_ERROR   = 0x01U,	/**< MID_COMM error operation result **/
	MID_COMM_RESULT_BUSY	= 0x02U,	/**< MID_COMM busy operation result **/
	MID_COMM_RESULT_TIMEOUT	= 0x03U,	/**< MID_COMM timeout operation result **/
}MID_COMM_result_e;

/**
 * @enum MID_COMM_request_e
 * @brief Structure with the available timers.
 */
typedef enum
{
	MID_COMM_REQUEST_INFO 						= 0x00U,	/**< MID_COMM Request for info register **/
	MID_COMM_REQUEST_CONTROL 				= 0x01U,	/**< MID_COMM Request for control register **/
	MID_COMM_REQUEST_STATUS  				= 0x02U,	/**< MID_COMM Request for error status register **/
	MID_COMM_REQUEST_ELECT_MEAS  		= 0x03U,	/**< MID_COMM Request for electrical measures **/
	MID_COMM_REQUEST_TEMP_MEAS 			= 0x04U,	/**< MID_COMM Request for temperature measures **/
	MID_COMM_REQUEST_HEARTBEAT  			= 0x05U,	/**< MID_COMM Request received with heartbeat **/
	MID_COMM_REQUEST_LIMITS_LS_VOLT 	= 0x06U,	/**< MID_COMM Request for LS voltage limits **/
	MID_COMM_REQUEST_LIMITS_LS_CURR 	= 0x07U,	/**< MID_COMM Request for LS current limits **/
	MID_COMM_REQUEST_LIMITS_HS_VOLT	= 0x08U,	/**< MID_COMM Request for HS voltage limits **/
	MID_COMM_REQUEST_LIMITS_PWR 			= 0x09U,	/**< MID_COMM Request for power limits **/
	MID_COMM_REQUEST_LIMITS_TEMP			= 0x0AU,	/**< MID_COMM Request for power limits **/
	MID_COMM_REQUEST_COUNT
}MID_COMM_request_e;

/**
 * @enum HAL_CAN_result_e
 * @brief Structure for the result of the CAN operation.
 */
typedef enum
{
	MID_COMM_MSG_ID_MODE						= 0x00U,			/**< **/
	MID_COMM_MSG_ID_REQ						= 0x01U,			/**< **/
	MID_COMM_MSG_ID_LS_VOLT_LIMIT	= 0x02U,			/**< **/
	MID_COMM_MSG_ID_LS_CURR_LIMIT	= 0x03U,			/**< **/
	MID_COMM_MSG_ID_HS_VOLT_LIMIT	= 0x04U,			/**< **/
	MID_COMM_MSG_ID_PWR_LIMIT			= 0x05U,			/**< **/
	MID_COMM_MSG_ID_TEMP_LIMIT			= 0x06U,			/**< **/
	MID_COMM_MSG_ID_PERIODIC				= 0x07U,			/**< **/
	MID_COMM_MSG_ID_INFO 					= 0x0AU,			/**< **/
	MID_COMM_MSG_ID_STATUS					= 0x0BU,			/**< **/
	MID_COMM_MSG_ID_ELECT_MEAS			= 0x0CU,			/**< **/
	MID_COMM_MSG_ID_TEMP_MEAS			= 0x0DU,			/**< **/
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

void MID_CommCallbackControlMode(MID_REG_control_s * const data);

void MID_CommCallbackConfigPeriodicConfig(MID_REG_periodic_s * data);

void MID_CommCallbackRequest(const MID_COMM_request_e req);

void MID_CommCallbackLimit(const MID_COMM_msg_id_e lim_type, const uint16_t valueMin, const uint16_t valueMax);

MID_COMM_result_e MID_CommInit(void);

MID_COMM_result_e MID_CommProcessIncommingData(void);

MID_COMM_result_e MID_CommSendReqLimits (const MID_COMM_request_e req, MID_REG_limit_s * const limits);

MID_COMM_result_e MID_CommSendInfo(void);

MID_COMM_result_e MID_CommSendElectMeas (MID_REG_meas_property_s * const meas);

MID_COMM_result_e MID_CommSendTempMeas (MID_REG_meas_property_s * const meas);

MID_COMM_result_e MID_CommSendStatus ( MID_REG_errorStatus_s * const status);

MID_COMM_result_e MID_CommSendControlMode (MID_REG_control_s * const status);

#endif /* MID_COMM_H_ */ 
