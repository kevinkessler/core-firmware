/*
 * si7021.c
 *
 *  Created on: Jun 17, 2014
 *      Author: Kevin
 */
#include "si7021.h"

SI7021::SI7021()
{

}
float SI7021::getHumidity()
{
	uint8_t buffer[2];

	if(i2cRead(SI7021_ADDR,0xE5,buffer,2)==CPAL_FAIL)
		return -100.0;

	uint16_t rh_code=buffer[0]<<8 | buffer[1];

	return (float)((125.0*rh_code)/65536.0 - 6.0);
}

float SI7021::getTemperature()
{
	uint8_t buffer[2];

	if(i2cRead(SI7021_ADDR,0xE3,buffer,2)==CPAL_FAIL)
		return -100.0;

	uint16_t temp_code=(uint16_t)buffer[0]<<8|buffer[1];

	return (float)((175.72*temp_code)/65536.0 - 46.85);

}
