/*
 * robot.h
 *
 *  Created on: May 16, 2021
 *      Author: shado
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include "wheel.h"
#include "pid.h"
#include "clock.h"
#include "driver.h"
#include "memory.h"
#include "odometry.h"
#include "gcode.h"
#include "memory.h"
#include "diffDrive.h"
typedef enum {
	MOTION_CONTROLED,
	DIFFERRENTIAL_DRIVED,
	SPEED_ASSERV,
	OPEN_LOOP

} MODE;


class robot {
public:
	/**
	 * Constrcuteur de la classe Robot. Composant principale du robot, gère la boucle principale et les composants du robot.
	 * @param driver Paramètre de type driver*, renseigner un objet driver qui permet à la classe robot d'accéder au élément extérieur
	 * du microcontrôleur
	 * @param mem Objet de type memory*: Objet mémoire permetant à la classe robot d'accéder à la mémoire
	 */
	robot(driver* driver, memory* mem);
	/**
	 * Fonction appelée à chaque interruption du timer d'asservissement. Cette fonction execute toute la boucle d'aservissement.
	 * En fonction du type d'asservissement : En position, en vitesse ou en vitesse différentielle la fonction les boucles d'aaservissemnt
	 * associées seront exécuter. Pour l'asservissement, on asservie d'abord la position et dans une seconde boucle la vitesse. Pour
	 * les aseervissement en vitesse on a juste un asservissement en vitesse (avec un convertisseur si on n'est pas en différentielle)
	 *
	 */
	void setup();
	/**
	 * Cette fonction lit une instruction Gcode (parsée sous la forme d'un objet GCode) en paramètre et l'execute.
	 * @param inst Instruction de gcode*. Instruction à éxecuter
	 */
	void execInstruction(gcode* inst);
	/**
	 * Enregistre tous les paramètres du robots et des sous classes de robot dans la mémoire du microcontrôleur.
	 */
	void saveInMemory();
	/**
	 * Met à jour tous les paramètre de la classe robot (et sous classes de robot) à jour avec les valeurs enregistrés dans la mémoire.
	 */
	void getFromMemory();
	void setVelocityCons(float linearSpeed, float angularSpeed);
	void setDiffSpeedCons(float rightSpeed, float leftSpeed);
	void setPosCons(float x, float y, float theta);
	void setOpenLoopCons(float rightSpeed, float leftSpeed);
private:
	memory* Memory;
	wheel* RightWheel;
	wheel* LeftWheel;
	pid* RightPID;
	pid* 	LeftPID;
	clock* Clock;
	driver* Driver;
	odometry* odo;
	MODE mode;
	consign cons;
	coor position;
	velocity speed;
	diffDrive* DiffDrive;
	bool testDebug;

};

#endif /* ROBOT_H_ */
