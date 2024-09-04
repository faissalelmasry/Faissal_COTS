/*
 * ADC_prog.c
 *
 *  Created on: Aug 20, 2024
 *      Author: Acer
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_interface.h"
static uint16* ADC_pu16ConversionResult=NULL;
static void (*ADC_pu16NotificationFunc)(void)=NULL;
static uint8 ADC_u8BusyFlag=IDLE;
void ADC_voidInit(void)
{
#if ADC_VOLTAGE_REF==AREF
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_VOLTAGE_REF==AVCC
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_VOLTAGE_REF==RESERVED
	CLR_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_VOLTAGE_REF==VOLT_2_65
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#else
#error Wrong ADC_VOLTAGE_REF configuration option
#endif

#if ADC_RESOLUTION==EIGHT_BITS
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_RESOLUTION==TEN_BITS
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error Wrong ADC_RESOLUTION configuration option
#endif

	ADCSRA&=PRE_SCALAR_MASK;
	ADCSRA|=PRE_SCALAR;

#if AUTO_TRIGGER==ENABLED
	SET_BIT(ADCSRA,ADCSRA_ADATE);
#elif AUTO_TRIGGER==DISABLED
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
#else
#error Wrong AUTO_TRIGGER configuration option
#endif

#if ADC_INTERRUPT==ENABLED
	SET_BIT(ADCSRA,ADCSRA_ADIE);
#elif ADC_INTERRUPT==DISABLED
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
#else
#error Wrong ADC_INTERRUPT configuration option
#endif

#if ADEN==ENABLED
	SET_BIT(ADCSRA,ADCSRA_ADEN);
#elif ADEN==DISABLED
	CLR_BIT(ADCSRA,ADCSRA_ADEN);
#else
#error Wrong ADEN configuration option
#endif
}

uint8 ADC_u16StartConversionSynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result)
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_pu16Result!=NULL)
	{
	if(ADC_u8BusyFlag==IDLE)
	{
	ADC_u8BusyFlag=BUSY;
	uint32 Local_u32TimeoutCounter=0u;
	ADMUX&=CHANNEL_MASK;
	ADMUX|=Copy_u8Channel;
	SET_BIT(ADCSRA,ADCSRA_ADSC);
	while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0)&&(Local_u32TimeoutCounter<ADC_TIMEOUT))
	{
		Local_u32TimeoutCounter++;
	}
	if(Local_u32TimeoutCounter>=ADC_TIMEOUT)Local_u8ErrorState=TIMEOUT_ERR;
	else
	{
		SET_BIT(ADCSRA,ADCSRA_ADIF);
	#if ADC_RESOLUTION==EIGHT_BITS
		*Copy_pu16Result= ADCH;
	#elif ADC_RESOLUTION==TEN_BITS
		*Copy_pu16Result=ADC;
	#else
	#error Wrong ADC_RESOLUTION configuration option
	#endif
	ADC_u8BusyFlag=IDLE;
	}
	}
	else
	{
		Local_u8ErrorState=BUSY_STATE_ERR;
	}
	}
	else Local_u8ErrorState=NULL_PTR_ERR;
	return Local_u8ErrorState;
}

sint32 ADC_s32Mapping(Mapping_t* Object )
{
	sint32 Local_s32OutputValue=(Object->MaxOutput)-((((Object->MaxInput)-(Object->InputValue))*(Object->MaxOutput))/(Object->MaxInput));
	return Local_s32OutputValue;
}

uint8 ADC_u16StartConversionAsynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result,void (*Copy_pvoidNotificationFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
	if((ADC_pu16ConversionResult!=NULL)&&(ADC_pu16NotificationFunc!=NULL))
	{
		if(ADC_u8BusyFlag==IDLE)
		{
		ADC_u8BusyFlag=BUSY;
		ADC_pu16ConversionResult=Copy_pu16Result;
		ADC_pu16NotificationFunc=Copy_pvoidNotificationFunc;
		ADMUX&=CHANNEL_MASK;
		ADMUX|=Copy_u8Channel;
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState=BUSY_STATE_ERR;
		}

	}
	else Local_u8ErrorState=NULL_PTR_ERR;
	return Local_u8ErrorState;

}

void __vector_16(void)  __attribute__((signal));
void __vector_16(void)
{
	if(ADC_pu16ConversionResult!=NULL)
	{
#if ADC_RESOLUTION==EIGHT_BITS
	*ADC_pu16ConversionResult= ADCH;
#elif ADC_RESOLUTION==TEN_BITS
	*ADC_pu16ConversionResult=ADC;
#endif
	}
	 CLR_BIT(ADCSRA,ADCSRA_ADIE);
	 ADC_u8BusyFlag=IDLE;
	 if(ADC_pu16ConversionResult!=NULL)
	 	{
		 ADC_pu16NotificationFunc();
	 	}
}
