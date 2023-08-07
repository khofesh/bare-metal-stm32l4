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
	SysTick->LOAD = (SYSTICK_LOAD_VAL - 1); // count from 0

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

void systick_1hz_interrupt()
{
	/* reload systick with number of cycles per second*/
	SysTick->LOAD = (ONE_SEC_LOAD - 1);

	/* clear systick current value register */
	SysTick->VAL = 0;

	/* select clock source and enable systick */
	SysTick->CTRL = CTRL_CLKSRC | CTRL_ENABLE;

	/* enable systick interrupt */
	SysTick->CTRL |= CTRL_TICKINT;
}



