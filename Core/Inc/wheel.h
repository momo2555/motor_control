/*
 * wheel.h
 *
 *  Created on: May 21, 2021
 *      Author: shado
 */

#ifndef INC_WHEEL_H_
#define INC_WHEEL_H_
#include "driver.h"
#include "clock.h"
typedef enum {
	LEFT, RIGHT
} WHEEL_POSITION;

class wheel {
public:

	wheel(WHEEL_POSITION pos, driver* driver);
	void setPower(double power);
	double getLinearSpeed(clock* Clock); //dt en seconde

	float getWheelEncRadius() {return WheelEncRadius;}
	void setWheelEncRadius(float WheelMotRadius) {this->WheelMotRadius = WheelMotRadius;}

	float getWheelMotRadius() {return WheelMotRadius;}
	void setWheelMotRadius(float WheelMotRadius) {this->WheelMotRadius = WheelMotRadius;}

	float getK() {return K;}
	void setK(float K) {this->K = K;}
private:
	driver* Driver;
	WHEEL_POSITION position;
	float WheelEncRadius;
	float WheelMotRadius;
	float K;
	long ticks;
	int maxTickPerDt;

};

#endif /* INC_WHEEL_H_ */
