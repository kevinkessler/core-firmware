/*
 * si7021.c
 *
 *  Created on: Jun 17, 2014
 *      Author: Kevin
 */
#include "si7021.h"

SI7021::SI7021()
{
	i2c=I2C::getInstance();

	status=SI7021_ACTIVE;
	temperature=-100.0;
	humidity=-100.0;

}

uint8_t SI7021::measure()
{
	uint8_t buffer[2];

	if(i2c->read(SI7021_ADDR,0xE5,buffer,2)==CPAL_FAIL)
	{
		status=SI7021_FAIL;
		temperature=-100.0;
		humidity=-100.0;
		return status;
	}
	else
		status=SI7021_SUCCESS;

	uint16_t rh_code=buffer[0]<<8 | buffer[1];

	humidity = (float)((125.0*rh_code)/65536.0 - 6.0);

	if(i2c->read(SI7021_ADDR,0xE3,buffer,2)==CPAL_FAIL)
	{
		status=SI7021_FAIL;
		temperature=-100.0;
		humidity=-100.0;
		return status;
	}
	else
		status=SI7021_SUCCESS;

	uint16_t temp_code=(uint16_t)buffer[0]<<8|buffer[1];

	temperature = (float)((175.72*temp_code)/65536.0 - 46.85);

	return status;


}
float SI7021::getHumidity()
{
	return humidity;
}

float SI7021::getTemperature()
{
	return temperature;
}
