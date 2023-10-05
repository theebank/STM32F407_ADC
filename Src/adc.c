/*
 * adc.c
 *
 *  Created on: Oct 4, 2023
 *      Author: TKuma
 */
#include "stm32f4xx.h"
#include "adc.h"
#include <stdio.h>

#define ADC1EN				(0x1U<<8)
#define GPIOAEN				(0x1U<<0)
#define ADC_CH1				(0x1U<<0)
#define ADC_SEQ_LEN_1		0x00
#define CR2_ADC_ON			(0x1U<<0)
#define CR2_ADC_START_CON	(0x1U<<30)
#define SR_EOC				(0x1U<<1)
#define CR2_CONT			(0x1U<<1)


void pa1_adc_init(){

//	configure adc gpio pin
//	enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAEN;
//	set mode of pa1 to analog mode
	GPIOA->MODER |= (0x1U<<2);
	GPIOA->MODER |= (0x1U<<3);

//	configure adc module
//	enable clock access to adc
	RCC->APB2ENR |= ADC1EN;

//	configure adc parameters
//	conversion sequence start
	ADC1->SQR1 = ADC_CH1;
//	conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;
//	enable adc module
	ADC1->CR2 |= CR2_ADC_ON;
}

void start_conversion(){
	//enable continuous conversion
	ADC1->CR2 |= CR2_CONT;
	//start adc conversion
	ADC1->CR2 |= CR2_ADC_START_CON;
}

uint32_t adc_read(){
	//wait for conversion to be complete
	while(!(ADC1->SR & SR_EOC)){}
//	read converted message
	return(ADC1->DR);

}

