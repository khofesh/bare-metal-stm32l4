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
#include "stm32l4xx.h"

#define GPIOAEN				(1U<<0)
#define UART2EN				(1U<<17)

#define SYS_FREQ			4000000
#define APB1_CLK			SYS_FREQ

#define CR1_TE				(1U<<3)
#define CR1_UE				(1U<<0)

#define ISR_TXE				(1U<<7)

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t Baudrate);
void uart2_tx_init(USART_TypeDef *USARTx);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);
static void uart2_write(USART_TypeDef *USARTx, uint8_t ch);

int main(void)
{
	uart2_tx_init(USART2);

	while(1)
	{
		uart2_write(USART2, 'y');
	}
}

void uart2_tx_init(USART_TypeDef *USARTx)
{
	/****** configure the UART pin ******/
	/* enable clock access to GPIOA for AP2 as TX line */
	RCC->AHB2ENR |= GPIOAEN;

	/* set PA2 mode as alternate function mode */
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/* set the alternate function typed to UART */
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/****** configure the UART module ******/
	/* enable clock access to UART2 */
	RCC->APB1ENR1 |= UART2EN;

	/* configure baud rate */
	uart_set_baudrate(USARTx, APB1_CLK, 115200);

	/* configure transfer direction */
	USARTx->CR1 = CR1_TE;

	/* enable UART module */
	USARTx->CR1 |= CR1_UE;
}

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t Baudrate)
{
	return (PeriphClk + (Baudrate / 2)) / Baudrate;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate)
{
	USARTx->BRR = compute_uart_div(PeriphClk, Baudrate);
}

static void uart2_write(USART_TypeDef *USARTx, uint8_t ch)
{
	/* wait for transmit data register to be empty */
	while (!(USARTx->ISR & ISR_TXE))
	{
	}

	/* transmit value*/
	USARTx->TDR = (ch & 0xFF);

}


