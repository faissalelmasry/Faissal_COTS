/*
 * LDR_prog.c
 *
 *  Created on: Aug 23, 2024
 *      Author: Acer
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "LDR_cfg.h"
#include "ADC_interface.h"

uint16 LDR_u16GetAnalogmilVolt(uint8 Copy_u8ADCChannel)
{
	uint16 Local_u16MappingObject;
	uint16 Local_u16Temp;
	Mapping_t Object1;
	Object1.MinInput=MIN_INPUT_VAL;
	Object1.MinOutput=MIN_OUTPUT_VAL;
	Object1.MaxInput=MAX_INPUT_VAL;
	Object1.MaxOutput=MAX_OUTPUT_VAL;
	ADC_u16StartConversionSynch(Copy_u8ADCChannel,(uint16*)&Local_u16Temp);
	Object1.InputValue=Local_u16Temp;
	Local_u16MappingObject=ADC_s32Mapping(&Object1);
	return Local_u16MappingObject;
}


