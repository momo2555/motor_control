/*
 * clock.cpp
 *
 *  Created on: May 21, 2021
 *      Author: shado
 */

#include <clock.h>

clock::clock() {
	// TODO Auto-generated constructor stub
	time();

}

void clock::time() {
	this->lastTime = HAL_GetTick();
}
long clock::getTime() {
	return HAL_GetTick();
}
long clock::getTimeDt() {
	return getTime() - lastTime;
}
