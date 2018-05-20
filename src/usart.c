/*
 * @file	usart.c
 * @date	May 18, 2018
 * @author	robin
 * @brief   USART Functions
 */

#include "usart.h"
#include <string.h>

UART_HandleTypeDef huart1;

void BSP_USART_Init(void)
{
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 38400;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(&huart1);
}

void BSP_USART_DeInit(void)
{
	HAL_UART_DeInit(&huart1);
}

void BSP_USART_PutChar(UART_HandleTypeDef *huart, const char c)
{
	HAL_UART_Transmit(huart, (uint8_t*)&c, 1, HAL_MAX_DELAY);
}

void BSP_USART_Write(UART_HandleTypeDef *huart, const char *string)
{
	HAL_UART_Transmit(huart, (uint8_t*)string, strlen(string), HAL_MAX_DELAY);
}

void BSP_USART_WriteLn(UART_HandleTypeDef *huart, const char *string)
{
	BSP_USART_Write(huart, string);
	BSP_USART_Write(huart, "\r\n");
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if (huart->Instance == USART1)
	{
		__HAL_RCC_USART1_CLK_ENABLE();

		GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		__HAL_RCC_USART1_CLK_DISABLE();

		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9|GPIO_PIN_10);
		HAL_NVIC_DisableIRQ(USART1_IRQn);
	}
}
