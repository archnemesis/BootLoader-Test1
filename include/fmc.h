/*
 * @file	fmc.h
 * @date	May 19, 2018
 * @author	robin
 * @brief   Description of file here...
 */

#ifndef INCLUDE_FMC_H_
#define INCLUDE_FMC_H_

#define SDRAM_MODEREG_BURST_LENGTH_1 0x00
#define SDRAM_MODEREG_BURST_LENGTH_2 0x01
#define SDRAM_MODEREG_BURST_LENGTH_4 0x02
#define SDRAM_MODEREG_BURST_LENGTH_8 0x03

#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL			(0x00 << 3)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED		(0x01 << 3)

#define SDRAM_MODEREG_CAS_LATENCY_2					(0x02 << 4)
#define SDRAM_MODEREG_CAS_LATENCY_3					(0x03 << 4)

#define SDRAM_MODEREG_OPERATING_MODE_STANDARD 		0x00

#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED	(0x00 << 9)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE		(0x01 << 9)

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"

extern SDRAM_HandleTypeDef hsdram1;

void BSP_FMC_Init(void);
void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *hsdram);
void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef *hsdram);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_FMC_H_ */
