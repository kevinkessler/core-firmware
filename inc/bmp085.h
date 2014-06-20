/*
 * bmp085.h
 *
 *  Created on: Mar 20, 2014
 *      Author: Kevin
 */

#ifndef BMP085_H_
#define BMP085_H_


#include "debug.h"
#include "i2c.h"
#include <math.h>

extern void delay (uint32_t);

#define BMP085_FAIL 0
#define BMP085_ACTIVE 1
#define BMP085_SUCCESS 1
#define BMP085_UNINITIALIZED 2
#define OSS 2
#define BMP085_ADDRESS 0x77
#define ALT 142.0

class BMP085
{
private:
	uint8_t status;

	// Calibration values
	int16_t ac1;
	int16_t ac2;
	int16_t ac3;
	uint16_t ac4;
	uint16_t ac5;
	uint16_t ac6;
	int16_t b1;
	int16_t b2;
	int16_t mb;
	int16_t mc;
	int16_t md;

	// b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
	// so ...Temperature(...) must be called before ...Pressure(...).
	int32_t b5;
	float temperature;
	float pressure;

	uint8_t calibration(void);
	uint16_t readInt(uint8_t);
	int16_t readTemperature(void);
	int32_t readPressure(void);

public:
	BMP085(void);
	float getTemperature(void);
	float getPressure(void);
	uint8_t measure(void);

};



#endif /* BMP085_H_ */
