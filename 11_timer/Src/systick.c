/*
 * systick.c
 *
 *  Created on: Aug 6, 2023
 *      Author: fahmad
 */

#include "systick.h"

void systick_delay_ms(int delay)
{
	/* reload systick with number of cycles per millisecond*/
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/* clear systick current value register */
	SysTick->VAL = 0;

	/* select clock source and enable systick */
	SysTick->CTRL = CTRL_CLKSRC | CTRL_ENABLE;

	for (int i = 0; i < delay; i++)
	{
		/* wait until COUNTFLAG is set */
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0 )
		{
		}
	}

	SysTick->CTRL = 0;
}
