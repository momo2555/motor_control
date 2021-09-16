/*
 * pid.cpp
 *
 *  Created on: May 16, 2021
 *      Author: shado
 */

#include "pid.h"

pid::pid() {
	// TODO Auto-generated constructor stub
	this->last_error = 0;
	this->integral = 0;

}

float pid::getConsign(float Err, float Cons, clock* clock) {

	float dt = clock->getTimeDt();
	float proportional = this->Kp * Err;
	this->integral = this->integral + this->Ki * Err*dt;
	float derivate = this->Kd*(Err - this->last_error)/dt;

	this->last_error = Err;

	return proportional + derivate + this->integral;

}

