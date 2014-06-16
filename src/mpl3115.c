/*
 * mpl3115.c
 *
 *  Created on: Jun 5, 2014
 *      Author: Kevin
 */
#include "mpl3115.h"

float mpl3115Pressure;
float mpl3115Temperature;

uint8_t mpl3115Measure()
{
/*	uint8_t regValue=0x07;	// Enable all events modes
	if(i2cWrite(MPL3115_ADDR,PT_DATA_CFG,&regValue,1)==CPAL_FAIL)
		return MPL3115_FAIL;

	regValue=0x39;			// Barometer mode, OSR=128, SBYB=1
	if(i2cWrite(MPL3115_ADDR,CTRL_REG1,&regValue,1)==CPAL_FAIL)
		return CPAL_FAIL;*/

	uint8_t buffer[2];
	buffer[0]=PT_DATA_CFG;
	buffer[1]=0x07;
	i2cWrite(MPL3115_ADDR,0,buffer,2);
	buffer[0]=CTRL_REG1;
	buffer[1]=0x39;
	i2cWrite(MPL3115_ADDR,0,buffer,2);

	uint8_t status=0x00;
	uint8_t count;
	for (count=0;count<200;count++)
	{
		buffer[0]=DR_STATUS;
		i2cWrite(MPL3115_ADDR,0,buffer,1);
		i2cRead(MPL3115_ADDR,0,&status,1);
		if(status & 0x06)  //TDR and PDR set
			break;

		delay(10);
	}

	if(count==200)
		return MPL3115_FAIL;

	uint8_t pressBytes[3];
	uint8_t p;
	buffer[0]=OUT_P_MSB;
	i2cWrite(MPL3115_ADDR,0,buffer,1);
	if(i2cRead(MPL3115_ADDR,0,&p,1)==CPAL_FAIL)
		return MPL3115_FAIL;
	pressBytes[0]=p;

	buffer[0]++;
	i2cWrite(MPL3115_ADDR,0,buffer,1);
	if(i2cRead(MPL3115_ADDR,0,&p,1)==CPAL_FAIL)
		return MPL3115_FAIL;
	pressBytes[1]=p;

	buffer[0]++;
	i2cWrite(MPL3115_ADDR,0,buffer,1);
	if(i2cRead(MPL3115_ADDR,0,&p,1)==CPAL_FAIL)
		return MPL3115_FAIL;
	pressBytes[2]=p;

	uint16_t temp;
	buffer[0]=OUT_T_MSB;
	i2cWrite(MPL3115_ADDR,0,buffer,1);
	if(i2cRead(MPL3115_ADDR,OUT_T_MSB,&p,1)==CPAL_FAIL)
		return MPL3115_FAIL;

	temp=p<<8;
	buffer[0]=OUT_T_MSB+1;
	i2cWrite(MPL3115_ADDR,0,buffer,1);
	if(i2cRead(MPL3115_ADDR,OUT_T_MSB,&p,1)==CPAL_FAIL)
		return MPL3115_FAIL;

	temp|=p;

	uint32_t press=pressBytes[0]<<16 | pressBytes[1]<<8 | pressBytes[0];
	mpl3115Pressure=press/64.0;

	mpl3115Temperature=temp/256.0;

	buffer[0]=CTRL_REG1;
	buffer[1]=0x38;
	i2cWrite(MPL3115_ADDR,0,buffer,2);

	return MPL3115_SUCCESS;
}

float mpl3115GetPressure()
{
	return mpl3115Pressure;
}

float mpl3115GetTemperature()
{
	return mpl3115Temperature;
}

