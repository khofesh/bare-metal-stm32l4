/*
 * spi.h
 *
 *  Created on: Aug 9, 2023
 *      Author: fahmad
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32l4xx.h"

#define GPIOBEN		(1U<<1)
#define SPI1EN		(1U<<12)
#define GPIOCEN 	(1U<<2)
#define SPI3EN		(1U<<15)

void spi1_config(void);
void spi3_config(void);
void spi1_activate(void);
void spi3_activate(void);

#endif /* SPI_H_ */
