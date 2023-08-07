/*
 * systick.h
 *
 *  Created on: Aug 6, 2023
 *      Author: fahmad
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>
#include "stm32l4xx.h"

#define SYSTICK_LOAD_VAL 		4000
#define CTRL_ENABLE				(1U<<0)
#define CTRL_CLKSRC				(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)
#define CTRL_TICKINT			(1U<<1)
#define ONE_SEC_LOAD 			4000000

void systick_delay_ms(int delay);
void systick_1hz_interrupt();

#endif /* SYSTICK_H_ */
