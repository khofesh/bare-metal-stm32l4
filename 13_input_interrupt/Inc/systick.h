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

void systick_delay_ms(int delay);

#endif /* SYSTICK_H_ */
