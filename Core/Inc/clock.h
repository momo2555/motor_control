/*
 * clock.h
 *
 *  Created on: May 21, 2021
 *      Author: shado
 */

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_
#include "stm32f3xx_hal.h"
class clock {
public:
	clock();
	void time();
	long getTime();
	long getTimeDt();
private:
	long lastTime;


};

#endif /* INC_CLOCK_H_ */
