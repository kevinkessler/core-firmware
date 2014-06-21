/*
 * max44009.c
 *
 *  Created on: Mar 24, 2014
 *      Author: Kevin
 */

#include "max44009.h"

MAX44009::MAX44009()
{
	i2c=I2C::getInstance();

	status=MAX44009_ACTIVE;
	lux=0.0;
}

float MAX44009::getLux()
{
	return lux;
}

uint8_t MAX44009::measure()
{
	uint8_t buffer;

	if(status == MAX44009_FAIL)
		i2c->reset();

	if(i2c->read(0x4B,0x03,&buffer,1) == CPAL_FAIL)
	{
		status=MAX44009_FAIL;
		return 0.0;
	}
	else
		status=MAX44009_ACTIVE;

	uint8_t luxHigh=buffer;


	if(i2c->read(0x4B,0x04,&buffer,1) == CPAL_FAIL)
	{
		status=MAX44009_FAIL;
		return 0.0;
	}
	else
		status=MAX44009_ACTIVE;

	uint8_t luxLow=buffer;

	uint8_t exponent=(luxHigh&0xf0)>>4;
	uint8_t mant=(luxHigh&0x0f)<<4|luxLow;

	lux = (float)(pow(2,exponent)*mant)*0.045;

	return status;

}
