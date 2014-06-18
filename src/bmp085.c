/*
 * bmp085.c
 *
 *  Created on: Mar 20, 2014
 *      Author: Kevin
 */

#include "bmp085.h"
#include <math.h>

uint8_t BMPStatus;
uint8_t BMPBuffer[3]={0,0,0};

// Calibration values
int16_t ac1;
int16_t ac2;
int16_t ac3;
uint16_t ac4;
uint16_t ac5;
uint16_t ac6;
int16_t b1;
int16_t b2;
int16_t mb;
int16_t mc;
int16_t md;

// b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
int32_t b5;


uint8_t bmp085Calibration()
{
      BMPStatus=BMP085_UNINITIALIZED;

	  ac1 = bmp085ReadInt(0xAA);
	  ac2 = bmp085ReadInt(0xAC);
	  ac3 = bmp085ReadInt(0xAE);
	  ac4 = bmp085ReadInt(0xB0);
	  ac5 = bmp085ReadInt(0xB2);
	  ac6 = bmp085ReadInt(0xB4);
	  b1 = bmp085ReadInt(0xB6);
	  b2 = bmp085ReadInt(0xB8);
	  mb = bmp085ReadInt(0xBA);
	  mc = bmp085ReadInt(0xBC);
	  md = bmp085ReadInt(0xBE);

	  if(BMPStatus==BMP085_UNINITIALIZED)
		  BMPStatus = BMP085_ACTIVE;

	  return BMPStatus;
}

uint8_t bmp085Write(uint8_t addr2, uint8_t numData)
{

	if(i2cWrite(BMP085_ADDRESS, addr2, BMPBuffer, numData)==CPAL_FAIL)
		BMPStatus=BMP085_FAIL;

	return BMPStatus;
}

uint8_t bmp085Read(uint8_t addr2, uint8_t numData)
{
	if(i2cRead(BMP085_ADDRESS, addr2, BMPBuffer, numData)==CPAL_FAIL)
		BMPStatus=BMP085_FAIL;

	return BMPStatus;
}

uint16_t bmp085ReadInt(uint8_t addr)
{


	if(bmp085Read(addr,2) == BMP085_FAIL)
		return 0x00;

	return BMPBuffer[0]<<8|BMPBuffer[1];


}

// Calculate temperature given ut.
// Value returned will be in units of 0.1 deg C
int16_t bmp085GetTemperature(uint16_t ut)
{
  int32_t x1, x2;

  x1 = (((int32_t)ut - (int32_t)ac6)*(int32_t)ac5) >> 15;
  x2 = ((int32_t)mc << 11)/(x1 + md);
  b5 = x1 + x2;

  return ((b5 + 8)>>4);
}

int32_t bmp085GetPressure(uint32_t up)
{
	  int32_t x1, x2, x3, b3, b6, p;
	  uint32_t b4, b7;

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

uint16_t bmp085ReadUT()
{

	BMPBuffer[0]=0x2E;
	if(bmp085Write(0xF4,1) == BMP085_FAIL)
		return 0x00;

	delay(5);

	return bmp085ReadInt(0xF6);
}

uint32_t bmp085ReadUP()
{

	BMPBuffer[0]=0x34 + (OSS<<6);
	if(bmp085Write(0xF4,1) == BMP085_FAIL)
		return 0x00;

	delay(2 + (3 << OSS));


	if(bmp085Read(0xF6,3) == BMP085_FAIL)
		return 0x00;

	return (((uint32_t)BMPBuffer[0]<<16)|((uint32_t)BMPBuffer[1] << 8) | ((uint32_t)BMPBuffer[2])) >> (8-OSS);

}

float getBMP085Temperature()
{
	if (BMPStatus == BMP085_FAIL)
	{
		i2cReset();
		if(bmp085Calibration() == BMP085_FAIL)
			return -500.0;
	}

	int16_t t=bmp085GetTemperature(bmp085ReadUT());

	return (float)t * 0.10;

}

float getBMP085Pressure()
{
	if (BMPStatus == BMP085_FAIL)
	{
		getBMP085Temperature();
		if(BMPStatus == BMP085_FAIL)
			return 0.0;
	}

	uint32_t up=bmp085ReadUP();
	//DEBUG("%ld",up);
	int32_t p=bmp085GetPressure(up);

	return ((float)p/pow(1-(ALT/44330.0),5.255))/100.0;

}
