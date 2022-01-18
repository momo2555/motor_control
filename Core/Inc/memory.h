/*
 * memory.h
 *
 *  Created on: May 16, 2021
 *      Author: shado
 */
#include "stdint.h"
#include "stm32f3xx_hal.h"
#include "string.h";
#ifndef MEMORY_H_
#define MEMORY_H_
#define MEMSTART 0x0000000
#define FLASH_STORAGE 0x0800F000//0x08005000
#define page_size 0x800

struct AllData {
	float right_Kp, right_Ki, right_Kd;
	float left_Kp, left_Ki, left_Kd;
	float encWheelRadiusRight, motWheelRadius;
	float encDis, motDis, K;
	float dt;
	float encWheelRadiusLeft;
};
typedef AllData AllData;
class memory {
public:
	memory();
	void readMemory();
	void saveMemory(AllData newdatas);
	AllData getMemory();
private:
	AllData datas;
	void write(uint16_t baseAddr, uint8_t *data, uint8_t len);
	void read(uint16_t baseAddr, uint8_t *buffer, uint8_t len);
	void read_flash(uint8_t* data);
	void save_to_flash(uint8_t *data, int size);
	void readData(AllData* data);
	void saveData(AllData* data);
};

#endif /* MEMORY_H_ */
