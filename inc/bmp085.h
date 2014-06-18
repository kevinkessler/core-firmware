/*
 * bmp085.h
 *
 *  Created on: Mar 20, 2014
 *      Author: Kevin
 */

#ifndef BMP085_H_
#define BMP085_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "debug.h"
#include "i2c.h"

extern CPAL_InitTypeDef I2C1_DevStructure;
extern void delay (uint32_t);

#define BMP085_FAIL 0
#define BMP085_ACTIVE 1
#define BMP085_UNINITIALIZED 2
#define OSS 2
#define BMP085_ADDRESS 0x77
#define ALT 142.0

float getBMP085Temperature(void);
float getBMP085Pressure(void);
uint32_t bmp085ReadUP(void);
int32_t bmp085GetPressure(uint32_t);
uint16_t bmp085ReadUT(void);
int16_t bmp085GetTemperature(uint16_t);
uint8_t bmp085Calibration(void);
uint16_t bmp085ReadInt(uint8_t);

#ifdef __cplusplus
}
#endif

#endif /* BMP085_H_ */
