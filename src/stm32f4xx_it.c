/*
 * @file	stm32f4xx_it.c
 * @date	May 18, 2018
 * @author	robin
 * @brief   Description of file here...
 */

#include "usart.h"

void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}
