#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include <util/delay.h>

void main(void)
{
	/*LCD pins initialization*/
	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_OUTPUT);//RS pin
	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_OUTPUT);//RW pin
	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN2,DIO_u8PIN_OUTPUT);//E pin
	DIO_u8SetPortDirection(DIO_u8PORTB,0xFF);//data port
	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_INPUT);//UP PB
	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN4,DIO_u8PIN_INPUT);//DOWN PB
	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_INPUT);//ENTER PB
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_HIGH);//UP PB pull up
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN4,DIO_u8PIN_HIGH);//DOWN PB pull up
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_HIGH);//ENTER PB pull up

	CLCD_voidInit();

	sint32 Local_s8Num1=1;
	sint8 Local_s8OperatorArrIndex=0;
	char  Local_charOperatorArray[4]={'+','-','*','/'};
	uint8 Local_u8Operator='+';
	sint32 Local_s8Num2=1;
	sint8 Local_s8Result;
	uint16 Local_s32Result;
	char  Local_chDivisionRes[4];
	sint8 Local_s8DivisionCounter=0;
	sint8 Local_s8UpBitMode;
	sint8 Local_s8DownBitMode;
	uint8 Local_u8EnterBitMode;
	uint8 Local_u8EnterCounter=0;
	uint8 Local_u8ArrowPattern[8]={0b00000100,0b00001010,0b00010101,0b00000100,0b00000100,0b00000100,0b00000100,0};
	while(1)
	{
		CLCD_voidGoToXY(0,0);
		CLCD_voidSendNumber(Local_s8Num1);
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendData(Local_u8Operator);
		CLCD_voidGoToXY(2,0);
		CLCD_voidSendNumber(Local_s8Num2);
		DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN5,&Local_u8EnterBitMode);
		if(Local_u8EnterCounter!=3)
		{
			CLCD_voidGoToXY(3,0);
			CLCD_u8SendString("       ");
		}
		if(Local_u8EnterBitMode==0)
		{
			_delay_ms(100);
			Local_u8EnterCounter++;
		}
		if(Local_u8EnterCounter==0)
		{
		CLCD_voidGoToXY(0,0);
		CLCD_voidSendNumber(Local_s8Num1);
		DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN3,&Local_s8UpBitMode);
		DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN4,&Local_s8DownBitMode);
		if(Local_s8UpBitMode==0)
		{
			_delay_ms(100);
			Local_s8Num1++;
			if(Local_s8Num1>9)
				{
					Local_s8Num1=0;
				}
			else if(Local_s8Num1<0)
			{
				Local_s8Num1=9;
			}
		}
		if(Local_s8DownBitMode==0)
		{
			_delay_ms(100);
			Local_s8Num1--;
			if(Local_s8Num1>9)
				{
					Local_s8Num1=0;
				}
			else if(Local_s8Num1<0)
			{
				Local_s8Num1=9;
			}
		}
		CLCD_voidGoToXY(1,1);
		CLCD_voidSendData(' ');
		CLCD_voidGoToXY(2,1);
		CLCD_voidSendData(' ');
		CLCD_voidSendSpecialCharacter(Local_u8ArrowPattern,0,0,1);
	}
		else if(Local_u8EnterCounter==1)
		{
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendData(Local_u8Operator);
			DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN3,&Local_s8UpBitMode);
			DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN4,&Local_s8DownBitMode);
			if(Local_s8UpBitMode==0)
			{
				_delay_ms(200);
				Local_s8OperatorArrIndex++;
				if(Local_s8OperatorArrIndex>3)
					{
						Local_s8OperatorArrIndex=0;
					}
				Local_u8Operator=Local_charOperatorArray[Local_s8OperatorArrIndex];
			}
			if(Local_s8DownBitMode==0)
			{
				_delay_ms(100);
				Local_s8OperatorArrIndex--;
				if(Local_s8OperatorArrIndex<0)
					{
						Local_s8OperatorArrIndex=3;
					}
				Local_u8Operator=Local_charOperatorArray[Local_s8OperatorArrIndex];
			}
			CLCD_voidGoToXY(0,1);
			CLCD_voidSendData(' ');
			CLCD_voidGoToXY(2,1);
			CLCD_voidSendData(' ');
			CLCD_voidSendSpecialCharacter(Local_u8ArrowPattern,0,1,1);

		}
		else if(Local_u8EnterCounter==2)
		{

			CLCD_voidGoToXY(2,0);
			CLCD_voidSendNumber(Local_s8Num2);
			DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN3,&Local_s8UpBitMode);
			DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN4,&Local_s8DownBitMode);
			if(Local_s8UpBitMode==0)
			{
				_delay_ms(100);
				Local_s8Num2++;
				if(Local_s8Num2>9)
					{
						Local_s8Num2=0;
					}
				else if(Local_s8Num2<0)
				{
					Local_s8Num2=9;
				}
			}
			if(Local_s8DownBitMode==0)
			{
				_delay_ms(100);
				Local_s8Num2--;
				if(Local_s8Num2>9)
					{
						Local_s8Num2=0;
					}
				else if(Local_s8Num2<0)
				{
					Local_s8Num2=9;
				}
			}
			if(Local_u8Operator=='/')
			{
				if(Local_s8Num2==0)
				{
					Local_s8Num2=1;
				}

			}
			CLCD_voidGoToXY(0,1);
			CLCD_voidSendData(' ');
			CLCD_voidGoToXY(1,1);
			CLCD_voidSendData(' ');
			CLCD_voidSendSpecialCharacter(Local_u8ArrowPattern,0,2,1);

		}
		else if(Local_u8EnterCounter==3)
		{
			CLCD_voidGoToXY(3,0);
			CLCD_voidSendData('=');
			if(Local_u8Operator=='/')
			{
				if(Local_s8Num1/Local_s8Num2!=0)
				{
				Local_s32Result=(((Local_s8Num1)*100)/Local_s8Num2);
				while(Local_s32Result>0)
				{
					Local_chDivisionRes[Local_s8DivisionCounter]=Local_s32Result%10;
					Local_s8DivisionCounter++;
					Local_s32Result/=10;
				}
				CLCD_voidSendNumber(Local_chDivisionRes[Local_s8DivisionCounter-1]);
				CLCD_voidSendData('.');
				CLCD_voidSendNumber(Local_chDivisionRes[Local_s8DivisionCounter-2]);
				CLCD_voidSendNumber(Local_chDivisionRes[Local_s8DivisionCounter-3]);
				Local_s8DivisionCounter=0;
				}
				else
				{
					Local_s32Result=(((Local_s8Num1)*100)/Local_s8Num2);
					while(Local_s32Result>0)
					{
						Local_chDivisionRes[Local_s8DivisionCounter]=Local_s32Result%10;
						Local_s8DivisionCounter++;
						Local_s32Result/=10;
					}
					CLCD_voidSendData('0');
					CLCD_voidSendData('.');
					CLCD_voidSendNumber(Local_chDivisionRes[1]);
					CLCD_voidSendNumber(Local_chDivisionRes[0]);
					Local_s8DivisionCounter=0;
				}
			}
			else if(Local_u8Operator=='+')
			{
				Local_s8Result=Local_s8Num1+Local_s8Num2;
				CLCD_voidSendNumber(Local_s8Result);
			}
			else if(Local_u8Operator=='-')
			{
				Local_s8Result=Local_s8Num1-Local_s8Num2;
				CLCD_voidSendNumber(Local_s8Result);
			}
			else if(Local_u8Operator=='*')
			{
				Local_s8Result=Local_s8Num1*Local_s8Num2;
				CLCD_voidSendNumber(Local_s8Result);
			}
			CLCD_voidGoToXY(0,1);
			CLCD_voidSendData(' ');
			CLCD_voidGoToXY(1,1);
			CLCD_voidSendData(' ');
			CLCD_voidGoToXY(2,1);
			CLCD_voidSendData(' ');
		}
		else
		{
			Local_u8EnterCounter=0;
		}
	}


}

