/*********************************************************************************
* @file           : epc_conf.h
* @brief          : Project configuration variables
**********************************************************************************/

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
extern const uint16_t EPC_CONF_PWR_kp[3];
extern const uint16_t EPC_CONF_PWR_ki[3];
extern const uint16_t EPC_CONF_PWR_kd[3];

/**********************************************************************************/
/*                        				HAL 									  */
/**********************************************************************************/
/**< Run Test instead of machine status **/
#define EPC_CONF_TESTING

/**< Decomment to enable each HAL module **/
#define EPC_CONF_USE_CUSTOM_HAL

/**< CAN sender standard identifier **/
#define EPC_CONF_CAN_ID 0x109

#define EPC_CONF_PWM_ENABLED
#define EPC_CONF_GPIO_ENABLED
#define EPC_CONF_ADC_DMA_ENABLED
//#define EPC_CONF_STS_ENABLED
#define EPC_CONF_TMR_ENABLED
//#define EPC_CONF_WDG_ENABLED
#define EPC_CONF_CAN_ENABLED
#define EPC_CONF_DABS_TEST
#define EPC_CONF_PWR_TEST
//#define EPC_CONF_DABS_TEST
//#define EPC_CONF_PWR_TEST
#define EPC_CONF_COMM_TEST

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
