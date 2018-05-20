/*
 * @file	flash_if.c
 * @date	May 20, 2018
 * @author	robin
 * @brief   Description of file here...
 */

#include "flash_if.h"

void FLASH_If_Erase(uint32_t start)
{
	uint32_t numSectors = 0;
	uint32_t pageError = 0;
	FLASH_EraseInitTypeDef EraseInit;
	HAL_StatusTypeDef status = HAL_OK;

	HAL_FLASH_Unlock();


}
