/*
 * @file	flash_if.h
 * @date	May 20, 2018
 * @author	robin
 * @brief   Description of file here...
 */

#ifndef INCLUDE_FLASH_IF_H_
#define INCLUDE_FLASH_IF_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"

enum
{
	FLASHIF_OK = 0,
	FLASHIF_ERASEKO,
	FLASHIF_WRITE_CTRL_ERROR,
	FLASHIF_WRITE_ERROR,
	FLASHIF_PROTECTION_ERROR
};

enum
{
	FLASHIF_PROTECTION_NONE = 0,
	FLASHIF_PROTECTION_PCROP_ENABLED = 1,
	FLASHIF_PROTECTION_WRP_ENABLED = 2,
	FLASHIF_PROTECTION_RDP_ENABLED = 4
};

enum
{
	FLASHIF_WRP_ENABLE,
	FLASHIF_WRP_DISABLE
};

void FLASH_If_Erase(uint32_t start);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_FLASH_IF_H_ */
