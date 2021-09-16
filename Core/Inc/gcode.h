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
	gcode(driver* driverCtrl);
	void readInstruction(char* stringCmd);
	//void exec();
	bool get(char val, long* cont); // check if a command is in the string
	bool get(char val, float* cont);
private:
	void addCmd(char val, float cont1, long cont2);
	bool isInt(char val); //0 -> is float // 1 -> is integer
	char otherCase(char val);
	driver* driverCtrl;
	char* aint;
	char *aflt;
	int nCmd; //the number of commands
	Gcmd* listCmd; // list of all commands

	//void fastMov();

};

#endif /* GCODE_H_ */
