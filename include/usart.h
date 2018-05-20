/*
 * @file	usart.h
 * @date	May 18, 2018
 * @author	robin
 * @brief   USART Functions
 */

#ifndef INCLUDE_USART_H_
#define INCLUDE_USART_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_usart.h"

#ifdef __cplusplus
extern "C" {
#endif

extern UART_HandleTypeDef huart1;

/**
 * Initialize the USART hardware.
 */
void BSP_USART_Init(void);

/**
 * De-initialize the USART hardware.
 */
void BSP_USART_DeInit(void);

/**
 * Send a single character via USART.
 *
 * @param c
 * @return void
 */
void BSP_USART_PutChar(UART_HandleTypeDef *huart, const char c);

/**
 * Send a null-terminated string via USART.
 *
 * @param string
 * @return void
 */
void BSP_USART_Write(UART_HandleTypeDef *huart, const char *string);

/**
 * Send a null-terminated string followed by a newline character via USART.
 *
 * @param string
 * @return null
 */
void BSP_USART_WriteLn(UART_HandleTypeDef *huart, const char *string);

#define usart_write(s) BSP_USART_Write(&huart1, s)
#define usart_writeln(s) BSP_USART_WriteLn(&huart1, s)

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_USART_H_ */
