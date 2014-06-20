/*
 * si7021.h
 *
 *  Created on: Jun 17, 2014
 *      Author: Kevin
 */

#ifndef SI7021_H_
#define SI7021_H_


#include "i2c.h"

#define SI7021_ADDR 0x40
#define SI7021_FAIL 0
#define SI7021_ACTIVE 1
#define	SI7021_SUCCESS 1

class SI7021{
private:
	float humidity;
	float temperature;
	uint8_t status;

public:
	SI7021(void);
	uint8_t measure();
	float getHumidity(void);
	float getTemperature(void);

};



#endif /* SI7021_H_ */
