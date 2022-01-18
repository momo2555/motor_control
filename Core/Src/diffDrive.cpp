/*
 * diffDrive.cpp
 *
 *  Created on: 26 mai 2021
 *      Author: shado
 */

#include <diffDrive.h>

diffDrive::diffDrive() {
	// TODO Auto-generated constructor stub

}
void diffDrive::getDiffSpeed(velocity* speed) {
	speed->vr = (speed->v + speed->w * this->motDis)/2;
	speed->vl = (speed->v - speed->w * this->motDis)/2;
}

