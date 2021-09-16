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
	speed->vr = speed->vr + speed->w * this->motDis;
	speed->vl = speed->vl + speed->w * this->motDis;
}

