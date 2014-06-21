/*
 * mpl3115.h
 *
 *  Created on: Jun 5, 2014
 *      Author: Kevin
 */

#ifndef MPL3115_H_
#define MPL3115_H_

#include "spark_wiring.h"
#include "i2c_comm.h"

#define MPL3115_ADDR 0x60
#define CTRL_REG1 0x26
#define PT_DATA_CFG 0x13
#define DR_STATUS 0x06
#define OUT_P_MSB 0x01
#define OUT_T_MSB 0x04

#define MPL3115_FAIL 0
#define MPL3115_SUCCESS 1

class MPL3115 {
private:
	float mpl3115Pressure;
	float mpl3115Temperature;
	void toggleOST(void);
	uint8_t init();
	I2C *i2c;
public:
	MPL3115();
	uint8_t measure(void);
	float getPressure(void);
	float getTemperature(void);

};



#endif /* MPL3115_H_ */
