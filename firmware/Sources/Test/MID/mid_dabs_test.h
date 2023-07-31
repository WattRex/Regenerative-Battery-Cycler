/*********************************************************************************
* @file           : mid_dabs_test.h
* @brief          : HAL header file for MID DABS TEST
***********************************************************************************/

/*********************************************************************************
*	
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
*@author           : WattRex <https://github.com/WattRex/>
*@date			   : 2023-07-04
*@version		   : v1.0.0
***********************************************************************************/

#ifndef MID_DABS_TEST_H_
#define MID_DABS_TEST_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "mid_dabs.h"
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
/*            Definition of exported types (typedef, enum, struct, union)         */
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


MID_DABS_result_e MID_DabsTestMeas(void);


/**
 * @fn MID_DABS_result_t MID_DabsTestLeds()
 * @brief Try the different states of the leds depending on the mode or error encounter.
 *
 * @return
 * 		@ref MID_DABS_RESULT_SUCCESS if test ends correctly,
 * 		@ref MID_DABS_RESULT_ERROR otherwise
 */
MID_DABS_result_e MID_DabsTestLeds(uint8_t state);
#endif /* MID_DABS_TEST_H_ */
 
