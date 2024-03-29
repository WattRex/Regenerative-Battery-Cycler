/*********************************************************************************
* @file             : hal_can.h
* @brief            : Header file for Hardware Abstraction Layer (HAL) of the CAN
* (Controller   Area  Network).    Provides    functions  for    initializing CAN
* communication, adding and deleting filters for message acceptance, transmitting
* data, and receiving data through CAN.
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

#ifndef HAL_CAN_H_
#define HAL_CAN_H_
/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include <stdint.h>
#include "can.h"

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
 * @enum HAL_CAN_result_e
 * @brief Structure for the result of the CAN operation.
 */
typedef enum
{
	HAL_CAN_RESULT_SUCCESS 		= 0x00U,	/**< HAL_CAN success operation result **/
	HAL_CAN_RESULT_ERROR 		= 0x01U,	/**< HAL_CAN error operation result **/
	HAL_CAN_RESULT_BUSY 		= 0x02U,	/**< HAL_CAN busy result **/
	HAL_CAN_RESULT_NO_MESSAGE 	= 0x03U,
	HAL_CAN_RESULT_TIMEOUT  	= 0x04		/**< HAL_CAN timeout expired **/
}HAL_CAN_result_e;

/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/

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
 * @fn HAL_CAN_result_e HAL_CanInit(HAL_CAN_port_t)
 * @brief Configures the CAN peripheral with the options provided by the
 * manufacturer provided functions.
 *
 * @param port Selected CAN interface
 * @return HAL_CAN_RESULT_SUCCESS if interface was initialized correctly,
 * HAL_CAN_RESULT_BUSY if the peripheral is not ready,
 * HAL_CAN_result_eIMEOUT if the CAN_TIMEOUT timeout has expired and
 * HAL_CAN_RESULT_ERROR otherwise
 */
HAL_CAN_result_e HAL_CanInit();


/**
 * @fn HAL_CAN_result_e HAL_CanAddFilters(const uint16_t id, const uint16_t mask)
 * @brief Configure the CAN filter with the options provided by the
 * manufacturer provided functions. This will have a id and a mask aplied to the id.
 * The receive message id must match the values where the mask is 0, with the id imposed.
 * Every time the function is called will set a filter in a bank up to 14
 *
 * @param id ID reference that will have the messages in order to receive them
 * @param mask With a negative logic, the bits set to a 1 will have to match the id.
 * @return HAL_CAN_RESULT_SUCCESS if interface was initialized correctly,
 * HAL_CAN_RESULT_BUSY if the peripheral is not ready,
 * HAL_CAN_result_eIMEOUT if the CAN_TIMEOUT timeout has expired and
 * HAL_CAN_RESULT_ERROR otherwise
 */
HAL_CAN_result_e HAL_CanAddFilters(const uint16_t id, const uint16_t mask);

/**
 * @fn HAL_CAN_result_e HAL_CanDelFilters(void)
 * @brief Configure the CAN filter to receive all messages deleting all filters
 *
 * @return HAL_CAN_RESULT_SUCCESS if interface was initialized correctly,
 * HAL_CAN_RESULT_BUSY if the peripheral is not ready,
 * HAL_CAN_result_eIMEOUT if the CAN_TIMEOUT timeout has expired and
 * HAL_CAN_RESULT_ERROR otherwise
 */
HAL_CAN_result_e HAL_CanDelFilters(void);

/**
 * @fn HAL_CAN_result_e HAL_CanTransmit(const uint32_t id, const uint8_t* data, const uint8_t size)
 * @brief Send data through CAN interface using the id provided
 * as standard id.
 * @param id Identifier of the message
 * @param data Data to be send.
 * @param size Size of send data. size must be <= 8b
 * @return HAL_CAN_RESULT_SUCCESS if data was sent correctly,
 * HAL_CAN_RESULT_BUSY if the peripheral is not ready,
 * HAL_CAN_result_eIMEOUT if the CAN_TIMEOUT timeout has expired and
 * HAL_CAN_RESULT_ERROR otherwise.
 */
HAL_CAN_result_e HAL_CanTransmit (const uint32_t id, const uint8_t* data, const uint8_t size);
/**
 * @fn HAL_CAN_result_e HAL_CanReceive(uint32_t* id, uint8_t* data, uint8_t* size)
 * @brief Checks if there are any messages pending on reception FIFO.
 * If so, it saves it in data.
 * @param id Pointer to the identifier of the message
 * @param data Pointer to the received data.
 * @param size Number of received data.
 * @return HAL_CAN_RESULT_SUCCESS if data was received correctly,
 * HAL_CAN_RESULT_BUSY if the peripheral is not ready,
 * HAL_CAN_result_eIMEOUT if the CAN_TIMEOUT timeout has expired and
 * HAL_CAN_RESULT_ERROR if FIFOs are empty or another error has happened.
 */
HAL_CAN_result_e HAL_CanReceive (uint32_t* id, uint8_t* data, uint8_t* size);

#endif /* HAL_CAN_H_ */
