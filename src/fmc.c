/*
 * @file	fmc.c
 * @date	May 19, 2018
 * @author	robin
 * @brief   Description of file here...
 */

#include "fmc.h"
#include "gpio.h"

SDRAM_HandleTypeDef hsdram1;

void BSP_FMC_Init(void)
{
	FMC_SDRAM_TimingTypeDef SdramTiming;
	FMC_SDRAM_CommandTypeDef SdramCommand;

	hsdram1.Instance = FMC_SDRAM_DEVICE;
	hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
	hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
	hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
	hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
	hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
	hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
	hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
	hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_2;

	SdramTiming.LoadToActiveDelay = 2;
	SdramTiming.ExitSelfRefreshDelay = 10;
	SdramTiming.SelfRefreshTime = 7;
	SdramTiming.RowCycleDelay = 6;
	SdramTiming.WriteRecoveryTime = 5;
	SdramTiming.RPDelay = 2;
	SdramTiming.RCDDelay = 2;

	HAL_SDRAM_Init(&hsdram1, &SdramTiming);

	SdramCommand.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	SdramCommand.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
	SdramCommand.AutoRefreshNumber = 1;
	SdramCommand.ModeRegisterDefinition = 0;
	HAL_SDRAM_SendCommand(&hsdram1, &SdramCommand, 100);
	HAL_Delay(100);

	SdramCommand.CommandMode = FMC_SDRAM_CMD_PALL;
	SdramCommand.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
	SdramCommand.AutoRefreshNumber = 1;
	SdramCommand.ModeRegisterDefinition = 0;
	HAL_SDRAM_SendCommand(&hsdram1, &SdramCommand, 100);

	SdramCommand.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	SdramCommand.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
	SdramCommand.AutoRefreshNumber = 4;
	SdramCommand.ModeRegisterDefinition = 0;
	HAL_SDRAM_SendCommand(&hsdram1, &SdramCommand, 100);

	SdramCommand.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	SdramCommand.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
	SdramCommand.AutoRefreshNumber = 1;
	SdramCommand.ModeRegisterDefinition = (uint32_t) (
	SDRAM_MODEREG_BURST_LENGTH_1 |
	SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
	SDRAM_MODEREG_CAS_LATENCY_3 |
	SDRAM_MODEREG_OPERATING_MODE_STANDARD |
	SDRAM_MODEREG_WRITEBURST_MODE_SINGLE);

	HAL_SDRAM_SendCommand(&hsdram1, &SdramCommand, 100);
	HAL_SDRAM_ProgramRefreshRate(&hsdram1, 683);
}

static uint32_t FMC_Initialized = 0;

static void HAL_FMC_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if (FMC_Initialized)
	{
		return;
	}

	FMC_Initialized = 1;

	__HAL_RCC_FMC_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
			| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13
			| GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5
			| GPIO_PIN_8 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10
			| GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14
			| GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14
			| GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *hsdram)
{
	HAL_FMC_MspInit();
}

static void HAL_FMC_MspDeInit(void)
{
	if (FMC_Initialized == 0)
	{
		return;
	}

	FMC_Initialized = 0;

	__HAL_RCC_FMC_CLK_DISABLE();

	HAL_GPIO_DeInit(GPIOF,
			GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
					| GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13
					| GPIO_PIN_14 | GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOH, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

	HAL_GPIO_DeInit(GPIOG,
			GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8
					| GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOE,
			GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11
					| GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
					| GPIO_PIN_0 | GPIO_PIN_1);

	HAL_GPIO_DeInit(GPIOD,
			GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15
					| GPIO_PIN_0 | GPIO_PIN_1);
}

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef *hsdram)
{
	HAL_FMC_MspDeInit();
}
