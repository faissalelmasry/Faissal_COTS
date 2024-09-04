/*
 * TIM_reg.c
 *
 *  Created on: Aug 26, 2024
 *      Author: Acer
 */

#ifndef TIM_REG_C_
#define TIM_REG_C_

#define TIMSK *((volatile uint8*)0x59)
#define TOEI 0u

#define TCCR0 *((volatile uint8*)0x53)
#define WGM01 3u
#define WGM00 6u

#define TCCNT0 *((volatile uint8*)0x52)

#endif /* TIM_REG_C_ */
