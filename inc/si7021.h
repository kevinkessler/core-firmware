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

class SI7021{

public:
	SI7021(void);
	float getHumidity(void);
	float getTemperature(void);

};



#endif /* SI7021_H_ */
