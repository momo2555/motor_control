/*
 * memory.cpp
 *
 *  Created on: May 16, 2021
 *      Author: shado
 */

#include "memory.h"


memory::memory() {
	// TODO Auto-generated constructor stub
	/*this->datas.encDis = 9.332;
	this->datas.encWheelRadius = 4.23;
	this->datas.left_Kd = 0.012;
	this->datas.left_Ki = 0.543;
	this->datas.left_Kp = 1.234;
	this->datas.motDis = 8.998;
	this->datas.motWheelRadius = 4.23;
	this->datas.right_Kd= 0.032;
	this->datas.right_Ki= 0.123;
	this->datas.right_Kp= 1.4;
	this->datas.dt = 10;*/

}
void memory::write(uint16_t baseAddr, uint8_t *data, uint8_t len) {
	uint8_t i;
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t wlen = (len/4) + len%4;
	HAL_FLASH_Unlock();
	for(i=0;i<wlen;i++) {
		status = HAL_FLASH_Program(FLASH_PROC_PROGRAMWORD, MEMSTART + baseAddr, data[i*4]);
		i++;
	}
	HAL_FLASH_Lock();
}
void memory::read(uint16_t baseAddr, uint8_t *buffer, uint8_t len){
	uint8_t *wAddr;
	wAddr = (uint8_t *)(MEMSTART + baseAddr);
	while(len--){
		*buffer++=*wAddr++;
	}

}
void memory::save_to_flash(uint8_t *data, int size)
{
	int dlen32 = (int) (size/4)	+ (int) ((size%4) != 0);
	uint32_t data_to_FLASH[dlen32];
	//memset((uint8_t*)data_to_FLASH, 0, strlen((char*)data_to_FLASH));
	//strcpy((char*)data_to_FLASH, (char*)data);
	//uint32_t* dtf;
	//uint8_t* dd;
	for(int i = 0;i<dlen32;i++) {
		data_to_FLASH[i] = *((uint32_t*)(data+i*4));
	}
	//data_to_FLASH = *((uint32_t*) data);
	uint32_t data_length = dlen32;
	uint16_t pages = (size/page_size)
									+ (int)((size%page_size) != 0);
	  /* Unlock the Flash to enable the flash control register access *************/
	  HAL_FLASH_Unlock();

	  /* Allow Access to option bytes sector */
	  HAL_FLASH_OB_Unlock();

	  /* Fill EraseInit structure*/
	  FLASH_EraseInitTypeDef EraseInitStruct;
	  EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	  EraseInitStruct.PageAddress = FLASH_STORAGE;
	  EraseInitStruct.NbPages = pages;
	  uint32_t PageError;

	  uint32_t write_cnt=0, index=0;

	  HAL_StatusTypeDef status;
	  status = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
	  //status = HAL_OK;
	  while(index < data_length)
	  {
		  if (status == HAL_OK)
		  {
			  status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_STORAGE+write_cnt, data_to_FLASH[index]);
			  if(status == HAL_OK)
			  {
				  write_cnt += 4;
				  index++;
			  }
		  }
	  }

	  HAL_FLASH_OB_Lock();
	  HAL_FLASH_Lock();
}

void memory::read_flash(uint8_t* data)
{
	volatile uint32_t read_data;
	volatile uint32_t read_cnt=0;
	do
	{
		read_data = *(uint32_t*)(FLASH_STORAGE + read_cnt);
		if(read_data != 0xFFFFFFFF)
		{
			data[read_cnt] = (uint8_t)read_data;
			data[read_cnt + 1] = (uint8_t)(read_data >>  8);
			data[read_cnt + 2] = (uint8_t)(read_data >> 16);
			data[read_cnt + 3] = (uint8_t)(read_data >> 24);
			read_cnt += 4;
		}
	}while(read_data != 0xFFFFFFFF);
}

void memory::readData(AllData* data)
{

	this->read_flash((uint8_t*)data);
}
void memory::saveData(AllData* data)
{
	this->save_to_flash((uint8_t*)data, sizeof(AllData));
}
void memory::readMemory()
{
	this->readData(&(this->datas));
}
void memory::saveMemory(AllData newdatas)
{
	this->datas = newdatas;
	this->saveData(&(this->datas));
}
AllData memory::getMemory()
{
	return this->datas;
}
