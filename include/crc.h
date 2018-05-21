/*
 * @file	crc.h
 * @date	May 20, 2018
 * @author	robin
 * @brief   Description of file here...
 */

#ifndef INCLUDE_CRC_H_
#define INCLUDE_CRC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"

extern CRC_HandleTypeDef hcrc;

void BSP_CRC_Init(void);
uint32_t CRC32_Update(unsigned char ch, uint32_t crc);
uint32_t CRC32_Buffer(char *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_CRC_H_ */
