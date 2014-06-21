/*
 * i2c_comm.cpp
 *
 *  Created on: Jun 21, 2014
 *      Author: Kevin
 */
#include "i2c_comm.h"

I2C::I2C()
{
	initialize();
}

void I2C::initialize()
{
	I2C_InitTypeDef *InitStruct=(I2C_InitTypeDef *)malloc(sizeof(I2C_InitTypeDef));
	InitStruct->I2C_ClockSpeed          = 100000;                        /* Initialize the I2C_ClockSpeed member */
	InitStruct->I2C_Mode                = I2C_Mode_I2C;                  /* Initialize the I2C_Mode member */
	InitStruct->I2C_DutyCycle           = I2C_DutyCycle_2;               /* Initialize the I2C_DutyCycle member */
	InitStruct->I2C_OwnAddress1         = 0x00;                             /* Initialize the I2C_OwnAddress1 member */
	InitStruct->I2C_Ack                 = I2C_Ack_Enable;                /* Initialize the I2C_Ack member */
	InitStruct->I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;  /* Initialize the I2C_AcknowledgedAddress member */

	CPAL_I2C_StructInit(&I2C1_DevStructure);
	I2C1_DevStructure.CPAL_Mode = CPAL_MODE_MASTER;
	I2C1_DevStructure.CPAL_ProgModel = CPAL_PROGMODEL_INTERRUPT;
	I2C1_DevStructure.wCPAL_Options=0x00;

	I2C1_DevStructure.pCPAL_I2C_Struct = InitStruct;


	CPAL_I2C_Init(&I2C1_DevStructure);
}

uint8_t I2C::write(uint8_t slave, uint8_t addr2, uint8_t *buf, uint8_t numData)
{
	CPAL_TransferTypeDef tx;


	tx.pbBuffer=buf;
	tx.wAddr1=slave<<1;
	tx.wAddr2=addr2;
	tx.wNumData=numData;
	I2C1_DevStructure.pCPAL_TransferTx=&tx;

	if(CPAL_I2C_Write(&I2C1_DevStructure) == CPAL_PASS)
	{
		while((I2C1_DevStructure.CPAL_State != CPAL_STATE_READY) && (I2C1_DevStructure.CPAL_State != CPAL_STATE_ERROR) )
		{

		}

		if(I2C1_DevStructure.CPAL_State == CPAL_STATE_ERROR)
		{
			return CPAL_FAIL;
		}

	}
	else
		return CPAL_FAIL;

	return CPAL_PASS;
}

uint8_t I2C::read(uint8_t slave, uint8_t addr2, uint8_t *buf, uint8_t numData)
{
	CPAL_TransferTypeDef rx;
	rx.pbBuffer=buf;
	rx.wAddr1=slave<<1;
	rx.wAddr2=addr2;
	rx.wNumData=numData;
	I2C1_DevStructure.pCPAL_TransferRx=&rx;

	if(CPAL_I2C_Read(&I2C1_DevStructure)==CPAL_PASS)
	{
		while((I2C1_DevStructure.CPAL_State != CPAL_STATE_READY) && (I2C1_DevStructure.CPAL_State != CPAL_STATE_ERROR) )
		{
		}

		if(I2C1_DevStructure.CPAL_State == CPAL_STATE_ERROR)
		{
			return CPAL_FAIL;
		}

	}
	else
		return CPAL_FAIL;

	return CPAL_PASS;
}

void I2C::reset()
{
	CPAL_I2C_DeInit(&I2C1_DevStructure);
	CPAL_I2C_Init(&I2C1_DevStructure);
}



void I2C::scan()
{
    uint8_t results[256];
    for (uint8_t n=0;n<255;n++)
    {
    	if(write(n,0,&n,0) == CPAL_FAIL)
    		results[n]=0;
    	else
    		results[n]=1;
    	reset();
    }

    for(uint8_t n=0;n<255;n+=5)
    {
    	DEBUG("%X %X : %X %X : %X %X : %X %X : %X %X",n,results[n],n+1,results[n+1],n+2,results[n+2],n+3,results[n+3],n+4,results[n+4]);
    }

}

