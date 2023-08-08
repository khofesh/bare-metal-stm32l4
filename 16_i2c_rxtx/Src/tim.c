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

void tim1_1hz_interrupt(void)
{
	RCC->APB2ENR |= TIM1EN;
	TIM1->PSC = 400 - 1;
	TIM1->ARR = 10000 - 1;
	TIM1->CNT = 0;

	TIM1->CR1 = CR1_CEN;

	/* enable timer update interrupt */
	TIM1->DIER |= DIER_UIE;

	/* enable interrupt in NVIC */
	NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
}

void tim2_output_compare(void)
{
	RCC->APB1ENR1 |= TIM2EN;
	TIM2->PSC = 400 - 1;
	TIM2->ARR = 10000 - 1;

	/* set output compare  toggle mode */
	TIM2->CCMR1 |= (1U<<4);
	TIM2->CCMR1 |= (1U<<5);

	/* set match value */
	TIM2->CCR1 = 0;

	/* enable CH1 compare mode */
	TIM2->CCER |= (1U<<0);

	/* clear counter */
	TIM2->CNT = 0;

	/* enable TIM2 */
	TIM2->CR1 = (1U<<0);
}
