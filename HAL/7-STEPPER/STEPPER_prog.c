#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "STEPPER_prv.h"
#include "STEPPER_interface.h"

uint8 STEPPER_u8Rotate(STEPPER_t* Object,uint16 Copy_u16Angle,uint8 Copy_Directon)
{
	uint8 LocalErrorState=OK;
	uint16 LocalCounter;
	if(Object!=NULL)
	{
		if(Object->Port<=DIO_u8PORTD && Object->BluePin<=DIO_u8PIN7 && Object->PinkPin<=DIO_u8PIN7 && Object->YellowPin<=DIO_u8PIN7 && Object->OrangePin<=DIO_u8PIN7)
		{
			uint16 Local_StepsNumber=(uint16)((uint32)Copy_u16Angle*1024/180);
			if(Copy_Directon==CCW)
			{
				for(LocalCounter=0;LocalCounter<=Local_StepsNumber;LocalCounter++)
				{
					if(LocalCounter%4==0)
					{
						DIO_u8SetPinValue(Object->Port,Object->PinkPin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->OrangePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->YellowPin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->BluePin,DIO_u8PIN_LOW);
						_delay_ms(2);
					}
					else if(LocalCounter%4==1)
					{
						DIO_u8SetPinValue(Object->Port,Object->BluePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->OrangePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->YellowPin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->PinkPin,DIO_u8PIN_LOW);
						_delay_ms(2);
					}
					else if(LocalCounter%4==2)
					{
						DIO_u8SetPinValue(Object->Port,Object->PinkPin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->OrangePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->BluePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->YellowPin,DIO_u8PIN_LOW);
						_delay_ms(2);
					}
					else if(LocalCounter%4==3)
					{
						DIO_u8SetPinValue(Object->Port,Object->BluePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->PinkPin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->YellowPin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->OrangePin,DIO_u8PIN_LOW);
						_delay_ms(2);
					}

				}
			}
			else if(Copy_Directon==CW)
			{

				for(LocalCounter=0;LocalCounter<=Local_StepsNumber;LocalCounter++)
				{
					if(LocalCounter%4==0)
					{
						DIO_u8SetPinValue(Object->Port,Object->BluePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->OrangePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->YellowPin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->OrangePin,DIO_u8PIN_LOW);
						_delay_ms(2);
					}
					else if(LocalCounter%4==1)
					{
						DIO_u8SetPinValue(Object->Port,Object->BluePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->OrangePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->PinkPin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->YellowPin,DIO_u8PIN_LOW);
						_delay_ms(2);
					}
					else if(LocalCounter%4==2)
					{
						DIO_u8SetPinValue(Object->Port,Object->YellowPin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->OrangePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->BluePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->PinkPin,DIO_u8PIN_LOW);
						_delay_ms(2);
					}
					else if(LocalCounter%4==3)
					{
						DIO_u8SetPinValue(Object->Port,Object->OrangePin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->PinkPin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->YellowPin,DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(Object->Port,Object->BluePin,DIO_u8PIN_LOW);
						_delay_ms(2);
					}

				}

			}
			else
			{
				LocalErrorState=NOK;
			}
			}
		else
		{
			LocalErrorState=NOK;
		}
	}
	else
	{
		LocalErrorState=NULL_PTR_ERR;
	}
	return LocalErrorState;
}
