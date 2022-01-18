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
	//this->getFromMemory();
	//pose le debug à false
	testDebug = false;
}
void robot::setup() {
	float err;
	//get data from wheels
	speed.vr = RightWheel->getLinearSpeed(Clock);
	speed.vl = LeftWheel->getLinearSpeed(Clock);

	//get speed and position by the odometry routine
	odo->setup(&position, &speed, Clock);
	char msg[50];




	//sprintf(msg,"vitesse gauche: %f \n\r", speed.vl);
	//Driver->printf(msg);
	if (mode == MOTION_CONTROLED) {

	}else if (mode == SPEED_ASSERV) {
		err = cons.v - speed.v; //soustracteur
		speed.v = err;
		err = cons.w - speed.w;
		speed.w = err;
		//on réccupère les erreurs en vitesses différentielles
		this->DiffDrive->getDiffSpeed(&speed);
		//on corrige avec un PID
		speed.vl = this->LeftPID->getConsign(speed.vl, this->Clock);
		speed.vr = this->RightPID->getConsign(speed.vr, this->Clock);
		//On envoie la consigne
		this->LeftWheel->setPower(speed.vl);
		this->RightWheel->setPower(speed.vr);

	}else if (mode == DIFFERRENTIAL_DRIVED) {
		//calcul de l'erreur
		err = cons.vl - speed.vl;
		speed.vl = err;
		err = cons.vr - speed.vr;
		speed.vr = err;
		//correction avec PID
		speed.vl = this->LeftPID->getConsign(speed.vl, this->Clock);
		speed.vr = this->RightPID->getConsign(speed.vr, this->Clock);
		//On envoie la consigne
		this->LeftWheel->setPower(speed.vl);
		this->RightWheel->setPower(speed.vr);

	}else if (mode == OPEN_LOOP) {
		this->LeftWheel->setPower(cons.vl);
		this->RightWheel->setPower(cons.vr);
		if (testDebug) {
			//temps, consigneR, consigneL, sortieR, sortieL
			sprintf(msg, "%d;%f;%f;%f;%f \n", this->Clock->getTime(), cons.vr, cons.vl, speed.vr, speed.vl);
			Driver->printf(msg);
		}
	}
	/*if (testDebug) {
			sprintf(msg,"%d,%f,%f,%f,%f,%f \n",Clock->getTimeDt(), position.x, position.y, position.theta,speed.v, speed.w);
			sprintf(msg, "consR=%f ,consL=%f, ", speed.vr, speed.vl);
			//sprintf(msg,"EncTickLeft=%d;  EncTickRight=%d \n", this->Driver->getLeftEncTicks(), this->Driver->getRightEncTicks());
			Driver->printf(msg);
	}*/
	Clock->time();

}
void robot::execInstruction(gcode* inst) {
	long G;
	long M, P;
	float  I, D, A, X, Y, J;
	bool isG = inst->get('G', &G);
	bool isM = inst->get('M', &M);
	char msg[50];

		if(isG) {
			//sprintf(msg,"commmande G = %d\n", G);
			//this->Driver->printf(msg);
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
				if(inst->get('I', &I) && inst->get('J', &J)) {
					this->setDiffSpeedCons(J, I);
				}
			break;
			case 26:
				//float X;
				//float Y;
				if (inst->get('X', &X)&&inst->get('Y', &Y)) {
					this->setOpenLoopCons(X, Y);
				}


				break;
			case 92:
				if (inst->get('X', &X)&&inst->get('Y', &Y)&&inst->get('A', &A)) {
					this->setPosCons(X, Y, A);
				}
				break;
			}
		}else
		if (isM){

			//sprintf(msg,"commmande M = %d\n", M);
			//this->Driver->printf(msg);

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
				if(inst->get('D', &D)) odo->setEncDis(D);
				break;
			case 321: //distances entre les roues motrices
				if(inst->get('D', &D)) DiffDrive->setMotDis(D);
				break;
			case 322: //constante de gain moteur
				if(inst->get('I', &I)) {this->LeftWheel->setK(I);this->RightWheel->setK(I);}
				break;
			case 323:
				break;

			case 400: //save in memory
				saveInMemory();
				break;
			case 401: //read memry
				getFromMemory();
				break;
			case 402:


				if (inst->get('P', &P)) {
					switch (P) {
					case 1: //réccupère la distance entre les moteurs

						sprintf(msg,"d(entre les moteurs) = %f\n",this->DiffDrive->getMotDis());
						this->Driver->printf(msg);
						break;
					case 2: //réccupère la distance entre les encodeurs
						//char msg[50];
						sprintf(msg,"d(entre les encodeurs) = %f\n",this->odo->getEncDis());
						this->Driver->printf(msg);
						break;
					case 3: //infos PID
						sprintf(msg,"PID droite: P=%f; I=%f; D%f \n",this->RightPID->getKp(), this->RightPID->getKi(), this->RightPID->getKd());
						this->Driver->printf(msg);
						sprintf(msg,"PID gauche: P=%f; I=%f; D%f \n",this->LeftPID->getKp(), this->LeftPID->getKi(), this->LeftPID->getKd());
						this->Driver->printf(msg);
						break;
					}
				}
				break;
			case 403: //active le mode test debug

				this->testDebug = !this->testDebug;
			case 404: //réccupère les ticks des encodeurs enc=(gauche;droite)
				sprintf(msg,"enc=(%ld;%ld)\n", this->Driver->getLeftEncTicks(), this->Driver->getRightEncTicks());
				this->Driver->printf(msg);
				break;
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

	LeftPID->setKd(memStruct.left_Kd);
	LeftPID->setKi(memStruct.left_Ki);
	LeftPID->setKp(memStruct.left_Kp);

	RightPID->setKd(memStruct.right_Kd);
	RightPID->setKi(memStruct.right_Ki);
	RightPID->setKp(memStruct.right_Kp);
}
void robot::setVelocityCons(float linearSpeed, float angularSpeed){
	this->cons.v = linearSpeed;
	this->cons.w = angularSpeed;
	this->mode = SPEED_ASSERV;
}
void robot::setDiffSpeedCons(float rightSpeed, float leftSpeed){
	this->cons.vl = leftSpeed;
	this->cons.vr = rightSpeed;
	this->mode = DIFFERRENTIAL_DRIVED;
}
void robot::setPosCons(float x, float y, float theta){
	this->cons.x = x;
	this->cons.y = y;
	this->cons.theta = theta;
	this->mode = MOTION_CONTROLED;
}
void robot::setOpenLoopCons(float rightSpeed, float leftSpeed) {
	this->cons.vl = leftSpeed;
	this->cons.vr = rightSpeed;
	this->mode = OPEN_LOOP;
}
