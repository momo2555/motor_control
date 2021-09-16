/*
 * odometry.h
 *
 *  Created on: 26 mai 2021
 *      Author: shado
 */

#ifndef INC_ODOMETRY_H_
#define INC_ODOMETRY_H_
#include "clock.h"
#include "math.h"

#ifndef POS_STRUCT
#define POS_STRUCT
typedef struct {
	float theta, x, y ;
	float v, w;
} consign;
typedef struct {
	float x, y, theta;
} coor;
typedef struct {
	float w, v, vl, vr;
} velocity;
#endif

class odometry {
public:
	odometry();
	void setup(coor* pos, velocity* speed, clock* Clock);
	float getEncDis() {return this->encDis;}
	void setEncDis(float encDis) {this->encDis=encDis;}
private:
	float encDis;
};

#endif /* INC_ODOMETRY_H_ */
