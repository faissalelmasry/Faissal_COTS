/*
 * EXTI_prog.c
 *
 *  Created on: Aug 16, 2024
 *      Author: Acer
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "defines.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"
#include "EXTI_reg.h"
#include "EXTI_cfg.h"
#include "EXTI_prv.h"

static void (*EXTI_pfIntFuncPtr[3]) (void)={NULL};

void EXTI_voidInit(void)
{
#if INT0_SENSE_CTRL==EXTI_u8FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CTRL==EXTI_u8RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CTRL==EXTI_u8LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CTRL==EXTI_u8LOGICAL_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#else
#error Wrong INT0_SENSE_CTRL configuration option
#endif
#if INT0_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT0);
#elif INT0_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT0);
#else
#error Wrong INT0_INITIAL_STATE configuration option
#endif

#if INT1_SENSE_CTRL==EXTI_u8FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE_CTRL==EXTI_u8RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE_CTRL==EXTI_u8LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif INT1_SENSE_CTRL==EXTI_u8LOGICAL_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#else
#error Wrong INT1_SENSE_CTRL configuration option
#endif
#if INT1_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT1);
#elif INT1_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT1);
#else
#error Wrong INT1_INITIAL_STATE configuration option
#endif

#if INT2_SENSE_CTRL==EXTI_u8FALLING_EDGE
	CLR_BIT(MCUSCR,MCUSCR_ISC2);
#elif INT2_SENSE_CTRL==EXTI_u8RISING_EDGE
	SET_BIT(MCUSCR,MCUSCR_ISC2);
#else
#error Wrong INT2_SENSE_CTRL configuration option
#endif
#if INT2_INITIAL_STATE==ENABLED
	SET_BIT(GICR,GICR_INT2);
#elif INT2_INITIAL_STATE==DISABLED
	CLR_BIT(GICR,GICR_INT2);
#else
#error Wrong INT2_INITIAL_STATE configuration option
#endif


}

uint8 EXTI_u8SetSenseControl(uint8 Copy_u8Int,uint8 Copy_u8SenseControl)
{
	uint8 Local_u8ErrorState=OK;
	switch(Copy_u8Int)
	{
	case EXTI_u8INT0:
		switch(Copy_u8SenseControl)
		{
		case EXTI_u8RISING_EDGE:SET_BIT(MCUCR,MCUCR_ISC00);SET_BIT(MCUCR,MCUCR_ISC01);break;
		case EXTI_u8FALLING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC00);SET_BIT(MCUCR,MCUCR_ISC01);break;
		case EXTI_u8LOW_LEVEL:CLR_BIT(MCUCR,MCUCR_ISC00);CLR_BIT(MCUCR,MCUCR_ISC01);break;
		case EXTI_u8LOGICAL_CHANGE:SET_BIT(MCUCR,MCUCR_ISC00);CLR_BIT(MCUCR,MCUCR_ISC01);break;
		default:Local_u8ErrorState=NOK;break;
		}
		break;
	case EXTI_u8INT1:
		switch(Copy_u8SenseControl)
		{
		case EXTI_u8RISING_EDGE:SET_BIT(MCUCR,MCUCR_ISC10);SET_BIT(MCUCR,MCUCR_ISC11);break;
		case EXTI_u8FALLING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC10);SET_BIT(MCUCR,MCUCR_ISC11);break;
		case EXTI_u8LOW_LEVEL:CLR_BIT(MCUCR,MCUCR_ISC10);CLR_BIT(MCUCR,MCUCR_ISC11);break;
		case EXTI_u8LOGICAL_CHANGE:SET_BIT(MCUCR,MCUCR_ISC10);CLR_BIT(MCUCR,MCUCR_ISC11);break;
		default:Local_u8ErrorState=NOK;break;
		}
		break;
	case EXTI_u8INT2:
		switch(Copy_u8SenseControl)
		{
		case EXTI_u8RISING_EDGE:SET_BIT(MCUSCR,MCUSCR_ISC2);break;
		case EXTI_u8FALLING_EDGE:CLR_BIT(MCUSCR,MCUSCR_ISC2);break;
		default:Local_u8ErrorState=NOK;break;
		}
		break;
	default  :
		Local_u8ErrorState=NOK;break;
	}

	return Local_u8ErrorState;
}

uint8 EXTI_u8IntEnable(uint8 Copy_u8Int)
{
	uint8 Local_u8ErrorState=OK;
	switch(Copy_u8Int)
	{
	case EXTI_u8INT0:SET_BIT(GICR,GICR_INT0);break;
	case EXTI_u8INT1:SET_BIT(GICR,GICR_INT1);break;
	case EXTI_u8INT2:SET_BIT(GICR,GICR_INT2);break;
	default  : Local_u8ErrorState=NOK;break;
	}

	return Local_u8ErrorState;
}

uint8 EXTI_u8IntDisable(uint8 Copy_u8Int)
{
	uint8 Local_u8ErrorState=OK;
	switch(Copy_u8Int)
	{
	case EXTI_u8INT0:CLR_BIT(GICR,GICR_INT0);break;
	case EXTI_u8INT1:CLR_BIT(GICR,GICR_INT1);break;
	case EXTI_u8INT2:CLR_BIT(GICR,GICR_INT2);break;
	default  : Local_u8ErrorState=NOK;break;
	}

	return Local_u8ErrorState;
}
uint8 EXTI_u8SetCallBack(uint8 Copy_u8Int,void (*Copy_pfFuncPtr)(void))
{
	uint8 Local_u8StateError=OK;
	if(Copy_pfFuncPtr!=NULL)
	{
		if(Copy_u8Int<=EXTI_u8INT2)
		{
			EXTI_pfIntFuncPtr[Copy_u8Int]=Copy_pfFuncPtr;
		}
		else Local_u8StateError=NOK;
	}
	else Local_u8StateError=NULL_PTR_ERR;
	return Local_u8StateError;
}
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if(EXTI_pfIntFuncPtr[EXTI_u8INT0]!=NULL)
	{
		EXTI_pfIntFuncPtr[EXTI_u8INT0]();
	}
}
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if(EXTI_pfIntFuncPtr[EXTI_u8INT1]!=NULL)
	{
		EXTI_pfIntFuncPtr[EXTI_u8INT1]();
	}

}
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if(EXTI_pfIntFuncPtr[EXTI_u8INT2]!=NULL)
	{
		EXTI_pfIntFuncPtr[EXTI_u8INT2]();
	}

}

