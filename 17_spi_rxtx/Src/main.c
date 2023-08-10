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
#include "exti.h"
#include "i2c.h"
#include "spi.h"

#define PIN_5				(1U<<5)
#define LED_PIN				PIN_5

#define GPIOAEN				(1U<<0)

#define AF1_TIM				(1U<<20)

static void spi1_tx_callback(void);
static void spi3_rx_callback(void);

uint8_t tx_buff[] = "hello from SPI";
uint8_t tx_size = sizeof(tx_buff);
volatile uint8_t tx_idx = 0;

uint8_t rx_buff[sizeof(tx_buff)];
uint8_t rx_size = sizeof(tx_buff);
volatile uint8_t rx_idx = 0;

/**
 * connect jumper wire
 * PB3 --> PC10
 * PB5 --> PC11
 */

int main(void)
{
	/* 1. enable clock access to GPIOA */
	RCC->AHB2ENR |= GPIOAEN;

	/* 2. set PA5 as output pin */
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	uart2_tx_init(USART2);

	spi1_config();
	spi3_config();
	spi3_activate();
	spi1_activate();

	while(1)
	{

	}
}

static void spi1_tx_callback(void)
{
	if (tx_idx < tx_size)
	{
		volatile uint8_t *spidr = ((volatile uint8_t *)&SPI1->DR);
		*spidr = tx_buff[tx_idx++];
	}
}

static void spi3_rx_callback(void)
{
	rx_buff[rx_idx++] = SPI3->DR;
}

void SPI1_IRQHandler(void)
{
	/* check if TXE is set */
	if ((SPI1->SR & (1U<<1)))
	{
		/* do something */
		spi1_tx_callback();
	}
}

void SPI3_IRQHandler(void)
{
	/* check if RXNE is set */
	if ((SPI3->SR & (1U<<0)))
	{
		/* do something */
		spi3_rx_callback();
	}
}

