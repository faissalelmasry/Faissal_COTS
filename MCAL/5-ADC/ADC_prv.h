/*
 * ADC_prv.h
 *
 *  Created on: Aug 20, 2024
 *      Author: Acer
 */

#ifndef ADC_PRV_H_
#define ADC_PRV_H_

#define AREF      1u
#define AVCC      2u
#define RESERVED  3u
#define VOLT_2_65 4u

#define EIGHT_BITS  1u
#define TEN_BITS    2u


#define DIVISION_BY_2   1u
#define DIVISION_BY_4   2u
#define DIVISION_BY_8   3u
#define DIVISION_BY_16  4u
#define DIVISION_BY_32  5u
#define DIVISION_BY_64  6u
#define DIVISION_BY_128 7u

#define PRE_SCALAR_MASK 0b11111000
#define CHANNEL_MASK 	0b11100000

#endif /* ADC_PRV_H_ */
