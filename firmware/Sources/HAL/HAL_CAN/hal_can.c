/*********************************************************************************
* @file           : hal_can.c
* @brief          : Implementation of HAL CAN
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
uint8_t				  filterBank=0;

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
    CAN_FilterTypeDef  sFilterConfig;

    error_raised = 0;
    MX_CAN_Init();
    if (error_raised){
    	res = HAL_CAN_RESULT_ERROR;
    }
    else{
    	/* Initialize to receive all messages */
  		sFilterConfig.FilterBank = 0;
  		sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  		sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
  		sFilterConfig.FilterIdHigh = 0x000;	// STDID[15:8] STD[7:5] RTR IDE EXID[2:0] - STDID = 4
  		sFilterConfig.FilterIdLow = 0x000;		// STDID = 3
  		sFilterConfig.FilterMaskIdHigh=0x000;//filter mask number or identification number,according to the mode - MSBs for a 32-bit configuration
  		sFilterConfig.FilterMaskIdLow=0x000;//filter mask number or identification number,according to the mode - LSBs for a 32-bit configuration

  		sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  		sFilterConfig.FilterActivation = ENABLE;
  		sFilterConfig.SlaveStartFilterBank = 14;
    	res = HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);
  		if (res == HAL_CAN_RESULT_SUCCESS){
				/* Start the CAN peripheral */
				res = HAL_CAN_Start(&hcan);
  		}
    }
    return res;
}

HAL_CAN_result_e HAL_CanFilters(const uint16_t id, const uint16_t mask){
	if (filterBank >13){
		filterBank=0;
	}
	HAL_CAN_result_e res = HAL_CAN_Stop(&hcan);
	CAN_FilterTypeDef  sFilterConfig;
	sFilterConfig.FilterBank = filterBank;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT; // STID[10:3] STID[2:0] RTR IDE EXID[17:15]
	sFilterConfig.FilterIdHigh = id << 5; // STDID + RTR=0 IDE=0 EXID = 00
	/* In list mode the Mask also works as part of the list.
	 * In the 16bit scale you have 4 ids per filter bank
	 */
	sFilterConfig.FilterIdLow = 0x000;
	sFilterConfig.FilterMaskIdHigh= mask << 5;
	sFilterConfig.FilterMaskIdLow=0xFFFF;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;
	res = HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);
	if (res == HAL_CAN_RESULT_SUCCESS){
		res = HAL_CAN_Start(&hcan);
	}
	filterBank++;
	return res;
}


HAL_CAN_result_e HAL_CanTransmit (const uint32_t id, const uint8_t* data, const uint8_t size)
{
	/* Start the Transmission process */
	HAL_CAN_result_e res = HAL_CAN_RESULT_ERROR;
	if (size <= 8){
		TxHeader.DLC =size;
		TxHeader.StdId = id;
		res = HAL_CAN_AddTxMessage(&hcan, &TxHeader, data, &TxMailbox);
	}
	return res;
}


HAL_CAN_result_e HAL_CanReceive (uint32_t* const id, uint8_t* data, uint8_t* const size)
{
	/* Get RX message */
	HAL_CAN_result_e res = HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &RxHeader, data);
	*id = RxHeader.StdId;
	*size = RxHeader.DLC;
	return res;
}
