/*
 * gcode.cpp
 *
 *  Created on: May 16, 2021
 *      Author: shado
 */

#include "gcode.h"

gcode::gcode(driver* driverCtrl) {
	// TODO Auto-generated constructor stub
	aint =  "GgMmNnSsPp";
	aflt  = "XxYyAaBbCcRrDd";
	this->driverCtrl = driverCtrl;
}

void gcode::readInstruction(char* stringCmd) {
	//free(this->listCmd);
	nCmd=0;//init cmdTab

	char space[2] = " ";
	char* lastChar = stringCmd + strlen(stringCmd);
	char* spacePos = strstr(stringCmd, space); //position of the first space character ' '(32)
	int len = (int)(spacePos - stringCmd);       //command length
	int next;    							      //next conversion
	char cmd;    							       //gcode character command (A to Z)
	char* temp;  							       //temp chars for float conversion (or int conversion)
	char*endptr; 							      //end pointer for conversion
	float f;     							     //for float conversion
	long i;      							   //for int conversion

	while(spacePos != NULL or len>0) {
		next = 0;
		temp = (char*)malloc(sizeof(char*)*(len-1));
		cmd = stringCmd[next];
		next+=1; //on enléve la lettre
		f=0.0;i=0;
		strcpy(temp, &(stringCmd[next]));

		if(isInt(cmd)) {
			i = strtol(temp, &endptr, 10); //convert to long
			if(temp==endptr)i=0.0;
		}else {
			f = strtof(temp, &endptr); //convert to float
			if(temp==endptr)f=0.0;
		}

		this->addCmd(cmd, f, i);

		stringCmd+=(len+1);
		spacePos = strstr(stringCmd, space);

		if(spacePos!=NULL) len = (int)(spacePos - stringCmd);
		else len = (int)(lastChar -  stringCmd);

		stringCmd;
		free(temp);
	}

}

void gcode::addCmd(char val, float cont1, long cont2) {
	if(nCmd < 20) {
		listCmd[nCmd].value = val;
		listCmd[nCmd].content1 = cont1;
		listCmd[nCmd].content2= cont2;
		nCmd++;
	}

}
bool gcode::get(char val, long* cont) {
	char _val = otherCase(val);
	for(int i = 0;i<nCmd;i++) {

		if(listCmd[i].value == val || listCmd[i].value == _val) {

			if (isInt(val)) {
				*cont = listCmd[i].content2;
			}
			return true;
		}
	}
	return false;
}
bool gcode::get(char val, float* cont) {
	char _val = otherCase(val);
		for(int i = 0;i<nCmd;i++) {

			if(listCmd[i].value == val || listCmd[i].value == _val) {
				if (!isInt(val)) {
					*cont = listCmd[i].content1;
				}
				return true;
			}
		}
		return false;
}
bool gcode::isInt(char val) {
	char _val = otherCase(val);
	bool ret = false;
	int n=strlen(aint);
	for(int i=0;i<n;i++){
		if(aint[i] == val || aint[i] == _val)  {
			return true;
		}
	}
	return false;

}
char gcode::otherCase(char val) {
	char _val = val;
	if ((uint8_t)val > 0x60) {
		_val = (char)((uint8_t)val - 0x20);
	} else {
		_val = (char)((uint8_t)val + 0x20);
	}
	return _val;
}

