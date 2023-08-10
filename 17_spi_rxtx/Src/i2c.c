/*
 * i2c.c
 *
 *  Created on: Aug 8, 2023
 *      Author: fahmad
 */

#include "i2c.h"

static void i2c1_set_own_address_1(uint32_t ownAddress1, uint32_t ownAddrSize);

void i2c1_slave_config(void)
{
	/***** SCL *****/
	/* enable clock access to GPIOB */
	RCC->AHB2ENR |= GPIOBEN;

	/* set PB8 (SCL line) mode to alternate function */
	GPIOB->MODER &= ~(1U<<16);
	GPIOB->MODER |= (1U<<17);

	/* set alternate function type to I2C1 (AF4) */
	GPIOB->AFR[1] &= ~(1U<<0);
	GPIOB->AFR[1] &= ~(1U<<1);
	GPIOB->AFR[1] |= (1U<<2);
	GPIOB->AFR[1] &= ~(1U<<3);

	/* set PB8 as open-drain */
	GPIOB->OTYPER |= (1U<<8);

	/* enable pull-up */
	GPIOB->PUPDR |= (1U<<16);
	GPIOB->PUPDR &= ~(1U<<17);

	/***** SDA *****/
	/* set PB9 (SDA line) mode to alternate function */
	GPIOB->MODER &= ~(1U<<18);
	GPIOB->MODER |= (1U<<19);

	/* set alternate function type to I2C1 (AF4) */
	GPIOB->AFR[1] &= ~(1U<<4);
	GPIOB->AFR[1] &= ~(1U<<5);
	GPIOB->AFR[1] |= (1U<<6);
	GPIOB->AFR[1] &= ~(1U<<7);

	/* set PB9 as open-drain */
	GPIOB->OTYPER |= (1U<<9);

	/* enable pull-up */
	GPIOB->PUPDR |= (1U<<18);
	GPIOB->PUPDR &= ~(1U<<19);

	/***** configure I2C parameters *****/
	/* enable clock access to I2C module */
	RCC->APB1ENR1 |= I2C1EN;

	/* enable I2C interrupt in NVIC */
	NVIC_EnableIRQ(I2C1_EV_IRQn);

	/* disable I2C1 */
	I2C1->CR1 &= ~(1U<<0);

	/* set device address */
	i2c1_set_own_address_1(SLAVE_OWN_ADDRESS, 0);

	/* enable own address 1 */
	I2C1->OAR1 |= (1U<<15);

	/* enable I2C1 */
	I2C1->CR1 |= (1U<<0);

	/* enable ADDR interrupt */
	I2C1->CR1 |= (1U<<3);

	/* enable NACK interrupt */
	I2C1->CR1 |= (1U<<4);

	/* enable STOP interrupt */
	I2C1->CR1 |= (1U<<5);
}

void i2c3_master_config(void)
{
	/***** SCL *****/
	/* enable clock access to GPIOC */
	RCC->AHB2ENR |= GPIOCEN;

	/* set PC0 (SCL line) mode to alternate function */
	GPIOC->MODER &= ~(1U<<0);
	GPIOC->MODER |= (1U<<1);

	/* set alternate function type to I2C3 (AF4) */
	GPIOC->AFR[0] &= ~(1U<<0);
	GPIOC->AFR[0] &= ~(1U<<1);
	GPIOC->AFR[0] |= (1U<<2);
	GPIOC->AFR[0] &= ~(1U<<3);

	/* set PC0 as open-drain */
	GPIOC->OTYPER |= (1U<<0);

	/* enable pull-up */
	GPIOC->PUPDR |= (1U<<0);
	GPIOC->PUPDR &= ~(1U<<1);

	/***** SDA *****/
	/* set PC1 (SDA line) mode to alternate function */
	GPIOC->MODER &= ~(1U<<2);
	GPIOC->MODER |= (1U<<3);

	/* set alternate function type to I2C3 (AF4) */
	GPIOC->AFR[0] &= ~(1U<<4);
	GPIOC->AFR[0] &= ~(1U<<5);
	GPIOC->AFR[0] |= (1U<<6);
	GPIOC->AFR[0] &= ~(1U<<7);

	/* set PC1 as open-drain */
	GPIOC->OTYPER |= (1U<<1);

	/* enable pull-up */
	GPIOC->PUPDR |= (1U<<2);
	GPIOC->PUPDR &= ~(1U<<3);

	/***** configure I2C parameters *****/
	/* enable clock access to I2C module */
	RCC->APB1ENR1 |= I2C3EN;

	/* disable I2C3 */
	I2C3->CR1 &= ~(1U<<0);

	/* configure I2C timing */
	I2C3->TIMINGR = I2C_TIMING;

	/* enable I2C3 */
	I2C3->CR1 |= (1U<<0);
}

static void i2c1_set_own_address_1(uint32_t ownAddress1, uint32_t ownAddrSize)
{
	MODIFY_REG(I2C1->OAR1, I2C_OAR1_OA1 | I2C_OAR1_OA1MODE, ownAddress1 | ownAddrSize);
}

uint32_t i2c1_get_address_matchcode(void)
{
	return (uint32_t)(READ_BIT(I2C1->ISR, I2C_ISR_ADDCODE) >> I2C_ISR_ADDCODE_Pos << 1);
}

