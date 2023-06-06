/*********************************************************************************
* @file           : mid_reg.h
* @brief          : Definition of global registers
***********************************************************************************/

#ifndef MID_MID_REG_MID_REG_H_
#define MID_MID_REG_MID_REG_H_
/**********************************************************************************/
/*                               Project Includes                                 */
/**********************************************************************************/

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
 * @enum MID_REG_status_e
 * @brief Possible values for the output status.
 */
typedef enum
{
	MID_REG_DISABLED = 0x0U,
	MID_REG_ENABLED
}MID_REG_status_e;


/**
 * @enum MID_REG_mode_e
 * @brief Status machine values definition.
 */
typedef enum
{
	MID_REG_MODE_IDLE = 0x0U,
	MID_REG_MODE_WAIT,
	MID_REG_MODE_CV,
	MID_REG_MODE_CC,
	MID_REG_MODE_CP,
	MID_REG_MODE_ERROR
}MID_REG_mode_e;


/**
 * @enum MID_REG_limit_type_e
 * @brief Status machine values definition.
 */
typedef enum
{
	MID_REG_LIMIT_TIME = 0x0U,
	MID_REG_LIMIT_VOLT,
	MID_REG_LIMIT_CURR,
	MID_REG_LIMIT_PWR
}MID_REG_limit_type_e;


/**
 * @enum MID_REG_error_e
 * @brief Error values definition.
 */
typedef enum
{
	MID_REG_ERROR_NONE = 0x0U,
	MID_REG_ERROR_RAISED
}MID_REG_error_e;


/**
 * @struct MID_REG_limit_s
 * @brief Structure for the operation limits registers.
 */
typedef struct
{
	uint16_t hsVoltMax;
	uint16_t hsVoltMin;
	uint16_t lsVoltMax;
	uint16_t lsVoltMin;
	int16_t lsCurrMax;
	int16_t lsCurrMin;
	int16_t lsPwrMax;
	int16_t lsPwrMin;
	int16_t tempMax;
	int16_t tempMin;
}MID_REG_limit_s;


/**
 * @struct MID_REG_control_s
 * @brief Structure for the control the value of output, ref and mode.
 */
typedef struct
{
	MID_REG_status_e outStatus : 1;
	MID_REG_mode_e mode            : 3;
	MID_REG_limit_type_e limitType : 2;
	int16_t modeRef;
	int32_t limRef;
}MID_REG_control_s;


/**
 * @struct MID_REG_periodic_period_s
 * @brief Structure for the time of periodic msgs.
 */
typedef struct
{
	uint16_t usrHeartBeat;
	uint16_t electricMsg;
	uint16_t tempMsg;
}MID_REG_periodic_period_s;


/**
 * @struct MID_REG_periodic_status_s
 * @brief Structure for the periodic msgs status.
 */
typedef struct
{
	MID_REG_status_e usrHeartBeat;
	MID_REG_status_e electricMsg;
	MID_REG_status_e tempMsg;
}MID_REG_periodic_status_s;


/**
 * @struct MID_REG_periodic_s
 * @brief Structure for the periodic msgs conf.
 */
typedef struct
{
	MID_REG_periodic_period_s period;
	MID_REG_periodic_status_s status;
}MID_REG_periodic_s;


/**
 * @struct MID_REG_info_s
 * @brief Structure for the equip ID and fw, sw versions.
 */
typedef struct
{
	uint16_t id : 6;
	uint16_t fwVer : 5;
	uint16_t hwVer : 5;
}MID_REG_info_s;


/**
 * @struct MID_REG_errorStatus_s
 * @brief Structure to track different errors.
 */
typedef struct
{
	MID_REG_error_e hsVoltErr;
	MID_REG_error_e lsVoltErr;
	MID_REG_error_e lsCurrErr;
	MID_REG_error_e commErr;
	MID_REG_error_e tempErr;
	MID_REG_error_e intErr;
	uint16_t lastErrVal;
}MID_REG_errorStatus_s;


/**
 * @struct MID_REG_meas_s
 * @brief Structure to track measures.
 */
typedef struct
{
	uint16_t hsVolt;
	uint16_t lsVolt;
	int16_t lsCurr;
	int16_t tempBody;
	int16_t tempAnod;
	int16_t tempAmb;
}MID_REG_meas_s;

/**********************************************************************************/
/*                        Definition of exported variables                        */
/**********************************************************************************/
extern const MID_REG_limit_s MID_REG_limit_range;
extern  MID_REG_limit_s MID_REG_limit;
extern MID_REG_control_s MID_REG_control;

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


#endif /* MID_MID_REG_MID_REG_H_ */
