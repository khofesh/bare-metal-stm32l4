/*
 * adc.c
 *
 *  Created on: Aug 5, 2023
 *      Author: fahmad
 */

#include "adc.h"

void pa4_adc1_init(void)
{
	/***** configure ADC GPIO pin *****/
	/* enable clock access to GPIOA */
	RCC->AHB2ENR |= GPIOAEN;

	/* set PA4 mode to analog */
	GPIOA->MODER |= (1U<<8);
	GPIOA->MODER |= (1U<<9);

	/* connect GPIO analog switch to ADC input */
	GPIOA->ASCR |= ASCR_ASC4;

	/***** configure ADC module *****/
	/* enable clock access to ADC module */
	RCC->AHB2ENR |= ADCEN;

	/* set ADC common clock */
	ADC123_COMMON->CCR &= ~(1U<<16);
	ADC123_COMMON->CCR |= (1U<<17);

	/* set continuous conversion */
	ADC1->CFGR |= CFGR_CONT;

	/* set sequencer length */
	ADC1->SQR1 = SEQ_LEN_1;

	/* set ADC channel and rank */
	ADC1->SQR1 |= (1U<<6);
	ADC1->SQR1 |= (1U<<9); // 0b 0 1001

	/* disable ADC deep power down */
	ADC1->CR &= ~(1U<<29);

	/* enable ADC internal regulator */
	ADC1->CR |= (1U<<28);

	/* start ADC calibration */
	ADC1->CR |= (1U<<31);

	/* enable ADC */
	ADC1->CR |= (1U<<0);
}

void start_conversion(void)
{
	ADC1->CR |= (1U<<2);
}

uint32_t adc_read(void)
{
	/* wait for end-of-conversion flag */
	while (!(ADC1->ISR & ISR_EOC))
	{
	}

	/* clear EOC flag */
	ADC1->ISR |= ISR_EOC;

	/* read results */
	return (ADC1->DR);
}
