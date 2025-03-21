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
#include "adc.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"

#define PIN_5				(1U<<5)
#define LED_PIN				PIN_5

#define GPIOAEN				(1U<<0)

#define AF1_TIM				(1U<<20)

int main(void)
{
	/* 1. enable clock access to GPIOA */
	RCC->AHB2ENR |= GPIOAEN;

	/* 2. set PA5 as output pin */
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	GPIOA->AFR[0] |= AF1_TIM;

	tim2_output_compare();

	while(1)
	{

	}
}






