/*
 * EXTI_cfg.h
 *
 *  Created on: Aug 16, 2024
 *      Author: Acer
 */

#ifndef EXTI_CFG_H_
#define EXTI_CFG_H_

/*
 *options:1-EXTI_u8RISING_EDGE
 *		  2-EXTI_u8FALLING_EDGE
 *		  3- EXTI_u8LOW_LEVEL
 *		  4-EXTI_u8LOGICAL_CHANGE
 */
#define INT0_SENSE_CTRL EXTI_u8FALLING_EDGE

/*
 *options:1-ENABLED
 *		  2-DISABLED
 */
#define INT0_INITIAL_STATE ENABLED

/*
 *options:1-EXTI_u8RISING_EDGE
 *		  2-EXTI_u8FALLING_EDGE
 *		  3- EXTI_u8LOW_LEVEL
 *		  4-EXTI_u8LOGICAL_CHANGE
 */
#define INT1_SENSE_CTRL EXTI_u8FALLING_EDGE

/*
 *options:1-ENABLED
 *		  2-DISABLED
 */
#define INT1_INITIAL_STATE ENABLED

/*
 *options:1-EXTI_u8RISING_EDGE
 *		  2-EXTI_u8FALLING_EDGE
 */
#define INT2_SENSE_CTRL EXTI_u8FALLING_EDGE

/*
 *options:1-ENABLED
 *		  2-DISABLED
 */
#define INT2_INITIAL_STATE ENABLED

#endif /* EXTI_CFG_H_ */
