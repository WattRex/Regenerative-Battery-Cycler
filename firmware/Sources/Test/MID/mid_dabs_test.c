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
	int16_t temp;
	uint8_t i=0;
	do{
		res = MID_DabsReadTemperature(&temp);
		HAL_Delay(1000);
		i++;
	}while (i<5 && res != MID_DABS_RESULT_ERROR);
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
			lscurr = 1;
			break;
		case 3: //CV DISCHARGING
			states = 5;
			lscurr = -1;
			break;
		case 4: //CC CHARGING
			states = 5;
			lscurr = 1;
			break;
		case 5:// CC DISCHARGING
			states = 5;
			lscurr = -1;
			break;
		case 6: // CP CHARGING
			states = 5;
			lscurr = 1;
			break;
		case 7://CP DISCHARGING
			states = 5;
			lscurr = -1;
			break;
		case 8:// ERROR HSVOLT
			errors = {1,0,0,0,0,0,0};
			break;
		case 9:// ERROR LSVOLT
			errors = {0,1,0,0,0,0,0};
			break;
		case 10:// ERROR LSCURR
			errors = {0,0,1,0,0,0,0};
			break;
		case 11:// ERROR COMM
			errors = {0,0,0,1,0,0,0};
			break;
		case 12:// ERROR TEMP
			errors = {0,0,0,0,1,0,0};
			break;
		case 13:// ERROR INT
			errors = {0,0,0,0,0,1,0};
			break;
	}
	do{
		res = MID_DabsUpdateLeds(state, 0, errors);
		i++;
	}while (i<states && res==MID_DABS_RESULT_SUCCESS);
	return res;
}
