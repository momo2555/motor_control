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

	if (this->position == LEFT) {
		actualTicks = Driver->getLeftEncTicks();
	}else if(this->position == RIGHT) {
		actualTicks = Driver->getRightEncTicks();
	}
	long dTicks = actualTicks - lastTicks;

	if (abs(dTicks) > maxTickPerDt) {
		dTicks = ((dTicks>=0)?1:-1)*(65535>>2) -  dTicks;
	}
	ticks = actualTicks;
	return ((float) dTicks) / ((float) Clock->getTimeDt()) * K * 1000.0; // k m per meterS

}



/*float getDistance() {

}*/
