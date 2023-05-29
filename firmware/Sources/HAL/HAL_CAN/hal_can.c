/*********************************************************************************
* @file           : hal_can.c
* @brief          : Implementation of HAL CAN
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
#include "stm32f3xx_hal.h"

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_can.h"
#include "can.h"
/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of local types (typedef, enum, struct, union)            */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local variables                          */
/**********************************************************************************/

/** Transmit and receive headers **/
CAN_TxHeaderTypeDef   TxHeader;
CAN_RxHeaderTypeDef   RxHeader;
/** Pointer to Mailbox used to store the Tx message **/
uint32_t              TxMailbox;

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/

/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported functions    					  */
/**********************************************************************************/

/**
 * @fn HAL_CAN_result_e HAL_CanInit()
 * @brief Initialize CAN in master mode and 125kbit/s of bit rate is used. CAN enters
 * into Bus-Off state after 255 failed transmissions and automatic recovery from it. It
 * not auto wakeup when micro wakeup from sleep mode. Transmission order is based on
 * identifiers priority (first msg with lowest identifier).
 */
HAL_CAN_result_e HAL_CanInit (){
    HAL_CAN_result_e res = HAL_CAN_RESULT_SUCCESS;
    MX_CAN_Init();
    return res;
}

HAL_CAN_result_e HAL_CanTransmit (uint32_t id, uint8_t* data, uint8_t size)
{
	/* Start the Transmission process */
	HAL_CAN_result_e res = HAL_CAN_RESULT_ERROR;
	if (size <= 8){
		TxHeader.DLC=size;
		TxHeader.StdId = id;
		res = HAL_CAN_AddTxMessage(&hcan, &TxHeader, data, &TxMailbox);
	}
	return res;
}


HAL_CAN_result_e HAL_CanReceive (uint32_t* id, uint8_t* data, uint8_t* size)
{
	/* Get RX message */
	HAL_CAN_result_e res = HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &RxHeader, data);
	id = &RxHeader.StdId;
	size = &RxHeader.DLC;
	return res;
}
