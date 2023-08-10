/*
 * spi.c
 *
 *  Created on: Aug 9, 2023
 *      Author: fahmad
 */

#include "spi.h"


void spi1_config(void)
{
	/* enable the peripheral clock of GPIOB */
	RCC->AHB2ENR |= GPIOBEN;

	/***** SCK *****/
	/* configure SCK pin PB3 */
	GPIOB->MODER &= ~(1U<<6);
	GPIOB->MODER |= (1U<<7);

	/* set alternate function type to AF5 */
	GPIOB->AFR[0] |= (1U<<12);
	GPIOB->AFR[0] &= ~(1U<<13);
	GPIOB->AFR[0] |= (1U<<14);
	GPIOB->AFR[0] &= ~(1U<<15);

	/* set speed of the pin to very high */
	GPIOB->OSPEEDR |= (1U<<6);
	GPIOB->OSPEEDR |= (1U<<7);

	/* enable pull-down resistor */
	GPIOB->PUPDR &= ~(1U<<6);
	GPIOB->PUPDR |= (1U<<7);

	/***** MOSI *****/
	/* configure MOSI pin PB5 */
	GPIOB->MODER &= ~(1U<<10);
	GPIOB->MODER |= (1U<<11);

	/* set alternate function type to SPI1 */
	GPIOB->AFR[0] |= (1U<<20);
	GPIOB->AFR[0] &= ~(1U<<21);
	GPIOB->AFR[0] |= (1U<<22);
	GPIOB->AFR[0] &= ~(1U<<23);

	/* set speed of the pin to very high */
	GPIOB->OSPEEDR |= (1U<<10);
	GPIOB->OSPEEDR |= (1U<<11);

	/* enable pull-down resistor */
	GPIOB->PUPDR &= ~(1U<<10);
	GPIOB->PUPDR |= (1U<<11);

	/* enable SPI1_IRQn */
	NVIC_EnableIRQ(SPI1_IRQn);

	/* enable the peripheral clock of SPI1 */
	RCC->APB2ENR |= SPI1EN;

	/* set clock to fPCLK/256 */
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 |= (1U<<4);
	SPI1->CR1 |= (1U<<5);

	/* select TX only */
	SPI1->CR1 |= (1U<<14);

	/* select 1-line bidirectional data mode selected */
	SPI1->CR1 |= (1U<<15);

	/* set CPOL to 1 and CPHA to 1 */
	SPI1->CR1 |= (1U<<0);
	SPI1->CR1 |= (1U<<1);

	/* set data width to 8 bit */
	SPI1->CR2 |= (1U<<8);
	SPI1->CR2 |= (1U<<9);
	SPI1->CR2 |= (1U<<10);
	SPI1->CR2 &= ~(1U<<11);

	/**
	 * select software slave management by
	 * setting SSM = 1 and SSI=1
	 */
	SPI1->CR1 |= (1<<8);
	SPI1->CR1 |= (1<<9);

	/* set FIFO reception threshold */
	SPI1->CR2 |= (1U<<12);

	/* set mode to MASTER */
	SPI1->CR1 |= (1U<<2);

	/* enable TXE interrupt */
	SPI1->CR2 |= (1U<<7);
}

void spi3_config(void)
{
	/* Enable the peripheral clock of GPIOC */
	RCC->AHB2ENR |= GPIOCEN;

	/***** SCK *****/
	/* Configure SCK Pin PC10 */
	GPIOC->MODER &= ~(1U<<20);
	GPIOC->MODER |= (1U<<21);

	/*Set alternate function type to SPI3*/
	GPIOC->AFR[1] &= ~(1U<<8);
	GPIOC->AFR[1] |= (1U<<9);
	GPIOC->AFR[1] |= (1U<<10);
	GPIOC->AFR[1] &= ~(1U<<11);

	/*Set pin speed very high*/
	GPIOC->OSPEEDR |= (1U<<20);
	GPIOC->OSPEEDR |= (1U<<21);

	/*Enable pull-down resistor*/
	GPIOC->PUPDR &= ~(1U<<20);
	GPIOC->PUPDR |= (1U<<21);

	/***** MISO *****/
	/*Configure MISO Pin PC11*/
	GPIOC->MODER &= ~(1U<<22);
	GPIOC->MODER |= (1U<<23);

	/*Set alternate function type to SPI3*/
	GPIOC->AFR[1] &= ~(1U<<12);
	GPIOC->AFR[1] |= (1U<<13);
	GPIOC->AFR[1] |= (1U<<14);
	GPIOC->AFR[1] &= ~(1U<<15);

	/*Set pin speed very high*/
	GPIOC->OSPEEDR |= (1U<<22);
	GPIOC->OSPEEDR |= (1U<<23);

	/*Enable pull-down resistor*/
	GPIOC->PUPDR &= ~(1U<<22);
	GPIOC->PUPDR |= (1U<<23);

	NVIC_EnableIRQ(SPI3_IRQn);

	/*Enable clock access to SPI3*/
	RCC->APB1ENR1 |= SPI3EN;

  	/*Set clock to fPCLK/256*/
	SPI3->CR1 |= (1U<<3);
	SPI3->CR1 |= (1U<<4);
	SPI3->CR1 |= (1U<<5);

	/*Select 1-line bidirectional data mode selected*/
	SPI3->CR1 |= (1U<<15);

	/*Set CPOL to 1 and CPHA to 1*/
	SPI3->CR1 |= (1U<<0);
	SPI3->CR1 |= (1U<<1);

	/*Set data width to 8 bit*/
	SPI3->CR2 |= (1U<<8);
	SPI3->CR2 |= (1U<<9);
	SPI3->CR2 |= (1U<<10);
	SPI3->CR2 &= ~(1U<<11);

	/*Enable software slave management*/
	SPI3->CR1 |= (1U<<9);

	/*Enable Slave Select Output*/
	SPI3->CR2 |= (1U<<2);

	/*Set FIFO reception threshold*/
	SPI3->CR2 |= (1U<<12);

	/* Enable RXNE  Interrupt */
	SPI3->CR2 |= (1U<<6);
}

void spi1_activate(void)
{
	/* enable SPI1 */
	SPI1->CR1 |= (1U<<6);
}

void spi3_activate(void)
{
	/* enable SPI3 */
	SPI3->CR1 |= (1U<<6);
}

