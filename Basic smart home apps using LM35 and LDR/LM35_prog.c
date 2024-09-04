/*
 * LM35_prog.c
 *
 *  Created on: Aug 22, 2024
 *      Author: Acer
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "LM35_interface.h"


uint16 LM35_u16GetTemp(uint8 Copy_u8ADCChannel)
{
	uint8 Local_u8AnalogReading;
	uint16 Local_u16TempReading;
	ADC_u16StartConversionSynch(Copy_u8ADCChannel,(uint16*)&Local_u8AnalogReading);
	Local_u16TempReading=(uint16)((uint32)Local_u8AnalogReading*500ul/256ul);
	return 	Local_u16TempReading;
}
