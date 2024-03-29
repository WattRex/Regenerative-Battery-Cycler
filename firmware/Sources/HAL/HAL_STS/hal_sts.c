/*********************************************************************************
* @file           : hal_sts.c
* @brief          : Implementation of Hardware Abstraction Layer (HAL) of the STS
* (Temperature Sensor).  Provides functions    for  initializing  the temperature
* sensor    and  reading the   temperature   data   from  the  sensor   using I2C
* communication.  The sensor is   configured  to measure temperature  with  a low
* repeatability of deci degrees Celsius.
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

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/
#include "epc_st_err.h" //Import EPC_ST_ERR_COUNTER

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_sts.h"
#include "i2c.h"

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
uint16_t devAddres = 0x4A; // Two options: 0x4A or 0x4B
uint16_t sts_conversion[2] = {1750, 450};
/**********************************************************************************/
/*                        Definition of imported variables                        */
/**********************************************************************************/
extern uint8_t EPC_ST_ERR_COUNTER;

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/

/**********************************************************************************/
/*                    Declaration of local function prototypes                    */
/**********************************************************************************/
/**
 * @fn HAL_STS_result_t _I2cTransfer()
 * @brief Transfer the data
 * @return
 * 		@ref HAL_STS_RESULT_SUCCESS if initialized correctly,
 * 		@ref HAL_STS_RESULT_ERROR otherwise
 */
static HAL_STS_result_e _I2cTransmit(const uint16_t devAddr, const uint8_t *comand);

/**
 * @fn HAL_STS_result_t _I2cTransfer()
 * @brief Transfer the data
 * @return
 * 		@ref HAL_STS_RESULT_SUCCESS if initialized correctly,
 * 		@ref HAL_STS_RESULT_ERROR otherwise
 */
static HAL_STS_result_e _I2cReceive(const uint16_t devAddr, uint16_t *data);
/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/
static HAL_STS_result_e _I2cTransmit(const uint16_t devAddr, const uint8_t *command)
{
	uint16_t header = devAddr << 1 | 1;
	// Warning suppression: the command variable is an input and should be constant.
	HAL_STS_result_e res = HAL_I2C_Master_Transmit(&hi2c1, header, command, 2, EPC_CONF_I2C_TIMEOUT);
	return res;
}

static HAL_STS_result_e _I2cReceive(const uint16_t devAddr, uint16_t *dataO)
{
	uint16_t header = devAddr << 1 | 1;
	uint8_t data[4];
	HAL_STS_result_e res = HAL_I2C_Master_Receive(&hi2c1, header, data, 3, EPC_CONF_I2C_TIMEOUT);
	*dataO = data[0] << 8 | data[1];
	return res;
}
/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/

HAL_STS_result_e HAL_StsInit(void)
{
	HAL_STS_result_e res = HAL_STS_RESULT_ERROR;
	EPC_ST_ERR_COUNTER = 0;
	MX_I2C1_Init();
	if (EPC_ST_ERR_COUNTER)
	{
		res = HAL_STS_RESULT_ERROR;
	}
	else
	{
		// Start periodical measurement Low repeatability 10mps
		/* Other possible modes are LowRep 4mps 0x23 0x29 // LowRep 2mps 0x22 0x2B */
		uint8_t command[] = {0x27, 0x2a};
		res = _I2cTransmit(devAddres, command);
	}
	return res;
}

HAL_STS_result_e HAL_StsReadTemperature(int16_t *temp)
{

	HAL_STS_result_e res = HAL_STS_RESULT_ERROR;
	uint8_t command[] = {0xE0, 0x00};
	res = _I2cTransmit(devAddres, command);
	if (res == HAL_STS_RESULT_SUCCESS)
	{
		uint16_t tempRaw;
		res = _I2cReceive(devAddres, &tempRaw);
		*temp = (int16_t)(((uint32_t)(sts_conversion[0] * tempRaw)) >> 16) - sts_conversion[1];
	}
	return res;
}
