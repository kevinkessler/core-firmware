/*
 * max44009.h
 *
 *  Created on: Mar 24, 2014
 *      Author: Kevin
 */

#ifndef MAX44009_H_
#define MAX44009_H_


#include <math.h>
#include "debug.h"
#include "i2c.h"

#define MAX44009_FAIL 0
#define MAX44009_ACTIVE 1
#define MAX44009_SUCCESS 1

class MAX44009
{
private:
	float lux;
	uint8_t status;

public:
	MAX44009();
	uint8_t measure();
	float getLux();
};

#endif /* MAX44009_H_ */
