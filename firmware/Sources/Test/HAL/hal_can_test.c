/*********************************************************************************
* @file           : hal_can.c
* @brief          : Implementation of HAL CAN
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

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_can_test.h"

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

HAL_CAN_result_e HAL_CanTest(void)
{
	/* Start the Transmission process */

	uint8_t data= 1, i= 1, size;
	uint8_t dataR[8]={0,0,0,0,0,0,0,0};
	uint32_t id;
	HAL_CAN_result_e res;
	res = HAL_CanAddFilters(0x130, 0x7F0);
	res = HAL_CanTransmit(0x102, &data, 1);
	if (res == HAL_CAN_RESULT_SUCCESS){
		while (i<5){
			res = HAL_CanReceive(&id, dataR, &size);
			if (res == HAL_CAN_RESULT_SUCCESS) break;
			HAL_Delay(1000);
			i++;
		}
		if (res == HAL_CAN_RESULT_SUCCESS){
			dataR[7]++;
			res = HAL_CanTransmit(0x102, dataR, 8);
		}
	}
	return res;
}
