/*********************************************************************************
* @file           : hal_wdg.c
* @brief          : Implementation of HAL WDG
***********************************************************************************/

/**********************************************************************************/
/*                  Include common and project definition header                  */
/**********************************************************************************/

/**********************************************************************************/
/*                        Include headers of the component                        */
/**********************************************************************************/
#include "hal_wdg.h"
#include "iwdg.h"

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

extern IWDG_HandleTypeDef hiwdg;

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

HAL_WDG_result_e HAL_WdgInit (void){
	HAL_WDG_result_e res = HAL_WDG_RESULT_SUCCESS;
	error_raised = 0;
	MX_IWDG_Init();
	if (error_raised){
		res = HAL_WDG_RESULT_ERROR;
	}
	return res;
}

HAL_WDG_result_e HAL_WdgRefresh(void){
	return HAL_IWDG_Refresh(&hiwdg);
}
