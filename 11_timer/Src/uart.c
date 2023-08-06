/*
 * uart.c
 *
 *  Created on: Aug 4, 2023
 *      Author: fahmad
 */

#include "uart.h"

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t Baudrate);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);
static void uart2_write(USART_TypeDef *USARTx, uint8_t ch);

int __io_putchar(int ch)
{
	uart2_write(USART2, ch);

	return ch;
}

void uart2_rxtx_init(USART_TypeDef *USARTx)
{
	/****** configure the UART pin ******/
	/* enable clock access to GPIOA for PA2 and PA3 as TX line */
	RCC->AHB2ENR |= GPIOAEN;

	/* set PA2 mode as alternate function mode */
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/* set the alternate function typed to UART */
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/* set PA3 mode as alternate function mode */
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/* set the alternate function typed to UART */
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);

	/****** configure the UART module ******/
	/* enable clock access to UART2 */
	RCC->APB1ENR1 |= UART2EN;

	/* configure baud rate */
	uart_set_baudrate(USARTx, APB1_CLK, 115200);

	/* configure transfer direction */
	USARTx->CR1 = (CR1_TE | CR1_RE);

	/* enable UART module */
	USARTx->CR1 |= CR1_UE;
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

char uart2_read(USART_TypeDef *USARTx)
{
	/* wait for receive data register not empty flag (RXNE) */
	while (!(USARTx->ISR & ISR_RXNE))
	{
	}

	/* read content of receive data register */
	return USARTx->RDR;
}



