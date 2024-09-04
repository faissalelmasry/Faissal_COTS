/*******************************************************/
/*******************************************************/
/**********      Author: Faissal Mahmoud      **********/  
/**********      File: SSD_program.c          **********/ 
/**********      Version: 1.00                **********/ 
/*******************************************************/
/*******************************************************/
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "SSD_prv.h"
#include "SSD_interface.h"


#define ZERO   0b00111111
#define ONE    0b00000110
#define TWO    0b01011011
#define THREE  0b01001111
#define FOUR   0b01100110
#define FIVE   0b01101101
#define SIX    0b01111101
#define SEVEN  0b00000111
#define EIGHT  0b01111111
#define NINE   0b01101111

uint8 SSD_u8Arr[10]={ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE}; //seven segment values


uint8 SSD_u8SetNumber(const SSD_t* Copy_SSDObject,uint8 Copy_u8Number)
{
	uint8 Local_u8StateError=OK;
	if(Copy_SSDObject!=NULL&&Copy_u8Number<=9)
	{
		if(Copy_SSDObject->Type==ANODE)
		{
			DIO_u8SetPortValue(Copy_SSDObject->Port,~SSD_u8Arr[Copy_u8Number]);
			DIO_u8SetPinValue(Copy_SSDObject->EnablePort,Copy_SSDObject->EnablePin,DIO_u8PIN_HIGH);
		}
		else if(Copy_SSDObject->Type==CATHODE)
		{
			DIO_u8SetPortValue(Copy_SSDObject->Port,SSD_u8Arr[Copy_u8Number]);
			DIO_u8SetPinValue(Copy_SSDObject->EnablePort,Copy_SSDObject->EnablePin,DIO_u8PIN_LOW);
		}
		else
		{
			Local_u8StateError=NOK;
		}
		
	}
	else
	{
		Local_u8StateError=NULL_PTR_ERR;
	}
	return Local_u8StateError;
		
}
