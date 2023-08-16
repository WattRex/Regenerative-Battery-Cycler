/*********************************************************************************
* @file                   : epc_conf.h
* @brief                  : Header  file for   Electronic  Power Converter (EPC)
* Configuration  (CONF)  module. It contains the definition and configuration of
* APP_CONF, including limits, message periods, hardware version, and measurement
* properties.
**********************************************************************************/

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

#ifndef EPC_CONF_H_
#define EPC_CONF_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "stdint.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include "mid_reg.h"
/**********************************************************************************/
/*                     Definition of exported symbolic constants                     */
/**********************************************************************************/
/*		DEFAULT LIMITS AT INIT		*/
#define EPC_CONF_MAX_EPC_PWR_DEF    500  // dW
#define EPC_CONF_MIN_EPC_PWR_DEF   -500  // dW
#define EPC_CONF_TEMP_MAX_DEF       660  // dºC
#define EPC_CONF_TEMP_MIN_DEF      -160  // dºC


#define EPC_CONF_FP_N_FRAC_BITS 	16	 // Number of bits for decimals

#define EPC_CONF_CTRL_TRANS_TIME     100   	//ms to consider the control stable
#define EPC_CONF_PWR_KP_I            567        // 0.008658
#define EPC_CONF_PWR_KI_I            655360 	// 10
#define EPC_CONF_PWR_KP_V            115 		// 0.00175
#define EPC_CONF_PWR_KI_V            4920 		// 0.075073
#define EPC_CONF_PWR_KP_P            2			// 0.000030
#define EPC_CONF_PWR_KI_P            70			// 0.001068
/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*                         Definition of local functions                          */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported symbolic constants               */
/**********************************************************************************/
extern const MID_REG_periodic_s EPC_CONF_periodic_time_min;
extern const MID_REG_limit_s EPC_CONF_limit_range;
extern const MID_REG_info_s EPC_CONF_info;

/**********************************************************************************/
/*                        				MIDDLEWARE								  */
/**********************************************************************************/
extern const MID_REG_meas_property_s EPC_CONF_MEAS_max_value;
extern const MID_REG_meas_property_s EPC_CONF_MEAS_factors;
extern const MID_REG_meas_property_s EPC_CONF_MEAS_offset;
extern const int16_t EPC_CONF_temp_lut[410];

/**********************************************************************************/
/*                        				HAL 									  */
/**********************************************************************************/
/**< Run Test instead of machine status **/
//#define EPC_CONF_TESTING
#ifdef EPC_CONF_TESTING
	#define EPC_CONF_DABS_TEST
	#define EPC_CONF_PWR_TEST
	#define EPC_CONF_COMM_TEST
#endif

/**< Decomment to enable each HAL module **/
#define EPC_CONF_USE_CUSTOM_HAL

#define EPC_CONF_PWM_ENABLED
#define EPC_CONF_GPIO_ENABLED
#define EPC_CONF_ADC_DMA_ENABLED
#define EPC_CONF_STS_ENABLED
#define EPC_CONF_TMR_ENABLED
#define EPC_CONF_WDG_ENABLED
#define EPC_CONF_CAN_ENABLED


/**< Timeout for initialization and blocking mode transfers for I2C peripheral**/
#define EPC_CONF_I2C_TIMEOUT 5

/**< Timeout until ADC conversion is finished **/
#define EPC_CONF_ADC_TIMEOUT 1

/**********************************************************************************/
/*                       Definition of local constant data                        */
/**********************************************************************************/

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/

/**********************************************************************************/
/*                      Definition of exported constant data                      */
/**********************************************************************************/


#endif /* EPC_CONF_H_ */
