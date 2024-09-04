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
	Mapping_t Object1;
	Object1.MinInput=MIN_INPUT_VAL;
	Object1.MinOutput=MIN_OUTPUT_VAL;
	Object1.MaxInput=MAX_INPUT_VAL;
	Object1.MaxOutput=MAX_OUTPUT_VAL;
	Object1.InputValue=(uint8)ADC_u16GetChannelReading(Copy_u8ADCChannel);
	Local_u16MappingObject=ADC_s32Mapping(&Object1);
	return Local_u16MappingObject;
}


