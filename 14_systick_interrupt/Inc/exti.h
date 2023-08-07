/*
 * exti.h
 *
 *  Created on: Aug 6, 2023
 *      Author: fahmad
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stm32l4xx.h"

#define		GPIOCEN			(1U<<2)
#define		SYSCFGEN		(1U<<0)
#define		PIN13			(1U<<13)

void pc13_exti_init(void);

#endif /* EXTI_H_ */
