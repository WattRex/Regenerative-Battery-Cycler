/*********************************************************************************
* @file           : hal_sys.h
* @brief          : HAL header file for SYS
**********************************************************************************
* @attention
* Research Laboratory in Fluid Dynamics and Combustion Technologies (LIFTEC)
*   Spanish National Research Council (CSIC)
*   c/ María de Luna 10, 50018 Zaragoza, Spain
*
*   All rights reserved. Distribution or duplication without previous
*   written agreement of the owner prohibited.
***********************************************************************************/

#ifndef HAL_SYS_H_
#define HAL_SYS_H_

/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/
#include "epc_conf.h"
#include "main.h"

#ifdef EPC_CONF_PWM_ENABLED
#include "hal_pwm.h"
#endif
#ifdef EPC_CONF_GPIO_ENABLED
   #include "hal_gpio.h"
#endif
#ifdef EPC_CONF_ADC_DMA_ENABLED
   #include "hal_adc.h"
   #include "hal_dma.h"
#endif
#ifdef EPC_CONF_I2C_ENABLED
   #include "hal_i2c.h"
#endif
#ifdef EPC_CONF_TMR_ENABLED
   #include "hal_tmr.h"
#endif
#ifdef EPC_CONF_WDG_ENABLED
   #include "hal_wdg.h"
#endif
#ifdef EPC_CONF_CAN_ENABLED
   #include "hal_can.h"
#endif


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

/**
 * @enum HAL_SYS_mode_t
 * @brief Structure for the defined micro power modes.
 */
typedef enum
{
	HAL_SYS_MODE_NORMAL = 0x0U,	/**< HAL_SYS_MODE_NORMAL Normal power mode **/
	HAL_SYS_MODE_SLEEP,			/**< HAL_SYS_MODE_SLEEP Sleep power mode **/
	HAL_SYS_MODE_COUNT			/**< HAL_SYS_MODE_COUNT */
}HAL_SYS_mode_t;


/**
 * @enum HAL_SYS_result_t
 * @brief Structure of available response values for HAL_SYS operations.
 */
typedef enum
{
	HAL_SYS_RESULT_SUCCESS = 0x0U, 	/**< HAL_SYS success operation result **/
	HAL_SYS_RESULT_ERROR_GPIO = 0x01U,	/**< HAL_SYS error on GPIO operation **/
	HAL_SYS_RESULT_ERROR_ADC  = 0x02U,	/**< HAL_SYS error on ADC operation  **/
	HAL_SYS_RESULT_ERROR_I2C  = 0x03U,	/**< HAL_SYS error on I2C operation  **/
	HAL_SYS_RESULT_ERROR_COMM = 0x04U,	/**< HAL_SYS error on communication process, CAN or UART **/
	HAL_SYS_RESULT_ERROR_CRIT = 0x05U,	/**< HAL_SYS critical error result **/
}HAL_SYS_result_t;


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
 * @fn HAL_SYS_result_t HAL_SysInit(void)
 * @brief Reset all peripherals, configures CPU, AHB and APB buses clocks to 8MHz
 * and invokes the corresponding initialization functions of the used peripherals.
 * If any initialization fails, a recovery process is initiated.
 * @return 	@ref HAL_SYS_RESULT_SUCCESS, if the initialization was successful and
 * @ref HAL_SYS_RESULT_ERROR, @ref HAL_SYS_RESULT_BUSY or @ref HAL_SYS_RESULT_TIMEOUT
 * if initialization and recovery of any peripheral failed.
 */
HAL_SYS_result_t HAL_SysInit(void);

/**
 * @fn HAL_SYS_result_t HAL_SysPwrMode(HAL_SYS_mode_t)
 * @brief The micro enters on power save mode.
 *
 * @param mode Power mode used
 * @return @ref HAL_SYS_RESULT_SUCCESS if power mode changed correctly and
 * @ref HAL_SYS_RESULT_ERROR otherwise.
 */
HAL_SYS_result_t HAL_SysPwrMode(HAL_SYS_mode_t mode);

/**
 * @fn HAL_SYS_result_t HAL_SysReset(void)
 * @brief Performs an hard or soft reset on the micro and peripherals.
 *
 * @return @ref HAL_SYS_RESULT_ERROR if action cannot be applied.
 */
HAL_SYS_result_t HAL_SysReset (void);

#endif /* HAL_SYS_H_ */
 
