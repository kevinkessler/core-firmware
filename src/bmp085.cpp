/*
 * bmp085.c
 *
 *  Created on: Mar 20, 2014
 *      Author: Kevin
 */

#include "bmp085.h"

BMP085::BMP085()
{
	i2c=I2C::getInstance();
	calibration();
}

uint8_t BMP085::calibration()
{
      status=BMP085_UNINITIALIZED;

	  ac1 = readInt(0xAA);
	  ac2 = readInt(0xAC);
	  ac3 = readInt(0xAE);
	  ac4 = readInt(0xB0);
	  ac5 = readInt(0xB2);
	  ac6 = readInt(0xB4);
	  b1 = readInt(0xB6);
	  b2 = readInt(0xB8);
	  mb = readInt(0xBA);
	  mc = readInt(0xBC);
	  md = readInt(0xBE);

	  if(status==BMP085_UNINITIALIZED)
		  status = BMP085_ACTIVE;

	  return status;
}


uint16_t BMP085::readInt(uint8_t addr)
{
	uint8_t buffer[2];

	if(i2c->read(BMP085_ADDRESS, addr, buffer, 2)==CPAL_FAIL)
	{
		status=BMP085_FAIL;
		return 0;
	}

	return buffer[0]<<8|buffer[1];


}


int16_t BMP085::readTemperature()
{
	int32_t x1, x2;
	uint8_t buffer[2];

	buffer[0]=0x2E;

	if(i2c->write(BMP085_ADDRESS, 0xF4, buffer, 1)==CPAL_FAIL)
	{
		status=BMP085_FAIL;
		return -100;
	}

	delay(5);

	uint16_t ut=readInt(0xF6);
	if(status==BMP085_FAIL)
	{
		return -100;
	}


	x1 = (((int32_t)ut - (int32_t)ac6)*(int32_t)ac5) >> 15;
	x2 = ((int32_t)mc << 11)/(x1 + md);
	b5 = x1 + x2;

	return ((b5 + 8)>>4);
}

int32_t BMP085::readPressure()
{

	int32_t x1, x2, x3, b3, b6, p;
	uint32_t b4, b7, up;
	uint8_t buffer[3];

	buffer[0]=0x34 + (OSS<<6);
	if(i2c->write(BMP085_ADDRESS, 0xF4, buffer, 1)==CPAL_FAIL)
	{
		status=BMP085_FAIL;
		return -100;
	}

	delay(2 + (3 << OSS));

	if(i2c->read(BMP085_ADDRESS, 0xF6, buffer, 3)==CPAL_FAIL)
	{
		status=BMP085_FAIL;
		return -100;
	}

	up= (((uint32_t)buffer[0]<<16)|((uint32_t)buffer[1] << 8) | ((uint32_t)buffer[2])) >> (8-OSS);

	b6 = b5 - 4000;
	// Calculate B3
	x1 = (b2 * (b6 * b6)>>12)>>11;
	x2 = (ac2 * b6)>>11;
	x3 = x1 + x2;
	b3 = (((((int32_t)ac1)*4 + x3)<<OSS) + 2)>>2;

	// Calculate B4
	x1 = (ac3 * b6)>>13;
	x2 = (b1 * ((b6 * b6)>>12))>>16;
	x3 = ((x1 + x2) + 2)>>2;
	b4 = (ac4 * (uint32_t)(x3 + 32768))>>15;

	b7 = ((uint32_t)(up - b3) * (50000>>OSS));
	if (b7 < 0x80000000)
	p = (b7<<1)/b4;
	else
	p = (b7/b4)<<1;

	x1 = (p>>8) * (p>>8);
	x1 = (x1 * 3038)>>16;
	x2 = (-7357 * p)>>16;
	p += (x1 + x2 + 3791)>>4;

	return p;
}

uint8_t BMP085::measure()
{
	if (status == BMP085_FAIL)
	{
		i2c->reset();
		if(calibration() == BMP085_FAIL)
			return BMP085_FAIL;
	}

	int16_t t=readTemperature();
	if(status==BMP085_FAIL)
	{
		temperature = -100.0;
		pressure = -100.0;
		return status;
	}

	temperature= t * 0.10;

	int32_t p=readPressure();
	if(status==BMP085_FAIL)
	{
		temperature = -100.0;
		pressure = -100.0;
		return status;
	}

	pressure= ((float)p/pow(1-(ALT/44330.0),5.255))/100.0;

	return status;

}

float BMP085::getTemperature()
{
	return temperature;
}

float BMP085::getPressure()
{
	return pressure;
}
