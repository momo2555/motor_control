/*
 * odometry.cpp
 *
 *  Created on: 26 mai 2021
 *      Author: shado
 */

#include <odometry.h>

odometry::odometry() {
	// TODO Auto-generated constructor stub

}
void odometry::setup(coor* pos, velocity* speed, clock* Clock) {
	float dt = (float) (Clock->getTimeDt());
	//get w v speeds
	speed->w = (speed->vr - speed->vl)/this->encDis;
	speed->v = (speed->vl + speed->vr)/2;

	//get the position
	pos->theta = pos->theta + speed->w * dt/1000.0;
	pos->x = pos->x + cos(pos->theta)*speed->v*dt/1000.0;
	pos->y = pos->y + sin(pos->theta)*speed->v*dt/1000.0;


}


