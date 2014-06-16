/*
 * i2c.h
 *
 *  Created on: Mar 24, 2014
 *      Author: Kevin
 */

#ifndef I2C_H_
#define I2C_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdlib.h>
#include "debug.h"
#include "cpal.h"
#include "cpal_i2c.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"


extern CPAL_InitTypeDef I2C1_DevStructure;
extern void delay (uint32_t);

void i2cInitialize(void);
void i2cTimerInit(void);
void i2cTimeDeInit(void);
uint8_t i2cWrite(uint8_t slave, uint8_t addr2, uint8_t *buf, uint8_t numData);
uint8_t i2cRead(uint8_t slave, uint8_t addr2, uint8_t *buf, uint8_t numData);
void i2cReset(void);

#ifdef __cplusplus
}
#endif

#endif /* I2C_H_ */
