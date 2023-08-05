/*
 * uart.h
 *
 *  Created on: Aug 4, 2023
 *      Author: fahmad
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32l4xx.h"

#define GPIOAEN				(1U<<0)
#define UART2EN				(1U<<17)

#define SYS_FREQ			4000000
#define APB1_CLK			SYS_FREQ

#define CR1_TE				(1U<<3)
#define CR1_UE				(1U<<0)
#define CR1_RE				(1U<<2)

#define ISR_TXE				(1U<<7)
#define ISR_RXNE			(1U<<5)

void uart2_tx_init(USART_TypeDef *USARTx);
void uart2_rxtx_init(USART_TypeDef *USARTx);
char uart2_read(USART_TypeDef *USARTx);

#endif /* UART_H_ */
