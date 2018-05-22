/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diag/Trace.h"
#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "usart.h"
#include "fmc.h"
#include "crc.h"
#include "firmware_metadata.h"
#include "flash_if.h"
#include "iap.h"

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

void (*JumpToApplication)(void);
uint32_t JumpAddress;

int main(int argc, char* argv[])
{

	BSP_GPIO_Init();

	if (HAL_GPIO_ReadPin(GPIO_BTNUP_PORT, GPIO_BTNUP_PIN) == GPIO_PIN_RESET)
	{
#ifdef DEBUG
		trace_printf("Boot switch engaged, entering bootloader...\n");
#endif

		BSP_USART_Init();
		FLASH_If_Init();
		IAP_Init();
	}
	else
	{
#ifdef DEBUG
			trace_printf("Found application signature: %#010x\n",
					((*(volatile uint32_t*) APPLICATION_ADDRESS) & 0x2FF00000));
#endif

		if (((*(volatile uint32_t*) APPLICATION_ADDRESS) & 0x2FF00000)
				== 0x20000000)
		{
			FirmwareMetadata_t *fw_meta =
					(FirmwareMetadata_t *) (APPLICATION_ADDRESS
							+ APPLICATION_FW_META_OFFSET);

#ifdef DEBUG
			trace_printf("Found firmware version: %d.%d.%d\n",
					fw_meta->major,
					fw_meta->minor,
					fw_meta->rev
					);
#endif

			JumpAddress = *(volatile uint32_t*) (APPLICATION_ADDRESS + 4);
			JumpToApplication = (void (*)(void))JumpAddress;

			__set_MSP(*(volatile uint32_t*) APPLICATION_ADDRESS);
			JumpToApplication();
		}
		else
		{
#ifdef DEBUG
			trace_printf("No firmware signature found or firmware signature invalid\n");
#endif

			while (1)
			{

			}
		}
	}

	// Infinite loop
	while (1)
	{
		// Add your code here.
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
