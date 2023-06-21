/*********************************************************************************
* @file           : mid_pwr.h
* @brief          : Middleware header file for Device ABStraction
***********************************************************************************/

#ifndef MID_PWR_H_
#define MID_PWR_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "mid_reg.h"

/**********************************************************************************/
/*                              Include other headers                             */
/**********************************************************************************/
#include <stdint.h>

/**********************************************************************************/
/*                     Definition of local symbolic constants                     */
/**********************************************************************************/

/**********************************************************************************/
/*                    Definition of local function like macros                    */
/**********************************************************************************/

/**********************************************************************************/
/*            Definition of exported types (typedef, enum, struct, union)         */
/**********************************************************************************/
/**
 * @enum MID_PWR_meas_e
 * @brief Enum of available outputs for MID_PWR.
 *
 */
typedef enum {
	MID_PWR_Disable = 0x00U,
	MID_PWR_Enable = 0x01U
}MID_PWR_Output_e;

/**
 * @enum MID_PWR_Mode_e
 * @brief Enum of available control modes for MID_PWR.
 *
 */
typedef enum{
	MID_PWR_MODE_CC = 0x0u,
	MID_PWR_MODE_CV,
	MID_PWR_MODE_CP,
	MID_PWR_COUNT
}MID_PWR_Mode_e;

/**
 * @enum MID_PWR_result_e
 * @brief Structure of available response values for MID_PWR operations.
 *
 */
typedef enum
{
  MID_PWR_RESULT_SUCCESS = 0x0U,	/**< MID_PWR_RESULT_SUCCESS success operation result */
  MID_PWR_RESULT_ERROR = 0x1U,		/**< MID_PWR_RESULT_ERROR error operation result */
  MID_PWR_RESULT_BUSY = 0x2U,		/**< MID_PWR_RESULT_ERROR busy operation result */
  MID_PWR_RESULT_TIMEOUT = 0x3U,	/**< MID_PWR_RESULT_ERROR timeout operation result */
} MID_PWR_result_e;

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
void TestFP(void); // TODO: remove it

//TODO: rewrite
/**
 * @fn MID_PWR_result_e MID_PwrSetOutput(const MID_PWR_Output_e outputMode)
 * @brief Enable or disable the output pwr.
 * @param outputMode Input variable to use to set the mode 
 * @return @ref MID_PWR_RESULT_SUCCESS if set correctly,
 * 		@ref MID_PWR_RESULT_BUSY, @ref MID_PWR_RESULT_TIMEOUT or
 * 		@ref MID_PWR_RESULT_ERROR otherwise.
 */
MID_PWR_result_e MID_PwrSetOutput(const MID_PWR_Output_e outputMode);
//TODO: rewrite
/**
 * @fn MID_PWR_result_e MID_PwrApplyPI(const uint16_t ref, const uint16_t actual_value, const MID_PWR_Mode_e, const XXXX limits)
 * @brief Enable or disable the output pwr.
 * @param outputMode Input variable to use to set the mode 
 * @return @ref MID_PWR_RESULT_SUCCESS if set correctly,
 * 		@ref MID_PWR_RESULT_BUSY, @ref MID_PWR_RESULT_TIMEOUT or
 * 		@ref MID_PWR_RESULT_ERROR otherwise.
 */
MID_PWR_result_e MID_PwrApplyCtrl(const int16_t ref, const uint16_t V_LS, const int16_t I_LS, const MID_PWR_Mode_e control_mode, const MID_REG_limit_s limits);
//TODO: rewrite
/**
 * @fn MID_PWR_result_e MID_PwrCalculateD0(const uint16_t V_HS, const uint16_t V_LS)
 * @brief Enable or disable the output pwr.
 * @param outputMode Input variable to use to set the mode 
 * @return @ref MID_PWR_RESULT_SUCCESS if set correctly,
 * 		@ref MID_PWR_RESULT_BUSY, @ref MID_PWR_RESULT_TIMEOUT or
 * 		@ref MID_PWR_RESULT_ERROR otherwise.
 */
MID_PWR_result_e MID_PwrCalculateD0(const uint16_t V_HS, const uint16_t V_LS);

#endif /* MID_PWR_H_ */
