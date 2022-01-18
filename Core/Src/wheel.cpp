/*
 * wheel.cpp
 *
 *  Created on: May 21, 2021
 *      Author: shado
 */

#include <wheel.h>
#include "math.h"

wheel::wheel(WHEEL_POSITION pos, driver* driver){
	this->position = pos;
	this->Driver = driver;
	if (this->position == LEFT) {
		ticks = driver->getLeftEncTicks();
	}else if(this->position == RIGHT) {
		ticks = driver->getRightEncTicks();
	}
	this->maxTickPerDt = 5000;
}
void wheel::setPower(double power){
	if (this->position == LEFT) {
		this->Driver->setPowerLeft(power);
	}else if (this->position == RIGHT) {
		this->Driver->setPowerRight (power);
	}

}
double wheel::getLinearSpeed(clock* Clock){
	long lastTicks = ticks;
	long actualTicks;
	char msg[50];
	if (this->position == LEFT) {
		actualTicks = Driver->getLeftEncTicks();
		sprintf(msg, "left wheel: %d \n", actualTicks);
	}else if(this->position == RIGHT) {
		actualTicks = Driver->getRightEncTicks();
		sprintf(msg, "right wheel: %d \n", actualTicks);
	}
	//this->Driver->printf(msg);
	long dTicks = actualTicks - lastTicks;

	if (abs(dTicks) > maxTickPerDt) {
		int maxTicks = 65535; //65535
		dTicks = ((dTicks>=0)?1:-1)*(maxTicks>>2) -  dTicks;
	}
	ticks = actualTicks;
	return ((float) dTicks) / ((float) Clock->getTimeDt()) * K * 1000.0; // k m per meterS

}



/*float getDistance() {

}*/
