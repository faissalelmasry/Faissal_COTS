/*
 * ADC_cfg.h
 *
 *  Created on: Aug 20, 2024
 *      Author: Acer
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/**
 * options:  1-AREF
			 2-AVCC
			 3-RESERVED
			 4-VOLT_2_65
 */
#define ADC_VOLTAGE_REF    AVCC

/**
 * options:  1-EIGHT_BITS
			 2-TEN_BITS
 */
#define ADC_RESOLUTION EIGHT_BITS

/**
 * options:  1-ADC0
			 2-ADC1
			 3-ADC2
			 4-ADC3
			 5-ADC4
			 6-ADC5
			 7-ADC6
			 8-ADC7
 */

/**
 * options:  1-ENABLED
			 2-DISABLED
 */
#define AUTO_TRIGGER  ENABLED

/**
 * options:  1-ENABLED
			 2-DISABLED
 */
#define ADC_INTERRUPT  DISABLED

#define CHANNEL ADC0

/**
 * options:  1-ENABLED
			 2-DISABLED
 */
#define ADEN  ENABLED

/**
 * options:  1-ENABLED
			 2-DISABLED
 */
#define ADIF DISABLED

/**
 * options:  1-ENABLED
			 2-DISABLED
 */
#define ADIE DISABLED

/**
 * options:  1-DIVISION_BY_2
			 2-DIVISION_BY_4
			 3-DIVISION_BY_8
			 4-DIVISION_BY_16
			 5-DIVISION_BY_32
			 6-DIVISION_BY_64
			 7-DIVISION_BY_128
 */
#define PRE_SCALAR DIVISION_BY_128

#define ADC_TIMEOUT     50000u

#endif /* ADC_CFG_H_ */
