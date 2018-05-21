/*
 * @file	flash_if.c
 * @date	May 20, 2018
 * @author	robin
 * @brief   Description of file here...
 */

#include "flash_if.h"

void FLASH_If_Init(void)
{
	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP|FLASH_FLAG_PGSERR|FLASH_FLAG_WRPERR|FLASH_FLAG_OPERR);
	HAL_FLASH_Lock();
}

HAL_StatusTypeDef FLASH_If_Erase()
{
	uint32_t numSectors = 0;
	uint32_t pageError = 0;
	FLASH_EraseInitTypeDef EraseInit;
	HAL_StatusTypeDef status = HAL_OK;

	HAL_FLASH_Unlock();

	EraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInit.Banks = FLASH_BANK_BOTH;
	EraseInit.Sector = FLASH_SECTOR_2;
	EraseInit.NbSectors = FLASH_SECTOR_23 - FLASH_SECTOR_2;
	EraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;

	status = HAL_FLASHEx_Erase(&EraseInit, &pageError);

	HAL_FLASH_Lock();

	return status;
}

HAL_StatusTypeDef FLASH_If_Write(uint32_t destination, uint32_t *p_source,
		uint32_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint32_t i = 0;

	HAL_FLASH_Unlock();

	for (i = 0; i < length; i++)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, destination, (uint64_t)p_source[i]) == HAL_OK)
		{
			if (*(uint32_t *)destination != p_source[i])
			{
				status = HAL_ERROR;
				break;
			}

			destination += 4;
		}
		else {
			status = HAL_ERROR;
			break;
		}
	}

	HAL_FLASH_Lock();

	return status;
}
