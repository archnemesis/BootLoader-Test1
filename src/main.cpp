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
#include "diag/Trace.h"
#include "stm32f4xx_hal.h"
#include "gpio.h"

#define APPLICATION_ADDRESS 0x08008000

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
	// At this stage the system clock should have already been configured
	// at high speed.

	if (((*(volatile uint32_t*)APPLICATION_ADDRESS) & 0x2FF00000) == 0x20000000)
	{
		JumpAddress = *(volatile uint32_t*) (APPLICATION_ADDRESS + 4);
		JumpToApplication = (void (*)(void))JumpAddress;

		__set_MSP(*(volatile uint32_t*) APPLICATION_ADDRESS);
		JumpToApplication();
	}
	else
	{
		BSP_GPIO_Init();

		HAL_GPIO_WritePin(GPIO_LED2_PORT, GPIO_LED2_PIN, GPIO_PIN_SET);
	}

	// Infinite loop
	while (1)
	{
		// Add your code here.
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
