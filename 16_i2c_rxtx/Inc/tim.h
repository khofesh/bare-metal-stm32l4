/*
 * time.h
 *
 *  Created on: Aug 6, 2023
 *      Author: fahmad
 */

#ifndef TIM_H_
#define TIM_H_

#include "stm32l4xx.h"

#define		TIM1EN		(1U<<11)
#define		TIM2EN		(1U<<0)

#define		CR1_CEN		(1U<<0)

#define 	SR_UIF		(1U<<0)
#define 	DIER_UIE 	(1u<<0)

void tim1_1hz_init(void);
void tim2_output_compare(void);
void tim1_1hz_interrupt(void);

#endif /* TIM_H_ */
