/*********************************************************************************
* @file           : mid_dabs_test.c
* @brief          : Implementation of MID DABS TEST
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "mid_dabs_test.h"
#include "hal_tmr.h"
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
MID_DABS_result_e MID_DabsTestMeas(void){
	MID_DABS_result_e res = MID_DABS_RESULT_ERROR;
	MID_REG_meas_s measreg = {0,0,0,0,0,0};
	uint8_t i=0;
	HAL_TmrStart(HAL_TMR_CLOCK_PWR_MEAS);
	HAL_TmrStart(HAL_TMR_CLOCK_RT);
	do{
		res = MID_DabsUpdateMeas(MID_DABS_MEAS_ELECTRIC, &measreg);
		i++;
	}while (i<10 && res == MID_DABS_RESULT_SUCCESS);
	if (res == MID_DABS_RESULT_SUCCESS){
		i=0;
		do{
			res = MID_DabsUpdateMeas(MID_DABS_MEAS_TEMP, &measreg);
			i++;
		}while (i<10 && res == MID_DABS_RESULT_SUCCESS);
	}
	return res;
}

MID_DABS_result_e MID_DabsTestLeds(uint8_t state){
	MID_DABS_result_e res = MID_DABS_RESULT_ERROR;
	MID_REG_errorStatus_s errors = {0,0,0,0,0,0,0};
	uint8_t i = 0, states=1;
	int16_t lscurr=0;
	switch(state){
		case 0://IDLE
			states = 2;
			break;
		case 1: // WAIT
			states = 3;
			break;
		case 2://CV CHARGING
			states = 5;
			state = 2;
			lscurr = 1;
			break;
		case 3: //CV DISCHARGING
			states = 5;
			lscurr = -1;
			state = 2;
			break;
		case 4: //CC CHARGING
			states = 5;
			lscurr = 1;
			state = 3;
			break;
		case 5:// CC DISCHARGING
			states = 5;
			lscurr = -1;
			state = 3;
			break;
		case 6: // CP CHARGING
			states = 5;
			lscurr = 1;
			state = 4;
			break;
		case 7://CP DISCHARGING
			states = 5;
			lscurr = -1;
			state = 4;
			break;
		case 8:// ERROR HSVOLT
			errors.hsVoltErr = 1;
			break;
		case 9:// ERROR LSVOLT
			errors.lsVoltErr = 1;
			break;
		case 10:// ERROR LSCURR
			errors.lsCurrErr = 1;
			break;
		case 11:// ERROR COMM
			errors.commErr = 1;
			break;
		case 12:// ERROR TEMP
			errors.tempErr = 1;
			break;
		case 13:// ERROR INT
			errors.intErr = 1;
			break;
	}
	uint8_t rep=0;
	for (rep=0;rep<100;rep++){
		do{
			res = MID_DabsUpdateLeds(state, lscurr, &errors);
			HAL_Delay(200);
			i++;
		}while (i<states && res==MID_DABS_RESULT_SUCCESS);
	}
	return res;
}
