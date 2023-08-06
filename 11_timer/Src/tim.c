/*
 * time.c
 *
 *  Created on: Aug 6, 2023
 *      Author: fahmad
 */

#include <tim.h>

void tim1_1hz_init(void)
{
	RCC->APB2ENR |= TIM1EN;
	TIM1->PSC = 400 - 1;
	TIM1->ARR = 10000 - 1;
	TIM1->CNT = 0;

	TIM1->CR1 = CR1_CEN;
}
