/*
 * mpl3115.h
 *
 *  Created on: Jun 5, 2014
 *      Author: Kevin
 */

#ifndef MPL3115_H_
#define MPL3115_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "i2c.h"

#define MPL3115_ADDR 0x60
#define CTRL_REG1 0x26
#define PT_DATA_CFG 0x13
#define DR_STATUS 0x06
#define OUT_P_MSB 0x01
#define OUT_T_MSB 0x04

#define MPL3115_FAIL 0
#define MPL3115_SUCCESS 1

uint8_t mpl3115Measure(void);
float mpl3115GetPressure(void);
float mpl3115GetTemperature(void);

#ifdef __cplusplus
}
#endif

#endif /* MPL3115_H_ */
