/*
 * mpl3115.c
 *
 *  Created on: Jun 5, 2014
 *      Author: Kevin
 */
#include "mpl3115.h"

float mpl3115Pressure;
float mpl3115Temperature;

uint8_t mpl3115Init()
{
	uint8_t buffer;

	buffer=0x38;
	if(i2cWrite(MPL3115_ADDR,CTRL_REG1,&buffer,1)==CPAL_FAIL)
		return MPL3115_FAIL;

	buffer=0x07;
	if(i2cWrite(MPL3115_ADDR,PT_DATA_CFG,&buffer,1)==CPAL_FAIL)
		return MPL3115_FAIL;

	buffer=0x39;
	if(i2cWrite(MPL3115_ADDR,CTRL_REG1,&buffer,1)==CPAL_FAIL)
		return MPL3115_FAIL;

	toggleOST();

	return MPL3115_SUCCESS;
}

uint8_t mpl3115Measure()
{

	uint8_t status=0x00;
	uint8_t count;
	for (count=0;count<200;count++)
	{

		i2cRead(MPL3115_ADDR,DR_STATUS,&status,1);
		if(status & 0x06)  //TDR and PDR set
			break;

		delay(10);
	}

	if(count==200)
		return MPL3115_FAIL;

	uint8_t pressBytes[3];
	if(i2cRead(MPL3115_ADDR,OUT_P_MSB,pressBytes,3)==CPAL_FAIL)
		return MPL3115_FAIL;

	uint8_t temp[2];
	if(i2cRead(MPL3115_ADDR,OUT_T_MSB,temp,2)==CPAL_FAIL)
		return MPL3115_FAIL;


	mpl3115Temperature=(float)(temp[0])+(temp[1]>>4)/16.0;

	uint32_t press_int=pressBytes[0]<<16 | pressBytes[1]<<8 | pressBytes[0];
	press_int>>=6;

	mpl3115Pressure=(float)press_int+(float)((pressBytes[0]&0x30)>>4)/4.0;

	toggleOST();

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

void toggleOST()
{
	uint8_t status;

	i2cRead(MPL3115_ADDR,CTRL_REG1,&status,1);
	status &= ~(1<<1);
	i2cWrite(MPL3115_ADDR,CTRL_REG1,&status,1);

	status |= (1<<1);
	i2cWrite(MPL3115_ADDR,CTRL_REG1,&status,1);
}
