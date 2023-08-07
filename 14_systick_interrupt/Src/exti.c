/*
 * exti.c
 *
 *  Created on: Aug 6, 2023
 *      Author: fahmad
 */

#include "exti.h"


void pc13_exti_init(void)
{
	/* enable clock access to GPIOC */
	RCC->AHB2ENR |= GPIOCEN;

	/* enable clock access to SYSCFG*/
	RCC->APB2ENR |= SYSCFGEN;

	/* set PC13 as input pin */
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	/* clear port selection for EXTI13 */
	SYSCFG->EXTICR[3] &= ~(1U<<4);
	SYSCFG->EXTICR[3] &= ~(1U<<5);
	SYSCFG->EXTICR[3] &= ~(1U<<6);
	SYSCFG->EXTICR[3] &= ~(1U<<7);

	/* select PORT C for EXTI13 */
	SYSCFG->EXTICR[3] |= (1U<<5);

	/* unmask EXTI13 */
	EXTI->IMR1 |= (1U<<13);

	/* select falling edge trigger */
	EXTI->FTSR1 |= (1U<<13);

	/* enable EXTI line in NVIC */
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}
