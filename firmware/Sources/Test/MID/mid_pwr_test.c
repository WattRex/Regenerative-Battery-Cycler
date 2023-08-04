/*********************************************************************************
* @file           : mid_pwr_test.c
* @brief          : Implementation of MID PWR TEST
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
#include "mid_pwr_test.h"
#include "mid_dabs_test.h"
#include "hal_tmr.h"
#include "hal_pwm.h"
#include "stm32f3xx_hal.h"

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
static int16_t I_ref = 1000;
static MID_REG_meas_property_s measreg = {0,0,0,0,0,0};
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
/*                         Definition of local functions                          */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported functions                        */
/**********************************************************************************/
MID_PWR_result_e MID_PwrTest(void){
	MID_PWR_result_e res = MID_PWR_RESULT_SUCCESS;
	HAL_PwmStop();
	//Set up limits HS_Volt 8V-5.3V LS_Volt 5.1V-0.4V LS_Curr +-2A
	//				Power +-510DW  Temp 660 , -160
	MID_REG_limit_s limits = {8000,5300,5100,400,2000,-2000,510,-510,660,-160};
	res = MID_PwrSetOutput(MID_PWR_Disable);
	HAL_TmrStart(HAL_TMR_CLOCK_PWR_MEAS);
	HAL_TmrStart(HAL_TMR_CLOCK_RT);
	//Delay of 5ms in order to be able to measure correctly
	HAL_Delay(5);
	res = (MID_PWR_result_e) MID_DabsUpdateMeas(MID_DABS_MEAS_ELECTRIC, &measreg);
	res |= MID_PwrCalculateD0(measreg.hsVolt,measreg.lsVolt);
	res |= MID_PwrSetOutput(MID_PWR_Enable);
	while (res == MID_PWR_RESULT_SUCCESS){
		res = (MID_PWR_result_e) MID_DabsUpdateMeas(MID_DABS_MEAS_ELECTRIC, &measreg);
		if (res == MID_PWR_RESULT_SUCCESS){
			res |= MID_PwrCalculateD0(measreg.hsVolt, measreg.lsVolt);
			if(res == MID_PWR_RESULT_SUCCESS){
				res |= MID_PwrApplyCtrl(I_ref, measreg.lsVolt, measreg.lsCurr, MID_PWR_MODE_CC, limits);
			}
		}
		HAL_Delay(1);
	}
	HAL_PwmStop();
	return res;
}
