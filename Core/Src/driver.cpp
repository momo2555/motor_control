/*
 * driver.cpp
 *
 *  Created on: May 19, 2021
 *      Author: shado
 */

#include "driver.h"

driver::driver(CAN_HandleTypeDef* hcan, TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim3
			, UART_HandleTypeDef* huart2,GPIO_cfg RightMotTo, GPIO_cfg RightMotFor, GPIO_cfg LeftMotTo,
			GPIO_cfg LeftMotFor) {
	// control all HAL functions
	this->hcan = hcan;
	this->htim1 = htim1;
	this->htim2 = htim2;
	this->htim3 = htim3;
	this->huart2 = huart2;
	this->RightMotTo = RightMotTo;
	this->RightMotFor = RightMotFor;
	this->LeftMotTo = LeftMotTo;
	this->LeftMotFor = LeftMotFor;

}
void driver::setPowerRight(double power){
	if (power > 1) {
		power = 1;
	}else if (power < -1) {
		power = -1;
	}
	if (power < 0) {
		power = (-1)*power;
		this->setDirRight(FORWARD_RIGHT);
	}else {
		this->setDirRight(TOWARD_RIGHT);
	}
	uint16_t alpha = power*10000;
	this->genPWMRight(alpha);
}
void driver::setPowerLeft(double power){
	if (power > 1) {
		power = 1;
	}else if (power < -1) {
		power = -1;
	}
	if (power < 0) {
		power = (-1)*power;
		this->setDirLeft(FORWARD_LEFT);
	}else {
		this->setDirLeft(TOWARD_LEFT);
	}
	uint16_t alpha = power*10000;
	this->genPWMLeft(alpha);
}

void driver::genPWMRight(uint16_t alpha){
	__HAL_TIM_SET_COMPARE(htim1, TIM_CHANNEL_1, alpha);
}

void driver::genPWMLeft(uint16_t alpha){
	__HAL_TIM_SET_COMPARE(htim1, TIM_CHANNEL_2, alpha);
}

void driver::setDirLeft(int dir){
	stopLeftMot();
	if (dir==FORWARD_LEFT) {
		HAL_GPIO_WritePin(LeftMotFor.port, LeftMotFor.pin, HIGH);
	}else  if (dir==TOWARD_LEFT){
		HAL_GPIO_WritePin(LeftMotTo.port, LeftMotTo.pin, HIGH);
	}

}

void driver::setDirRight(int dir){
	stopRightMot();
	if (dir==FORWARD_RIGHT) {
		HAL_GPIO_WritePin(RightMotFor.port, RightMotFor.pin, HIGH);
	}else  if (dir==TOWARD_RIGHT){
		HAL_GPIO_WritePin(RightMotTo.port, RightMotTo.pin, HIGH);
	}

}

void driver::stopLeftMot() {

	HAL_GPIO_WritePin(LeftMotTo.port, LeftMotTo.pin, LOW);
	HAL_GPIO_WritePin(LeftMotFor.port, LeftMotFor.pin, LOW);
}

void driver::stopRightMot(){
	HAL_GPIO_WritePin(RightMotTo.port, RightMotTo.pin, LOW);
	HAL_GPIO_WritePin(RightMotFor.port, RightMotFor.pin, LOW);
}

long driver::getRightEncTicks(){
	long val = __HAL_TIM_GET_COUNTER(htim2)>>2;
	return val;
}
long driver::getLeftEncTicks(){
	return __HAL_TIM_GET_COUNTER(htim3)>>2;
}
void driver::printf(char* msg){
	HAL_UART_Transmit(huart2, (uint8_t*)msg, strlen(msg), 100);
}
