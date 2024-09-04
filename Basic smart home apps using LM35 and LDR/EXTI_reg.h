/*
 * EXTI_reg.h
 *
 *  Created on: Aug 16, 2024
 *      Author: Acer
 */

#ifndef EXTI_REG_H_
#define EXTI_REG_H_

#define GICR  *((volatile uint8*) 0x5B)
#define GICR_INT1  					 7u
#define GICR_INT0  					 6u
#define GICR_INT2  					 5u

#define MCUCR *((volatile uint8*) 0x55)
#define MCUCR_ISC00 				 0u
#define MCUCR_ISC01 				 1u
#define MCUCR_ISC10 				 2u
#define MCUCR_ISC11 				 3u

#define MCUSCR *((volatile uint8*) 0x54)
#define MCUSCR_ISC2 				 6u

#endif /* EXTI_REG_H_ */
