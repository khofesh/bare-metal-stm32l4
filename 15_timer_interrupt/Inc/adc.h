/*
 * adc.h
 *
 *  Created on: Aug 5, 2023
 *      Author: fahmad
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32l4xx.h"

#define GPIOAEN				(1U<<0)
#define ASCR_ASC4			(1U<<4)
#define ADCEN				(1U<<13)
#define CFGR_CONT			(1U<<13)
#define SEQ_LEN_1			0
#define ISR_EOC				(1U<<2)

void pa4_adc1_init(void);
void start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
