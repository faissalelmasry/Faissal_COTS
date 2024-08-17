/*
 * EXTI_interface.h
 *
 *  Created on: Aug 16, 2024
 *      Author: Acer
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define EXTI_u8INT0 1u
#define EXTI_u8INT1 2u
#define EXTI_u8INT2 3u

#define EXTI_u8RISING_EDGE    1u
#define EXTI_u8FALLING_EDGE   2u
#define EXTI_u8LOW_LEVEL      3u
#define EXTI_u8LOGICAL_CHANGE 4u

void EXTI_voidInit(void);
uint8 EXTI_u8SetSenseControl(uint8 Copy_u8Int,uint8 Copy_u8SenseControl);
uint8 EXTI_u8IntEnable(uint8 Copy_u8Int);
uint8 EXTI_u8IntDisable(uint8 Copy_u8Int);

#endif /* EXTI_INTERFACE_H_ */
