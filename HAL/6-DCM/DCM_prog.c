#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "DCM_prv.h"
#include "DCM_interface.h"

uint8 DCM_u8RotateRight(const DCM_t* Object)
{
	uint8 Local_StateErr=OK;
	if(Object!=NULL)
	{

		if(Object->Port<=DIO_u8PORTD||Object->Pin1_4<=DIO_u8PIN7||Object->Pin2_3<=DIO_u8PIN7)
		{
			DIO_u8SetPinValue(Object->Port,Object->Pin1_4,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(Object->Port,Object->Pin2_3,DIO_u8PIN_HIGH);
		}
		else
		{
			Local_StateErr=NOK;
		}
	}
	else
	{
		Local_StateErr=NULL_PTR_ERR;
	}
	return Local_StateErr;
}

uint8 DCM_u8RotateLeft(const DCM_t* Object)
{
	uint8 Local_StateErr=OK;
	if(Object!=NULL)
	{

		if(Object->Port<=DIO_u8PORTD||Object->Pin1_4<=DIO_u8PIN7||Object->Pin2_3<=DIO_u8PIN7)
		{
			DIO_u8SetPinValue(Object->Port,Object->Pin2_3,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(Object->Port,Object->Pin1_4,DIO_u8PIN_HIGH);
		}
		else
		{
			Local_StateErr=NOK;
		}
	}
	else
	{
		Local_StateErr=NULL_PTR_ERR;
	}
	return Local_StateErr;
}

uint8 DCM_u8Stop(const DCM_t* Object)
{
	uint8 Local_StateErr=OK;
	if(Object!=NULL)
	{

		if(Object->Port<=DIO_u8PORTD||Object->Pin1_4<=DIO_u8PIN7||Object->Pin2_3<=DIO_u8PIN7)
		{
			DIO_u8SetPinValue(Object->Port,Object->Pin2_3,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(Object->Port,Object->Pin1_4,DIO_u8PIN_LOW);
		}
		else
		{
			Local_StateErr=NOK;
		}
	}
	else
	{
		Local_StateErr=NULL_PTR_ERR;
	}
	return Local_StateErr;
}

