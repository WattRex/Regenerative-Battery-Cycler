/*********************************************************************************
* @file           : hal_can.h
* @brief          : HAL header file for CAN module
**********************************************************************************
* @attention
* Research Laboratory in Fluid Dynamics and Combustion Technologies (LIFTEC)
*   Spanish National Research Council (CSIC)
*   c/ María de Luna 10, 50018 Zaragoza, Spain
*
*   All rights reserved. Distribution or duplication without previous
*   written agreement of the owner prohibited.
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
	HAL_CAN_RESULT_SUCCESS = 0x00U,	/**< HAL_CAN success operation result **/
	HAL_CAN_RESULT_ERROR = 0x01U,	/**< HAL_CAN error operation result **/
	HAL_CAN_RESULT_BUSY = 0x02U,	/**< HAL_CAN busy result **/
	HAL_CAN_RESULT_TIMEOUT  = 0x03	/**< HAL_CAN timeout expired **/
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
 * @fn HAL_CAN_result_e HAL_SpiInit(HAL_CAN_port_t)
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
 * @fn HAL_CAN_result_e HAL_CanSendMsg(uint8_t*, const uint8_t)
 * @brief Send data through CAN 1 interface using APP_CONF_CAN_ID
 * as standard id.
 * @param id Identifier of the message
 * @param data Data to be send.
 * @param size Size of send data. size must be <= 8b
 * @return HAL_CAN_RESULT_SUCCESS if data was sent correctly,
 * HAL_CAN_RESULT_BUSY if the peripheral is not ready,
 * HAL_CAN_result_eIMEOUT if the CAN_TIMEOUT timeout has expired and
 * HAL_CAN_RESULT_ERROR otherwise.
 */
HAL_CAN_result_e HAL_CanTransmit (uint32_t id, uint8_t* data, uint8_t size);
/**
 * @fn HAL_CAN_result_e HAL_CanReceiveMsg(uint8_t*, uint8_t*)
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
