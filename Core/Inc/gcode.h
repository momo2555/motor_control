/*
 * gcode.h
 *
 *  Created on: May 16, 2021
 *      Author: shado
 */
//#include <iostream>
//#include <vector>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "driver.h"
#ifndef GCODE_H_
#define GCODE_H_

typedef struct {
	char value;
	float content1;
	long content2;
}Gcmd;
class gcode {
public:
	/**
	 * Constructeur de la classe GCode
	 * @param driverCtrl:driver* pointeur de la classe driver
	 */
	gcode(driver* driverCtrl);
	/**
	 * Lit une instruction Gcode sous forme de tableau de char. Le Gcode est ensuite décomposé en plusieurs variables
	 * que l'on peut réccupérer grâce aux fonctions get(nom de la variable à réccupérer)
	 * @param stringCmd: char* Tableau de caractères contenant le commande GCode à traîter
	 */
	void readInstruction(char* stringCmd);
	/**
	 * Permet de réccupérer la valeur d'une variable GCode de type long
	 * @param val:char Nom de la variable à réccupérer à donner sous la forme d'un char
	 * @param cont:long* Pointeur de la variable qui va contenir la valeur de la variable Gcode
	 * @return bool Retourne true s'il n'y pas d'erreur lors de la réccupération de la variable (cause d'erreur possible: si la
	 * variable n'existe pas par exemple)
	 */
	bool get(char val, long* cont); // check if a command is in the string
	/**
	 * Permet de réccupérer la valeur d'une variable GCode de type float
	 * @param val:char Nom de la variable à réccupérer à donner sous la forme d'un char
	 * @param cont:float* Pointeur de la variable qui va contenir la valeur de la variable Gcode
	 * @return bool Retourne true s'il n'y pas d'erreur lors de la réccupération de la variable (cause d'erreur possible: si la
	 * variable n'existe pas par exemple)
	 */
	bool get(char val, float* cont);
private:
	/**
	 * Ajoute une valeur GCode dans le tableau de commande "listCms". Cette fonction est déclarée en privée car elle est utilisée
	 * seulement par la fonction readInstruction()
	 * @param val:char Nom de la varioable Gcode à ajouter
	 * @param cont1:float Contenu de la variable Gcode pour un type float
	 * @param cont2:long Contenu de la variable Gcode pour un type long
	 */
	void addCmd(char val, float cont1, long cont2);
	/**
	 * Vérifie si la variable est de type entie. (!!Attention instruction gourmande)
	 * @param val:char Nom de la variable Gcode à vérifier
	 * @return bool Retourne True si la variable est de type entier sinon False
	 */
	bool isInt(char val); //0 -> is float // 1 -> is integer
	/**
	 * Convertie le caractère en majuscule quelle que soit sa casse pour éviter les problèmes de casse.
	 * @param val:char caractère à transformer
	 * @return caractère en majuscule
	 */
	char otherCase(char val);

	driver* driverCtrl;
	char* aint;
	char *aflt;
	int nCmd; //the number of commands
	Gcmd listCmd[20]; // list of all commands

	//void fastMov();

};

#endif /* GCODE_H_ */
