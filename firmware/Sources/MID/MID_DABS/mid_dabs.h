/*********************************************************************************
* @file           : mid_dabs.h
* @brief          : Middleware header file for Device ABStraction
***********************************************************************************/

#ifndef MID_DABS_H_
#define MID_DABS_H_

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
 * @enum MID_DABS_result_e
 * @brief Structure of available response values for MID_DABS operations.
 *
 */
typedef enum
{
  MID_DABS_RESULT_SUCCESS = 0x0U,	/**< MID_DABS_RESULT_SUCCESS success operation result */
  MID_DABS_RESULT_ERROR = 0x1U,		/**< MID_DABS_RESULT_ERROR error operation result */
  MID_DABS_RESULT_BUSY = 0x2U,		/**< MID_DABS_RESULT_ERROR busy operation result */
  MID_DABS_RESULT_TIMEOUT = 0x3U,	/**< MID_DABS_RESULT_ERROR timeout operation result */
} MID_DABS_result_e;

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

/**
 * @fn MID_DABS_result_e MID_DabsGetMeas()
 * @brief Get meassurements from all the sensors
 *
 * @return @ref MID_DABS_RESULT_SUCCESS if measured correctly,
 * 		@ref MID_DABS_RESULT_BUSY, @ref MID_DABS_RESULT_TIMEOUT or
 * 		@ref MID_DABS_RESULT_ERROR otherwise.
 */
MID_DABS_result_e MID_DabsUpdateMeas(const MID_DABS_meas_e type,MID_REG_meas_s * measreg);

/**
 * @fn MID_DABS_result_e MID_DabsUpdateLeds()
 * @brief Update Leds to show the state/mode of the epc
 *
 * @return @ref MID_DABS_RESULT_SUCCESS if update successfully,
 * 		@ref MID_DABS_RESULT_BUSY, @ref MID_DABS_RESULT_TIMEOUT or
 * 		@ref MID_DABS_RESULT_ERROR otherwise.
 */
MID_DABS_result_e MID_DabsUpdateLeds(MID_REG_mode_e epcmode, int16_t lscurr, MID_REG_errorStatus_s errors);

#endif /* MID_DABS_H_ */
