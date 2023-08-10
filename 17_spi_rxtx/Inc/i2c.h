/*
 * i2c.h
 *
 *  Created on: Aug 8, 2023
 *      Author: fahmad
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "stm32l4xx.h"

#define 	GPIOBEN				(1U<<1)
#define 	I2C1EN				(1U<<21)

#define 	GPIOCEN				(1U<<2)
#define 	I2C3EN				(1U<<23)

#define		SLAVE_OWN_ADDRESS	0x5A
#define		I2C_TIMING			(0x00000E14)

void i2c1_slave_config(void);
void i2c3_master_config(void);
uint32_t i2c1_get_address_matchcode(void);

#endif /* I2C_H_ */
