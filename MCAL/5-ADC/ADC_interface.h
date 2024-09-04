/*
 * ADC_interface.h
 *
 *  Created on: Aug 20, 2024
 *      Author: Acer
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_SINGLE_ENDED_CH0      0u
#define ADC_SINGLE_ENDED_CH1      1u
#define ADC_SINGLE_ENDED_CH2      2u
#define ADC_SINGLE_ENDED_CH3      3u
#define	ADC_SINGLE_ENDED_CH4      4u
#define	ADC_SINGLE_ENDED_CH5      5u
#define	ADC_SINGLE_ENDED_CH6      6u
#define	ADC_SINGLE_ENDED_CH7	  7u

typedef struct
{
	sint32 MinInput;
	sint32 MaxInput;
	sint32 MinOutput;
	sint32 MaxOutput;
	sint32 InputValue;
}Mapping_t;

void ADC_voidInit(void);

uint8 ADC_u16StartConversionSynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result);

uint8 ADC_u16StartConversionAsynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result,void (*Copy_pvoidNotificationFunc)(void));

sint32 ADC_s32Mapping(Mapping_t* Object );

#endif /* ADC_INTERFACE_H_ */
