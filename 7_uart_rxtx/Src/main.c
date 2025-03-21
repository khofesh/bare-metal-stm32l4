/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include "stm32l4xx.h"
#include "uart.h"

#define GPIOAEN				(1U<<0)
#define GPIOCEN				(1U<<2)
#define GPIOA_5				(1U<<5)
#define LED_PIN				GPIOA_5

char key;

int main(void)
{
	/* enable clock access to GPIOA */
	RCC->AHB2ENR |= GPIOAEN;

	uart2_rxtx_init(USART2);

	/* set PA5 as output pin */
	GPIOA->MODER |= (1U<<10); // set bit 10 to 1
	GPIOA->MODER &= ~(1U<<11); // set bit 11 to 0

	while(1)
	{
		key = uart2_read(USART2);

		if (key == '1')
		{
			GPIOA->ODR |= LED_PIN;
		}
		else
		{
			GPIOA->ODR &= ~(LED_PIN);
		}
	}
}






