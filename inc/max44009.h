/*
 * max44009.h
 *
 *  Created on: Mar 24, 2014
 *      Author: Kevin
 */

#ifndef MAX44009_H_
#define MAX44009_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <math.h>
#include "debug.h"
#include "i2c.h"

#define MAX44009_FAIL 0
#define MAX44009_ACTIVE 1

float max44009GetLux(void);

#ifdef __cplusplus
}
#endif



#endif /* MAX44009_H_ */
