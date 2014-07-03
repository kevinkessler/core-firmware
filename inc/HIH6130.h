/*
 * HIH6130.h
 *
 *  Created on: Jul 1, 2014
 *      Author: Kevin
 */

#ifndef HIH6130_H_
#define HIH6130_H_

#include "debug.h"
#include "spark_wiring.h"
#include "i2c_comm.h"

#define HIH6130_ADDR 0x27
#define HIH6130_FAIL 0
#define HIH6130_ACTIVE 1
#define	HIH6130_SUCCESS 1

class HIH6130 {
private:
	float temperature;
	float humidity;
	uint8_t status;
	I2C *i2c;

public:
	HIH6130();
	uint8_t measure();
	float getHumidity(void);
	float getTemperature(void);
};

#endif /* HIH6130_H_ */
