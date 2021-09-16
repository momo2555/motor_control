/*
 * driver.h
 *
 *  Created on: May 19, 2021
 *      Author: shado
 */
#include "stdio.h"
#include "stm32f3xx_hal.h"
#include "string.h"
//#include "intlib.h"
#ifndef SRC_DRIVER_H_
#define SRC_DRIVER_H_
#define	FORWARD_LEFT 1
#define TOWARD_LEFT -1
#define FORWARD_RIGHT -1
#define TOWARD_RIGHT 1
#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET

typedef struct {
	GPIO_TypeDef* port;
	int pin;
} GPIO_cfg ;
class driver {
public:
	driver(CAN_HandleTypeDef* hcan, TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim3
				, UART_HandleTypeDef* huart2, GPIO_cfg RightMotTo, GPIO_cfg RightMotFor, GPIO_cfg LeftMotTo,
				GPIO_cfg LeftMotFor);

	void setPowerRight(double power);
	/**
	 * Set power in the right motor
	 * @param power: double A power value that will be applied to the left motor
	 */
	void setPowerLeft(double power);
	void genPWMRight(uint16_t alpha);
	void genPWMLeft(uint16_t alpha);
	void setDirLeft(int dir);
	void setDirRight(int dir);
	void printf(char* msg);
	void stopLeftMot();
	void stopRightMot();
	long getRightEncTicks();
	long getLeftEncTicks();
private:
	CAN_HandleTypeDef* hcan;
	TIM_HandleTypeDef* htim1;
	TIM_HandleTypeDef* htim2;
	TIM_HandleTypeDef* htim3;
	UART_HandleTypeDef* huart2;

	GPIO_cfg RightMotTo;
	GPIO_cfg RightMotFor;
	GPIO_cfg LeftMotTo;
	GPIO_cfg LeftMotFor;

};

#endif /* SRC_DRIVER_H_ */
