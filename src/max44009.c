/*
 * max44009.c
 *
 *  Created on: Mar 24, 2014
 *      Author: Kevin
 */

#include "max44009.h"

uint8_t MAXBuffer[1]={0};
uint8_t MAXStatus=MAX44009_ACTIVE;


float max44009GetLux()
{
	if(MAXStatus == MAX44009_FAIL)
		i2cReset();

	MAXBuffer[0]=0x03;
	if(i2cWrite(0x4B,0,MAXBuffer,1) == CPAL_FAIL)
	{
		MAXStatus=MAX44009_FAIL;
		return 0.0;
	}
	else
		MAXStatus=MAX44009_ACTIVE;

	if(i2cRead(0x4B,0,MAXBuffer,1) == CPAL_FAIL)
	{
		MAXStatus=MAX44009_FAIL;
		return 0.0;
	}
	else
		MAXStatus=MAX44009_ACTIVE;

	uint8_t luxHigh=MAXBuffer[0];

	MAXBuffer[0]=0x04;
	if(i2cWrite(0x4B,0, MAXBuffer,1) == CPAL_FAIL)
	{
		MAXStatus=MAX44009_FAIL;
		return 0.0;
	}
	else
		MAXStatus=MAX44009_ACTIVE;

	if(i2cRead(0x4B,0,MAXBuffer,1) == CPAL_FAIL)
	{
		MAXStatus=MAX44009_FAIL;
		return 0.0;
	}
	else
		MAXStatus=MAX44009_ACTIVE;

	uint8_t luxLow=MAXBuffer[0];

	uint8_t exponent=(luxHigh&0xf0)>>4;
	uint8_t mant=(luxHigh&0x0f)<<4|luxLow;

	return (float)(pow(2,exponent)*mant)*0.045;

}
