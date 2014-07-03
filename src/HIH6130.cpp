/*
 * HIH6130.cpp
 *
 *  Created on: Jul 1, 2014
 *      Author: Kevin
 */

#include "HIH6130.h"

HIH6130::HIH6130()
{
	i2c=I2C::getInstance();

	status=HIH6130_ACTIVE;
	temperature=-100.0;
	humidity=-100.0;
}

float HIH6130::getTemperature()
{
	return temperature;
}

float HIH6130::getHumidity()
{
	return humidity;
}

uint8_t HIH6130::measure()
{
	uint8_t buffer[4];

	buffer[0]=0x00;
	if(i2c->write(HIH6130_ADDR,buffer,0)==CPAL_FAIL)
	{
		status=HIH6130_FAIL;
		temperature=-100.0;
		humidity=-100.0;
		return status;
	}

	for (int n=0;n<10;n++)
	{
		if(i2c->read(HIH6130_ADDR,buffer,4)==CPAL_FAIL)
		{
			status=HIH6130_FAIL;
			temperature=-100.0;
			humidity=-100.0;
			return status;
		}
		else
			status=HIH6130_SUCCESS;


		if(!(buffer[0] & 0xC0))
			break;


		delay(10);
	}

	uint16_t hum=((buffer[0] & 0x3F)<<8)+buffer[1];
	uint16_t temp=((buffer[2]<<8|buffer[3])>>2);

	humidity = (float) hum * 6.10e-3;
	temperature = (float) temp*1.007e-2 -40.0;

	return status;
}
