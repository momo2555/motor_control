/*
 * robot.cpp
 *
 *  Created on: May 16, 2021
 *      Author: shado
 */

#include "robot.h"



robot::robot(driver* driver, memory* mem) {
	// TODO Auto-generated constructor stub
	this->Memory = mem;
	this->Clock = new clock();
	this->Driver = driver;
	this->RightWheel = new wheel(RIGHT, driver);
	this->LeftWheel  = new wheel(LEFT, driver);
	this->RightPID   = new pid();
	this->LeftPID    = new pid();
	this->odo        = new odometry();
	this->DiffDrive  = new diffDrive();
	mode = MOTION_CONTROLED;
	position.x = 0;
	position.y = 0;
	position.theta = 0.0;
	speed.w = 0; speed.v = 0; speed.vl = 0; speed.vr = 0;
	/*read propreties from memory*/
	this->getFromMemory();
}
void robot::setup() {

	//get data from wheels
	speed.vr = RightWheel->getLinearSpeed(Clock);
	speed.vl = LeftWheel->getLinearSpeed(Clock);

	//get speed and position by the odometry routine
	odo->setup(&position, &speed, Clock);
	char msg[50];
	sprintf(msg,"%f,%f,%f,%f,%f \n",position.x, position.y, position.theta,speed.v, speed.w);
	Driver->printf(msg);
	//sprintf(msg,"vitesse gauche: %f \n\r", speed.vl);
	//Driver->printf(msg);
	if (mode == MOTION_CONTROLED) {

	}else if (mode == SPEED_ASSERV) {
		this->DiffDrive->getDiffSpeed(&speed);
	}else if (mode == DIFFERRENTIAL_DRIVED) {

	}
	Clock->time();

}
void robot::execInstruction(gcode* inst) {
	long G;
	long M;
	float P, I, D, A, X, Y;
		if(inst->get('G', &G)) {
			switch(G) {
			case 00:
				if(inst->get('X', &X)) {

				}
				if (inst->get('Y', &Y)) {

				}
				if (inst->get('A', &A)) {

				}
			break;
			case 01:
				if(inst->get('X', &X)) {

				}
				if (inst->get('Y', &Y)) {

				}
				if (inst->get('A', &A)) {

				}
			break;
			case 10:
				if(inst->get('I', &I)) {

				}
				if (inst->get('J', &J)) {

				}
			break;
			case 11:
				if(inst->get('I', &I)) {

				}
				if (inst->get('J', &J)) {

				}
			break;
			case 26:
				float X;
				float Y;
				if (inst->get('X', &X)) {
					this->Driver->setPowerRight(X);
				}
				if (inst->get('Y', &Y)) {
					this->Driver->setPowerLeft(Y);
				}

			break;
			}
		}else if (inst->get('M', &M)){
			switch (M){
			case 301: //PID roue gauche

				if(inst->get('P', &P)) LeftPID->setKp(P);
				if(inst->get('I', &I)) LeftPID->setKi(I);
				if(inst->get('D', &D)) LeftPID->setKd(D);
				break;

			case 302: //PID roue droite

				if(inst->get('P', &P)) RightPID->setKp(P);
				if(inst->get('I', &I)) RightPID->setKi(I);
				if(inst->get('D', &D)) RightPID->setKd(D);
				break;

			case 311: //diamètre roue codeuse droite

				if(inst->get('D', &D)) RightWheel->setWheelEncRadius(D);
				break;
			case 312: //diamètre roue codeuse gauche
				if(inst->get('D', &D)) LeftWheel->setWheelEncRadius(D);
				break;
			case 313: //distance entre les roues codeuses

				break;
			case 321: //distances entre les roues motrices
				break;
			case 322:
				break;
			case 323:
				break;

			case 400: //save in memory
				saveInMemory();
				break;
			case 401: //read memry
				getFromMemory();

			}
		}
}

void robot::saveInMemory() {
	AllData memStruct;
	this->Memory->readMemory();
	memStruct = this->Memory->getMemory();
	memStruct.encDis = odo->getEncDis();

	memStruct.encWheelRadiusRight = RightWheel->getWheelEncRadius();
	memStruct.encWheelRadiusLeft = LeftWheel->getWheelEncRadius();
	memStruct.motWheelRadius = RightWheel->getWheelMotRadius();
	memStruct.motDis = DiffDrive->getMotDis();
	memStruct.K = RightWheel->getK();

	memStruct.left_Kd = LeftPID->getKd();
	memStruct.left_Ki = LeftPID->getKi();
	memStruct.left_Kp = LeftPID->getKp();

	memStruct.right_Kd = RightPID->getKd();
	memStruct.right_Ki = RightPID->getKi();
	memStruct.right_Kp = RightPID->getKp();

	this->Memory->saveMemory(memStruct);

}
void robot::getFromMemory() {
	AllData memStruct;
	this->Memory->readMemory();
	memStruct = this->Memory->getMemory();
	odo->setEncDis(memStruct.encDis);
	/*char msg[50];
	sprintf(msg,"theta: %f \n\r",memStruct.encDis);
	Driver->printf(msg);*/
	RightWheel->setWheelEncRadius(memStruct.encWheelRadiusRight);
	RightWheel->setWheelMotRadius(memStruct.motWheelRadius);
	LeftWheel->setWheelEncRadius(memStruct.encWheelRadiusLeft);
	LeftWheel->setWheelMotRadius(memStruct.motWheelRadius);

	DiffDrive->setMotDis(memStruct.motDis);
	RightWheel->setK(memStruct.K);
	LeftWheel->setK(memStruct.K);

	LeftPID->setKd(memStruct.left_Kd );
	LeftPID->setKi(memStruct.left_Ki);
	LeftPID->setKp(memStruct.left_Kp);

	RightPID->setKd(memStruct.right_Kd);
	RightPID->setKi(memStruct.right_Ki);
	RightPID->setKp(memStruct.right_Kp);
}
