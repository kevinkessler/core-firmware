/*
 * i2c_comm.h
 *
 *  Created on: Jun 21, 2014
 *      Author: Kevin
 */

#ifndef I2C_COMM_H_
#define I2C_COMM_H_

#include <stdlib.h>
#include "debug.h"
#include "cpal.h"
#include "cpal_i2c.h"
/*#include "stm32f10x_i2c.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
*/

extern CPAL_InitTypeDef I2C1_DevStructure;
extern void delay (uint32_t);

class I2C
{
public:
	static I2C *getInstance()
	{
		static I2C *instance;

		if (!instance)
			instance=new I2C();

		return instance;
	}

	uint8_t write(uint8_t slave, uint8_t addr2, uint8_t *buf, uint8_t numData);
	uint8_t read(uint8_t slave, uint8_t addr2, uint8_t *buf, uint8_t numData);
	void reset();
	void scan();

private:
	I2C(void);
	I2C(I2C const&);
	void operator=(I2C const&);
	void initialize(void);
};



#endif /* I2C_COMM_H_ */
