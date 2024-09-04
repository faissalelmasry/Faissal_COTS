#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include <util/delay.h>


void main(void)
{
	PORT_voidInit();
	CLCD_voidInit();
	uint8 Local_u8PressedKey;
	sint8 Local_s8HrsTenth=0;
	sint8 Local_s8HrsUnit=0;
	sint8 Local_s8MinsTenth=0;
	sint8 Local_s8MinsUnit=0;
	sint8 Local_s8SecsTenth=0;
	sint8 Local_s8SecsUnit=0;
	sint8 Local_u8Arrow=0;
	uint8 Local_u8StartIndicator=0;
	uint8 Local_u8ArrowPattern[8]={0b00000100,0b00001010,0b00010101,0b00000100,0b00000100,0b00000100,0b00000100,0};
	CLCD_u8SendString("00:00:00");
	CLCD_voidSendSpecialCharacter(Local_u8ArrowPattern,0,0,1);
	while(1)
	{
		Local_u8PressedKey=KPD_u8GetPressedKey();
		if(Local_u8PressedKey=='S')Local_u8StartIndicator=1;
		if(Local_u8PressedKey=='N')Local_u8StartIndicator=0;

		if(Local_u8PressedKey!=0xff&&Local_u8StartIndicator!=1)
		{
			if(Local_u8PressedKey=='R')
			{
				Local_u8Arrow++;
			}
			if(Local_u8PressedKey=='L')
			{
				Local_u8Arrow--;
			}
			if(Local_u8Arrow>5)Local_u8Arrow=0;
			if(Local_u8Arrow<0)Local_u8Arrow=5;
			switch(Local_u8Arrow)
			{
				case 0:
					if(Local_u8PressedKey>=0&&Local_u8PressedKey<=9)
					{
						Local_s8HrsTenth=Local_u8PressedKey;
						CLCD_voidGoToXY(0,0);
						CLCD_voidSendNumber(Local_s8HrsTenth);
					}
					CLCD_voidGoToXY(0,1);CLCD_u8SendString("                ");
					CLCD_voidSendSpecialCharacter(Local_u8ArrowPattern,0,0,1);break;
				case 1:
					if(Local_u8PressedKey>=0&&Local_u8PressedKey<=9)
					{
						Local_s8HrsUnit=Local_u8PressedKey;
						CLCD_voidGoToXY(1,0);
						CLCD_voidSendNumber(Local_s8HrsUnit);
					}
					CLCD_voidGoToXY(0,1);CLCD_u8SendString("                ");
					CLCD_voidSendSpecialCharacter(Local_u8ArrowPattern,0,1,1);break;
				case 2:
					if(Local_u8PressedKey>=0&&Local_u8PressedKey<6)
					{
						Local_s8MinsTenth=Local_u8PressedKey;
						CLCD_voidGoToXY(3,0);
						CLCD_voidSendNumber(Local_s8MinsTenth);
					}
					CLCD_voidGoToXY(0,1);CLCD_u8SendString("                ");
					CLCD_voidSendSpecialCharacter(Local_u8ArrowPattern,0,3,1);break;
				case 3:
					if(Local_u8PressedKey>=0&&Local_u8PressedKey<=9)
					{
						Local_s8MinsUnit=Local_u8PressedKey;
						CLCD_voidGoToXY(4,0);
						CLCD_voidSendNumber(Local_s8MinsUnit);
					}
					CLCD_voidGoToXY(0,1);CLCD_u8SendString("                ");
					CLCD_voidSendSpecialCharacter(Local_u8ArrowPattern,0,4,1);break;
				case 4:
					if(Local_u8PressedKey>=0&&Local_u8PressedKey<6)
					{
						Local_s8SecsTenth=Local_u8PressedKey;
						CLCD_voidGoToXY(6,0);
						CLCD_voidSendNumber(Local_s8SecsTenth);
					}
					CLCD_voidGoToXY(0,1);CLCD_u8SendString("                ");
					CLCD_voidSendSpecialCharacter(Local_u8ArrowPattern,0,6,1);break;
				case 5:
					if(Local_u8PressedKey>=0&&Local_u8PressedKey<=9)
					{
						Local_s8SecsUnit=Local_u8PressedKey;
						CLCD_voidGoToXY(7,0);
						CLCD_voidSendNumber(Local_s8SecsUnit);
					}
					CLCD_voidGoToXY(0,1);CLCD_u8SendString("                ");
					CLCD_voidSendSpecialCharacter(Local_u8ArrowPattern,0,7,1);break;
			}
		}
		if(Local_u8StartIndicator==1)
		{
			CLCD_voidGoToXY(0,1);CLCD_u8SendString("                ");
			CLCD_voidGoToXY(7,0);
			CLCD_voidSendNumber(Local_s8SecsUnit);
			_delay_ms(1000);
			if(Local_s8SecsUnit==0&&Local_s8SecsTenth==0&&Local_s8MinsUnit==0&&Local_s8MinsTenth==0&&Local_s8HrsUnit==0&&Local_s8HrsTenth==0)
			{
				 CLCD_voidGoToXY(0,1);
				 CLCD_u8SendString("Time is up!");
				 Local_u8StartIndicator=0;
				 Local_s8HrsTenth=0;
				 Local_s8HrsUnit=0;
				 Local_s8MinsTenth=0;
				 Local_s8MinsUnit=0;
				 Local_s8SecsTenth=0;
				 Local_s8SecsUnit=1;
			}
			else if(Local_s8SecsUnit==0&&Local_s8SecsTenth==0&&Local_s8MinsUnit==0&&Local_s8MinsTenth==0&&Local_s8HrsUnit==0)
			{
				Local_s8SecsUnit=10;
				Local_s8SecsTenth=5;
				Local_s8MinsUnit=9;
				Local_s8MinsTenth=5;
				Local_s8HrsUnit=9;
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendNumber(Local_s8HrsUnit);
				CLCD_voidGoToXY(3,0);
				CLCD_voidSendNumber(Local_s8MinsTenth);
				CLCD_voidGoToXY(4,0);
				CLCD_voidSendNumber(Local_s8MinsUnit);
				CLCD_voidGoToXY(6,0);
				CLCD_voidSendNumber(Local_s8SecsTenth);
				Local_s8HrsTenth--;
				CLCD_voidGoToXY(0,0);
				CLCD_voidSendNumber(Local_s8HrsTenth);
			}
			else if(Local_s8SecsUnit==0&&Local_s8SecsTenth==0&&Local_s8MinsUnit==0&&Local_s8MinsTenth==0)
			{
				Local_s8SecsUnit=10;
				Local_s8SecsTenth=5;
				Local_s8MinsUnit=9;
				Local_s8MinsTenth=5;
				CLCD_voidGoToXY(3,0);
				CLCD_voidSendNumber(Local_s8MinsTenth);
				CLCD_voidGoToXY(4,0);
				CLCD_voidSendNumber(Local_s8MinsUnit);
				CLCD_voidGoToXY(6,0);
				CLCD_voidSendNumber(Local_s8SecsTenth);
				Local_s8HrsUnit--;
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendNumber(Local_s8HrsUnit);
			}
			else if(Local_s8SecsUnit==0&&Local_s8SecsTenth==0&&Local_s8MinsUnit==0)
			{
				Local_s8SecsUnit=10;
				Local_s8SecsTenth=5;
				Local_s8MinsUnit=9;
				CLCD_voidGoToXY(4,0);
				CLCD_voidSendNumber(Local_s8MinsUnit);
				CLCD_voidGoToXY(6,0);
				CLCD_voidSendNumber(Local_s8SecsTenth);
				Local_s8MinsTenth--;
				CLCD_voidGoToXY(3,0);
				CLCD_voidSendNumber(Local_s8MinsTenth);
			}
			else if(Local_s8SecsUnit==0&&Local_s8SecsTenth==0)
			{
				Local_s8SecsUnit=10;
				Local_s8SecsTenth=5;
				CLCD_voidGoToXY(6,0);
				CLCD_voidSendNumber(Local_s8SecsTenth);
				Local_s8MinsUnit--;
				CLCD_voidGoToXY(4,0);
				CLCD_voidSendNumber(Local_s8MinsUnit);
			}
			else if(Local_s8SecsUnit==0)
			{
				Local_s8SecsUnit=10;
				Local_s8SecsTenth--;
				CLCD_voidGoToXY(6,0);
				CLCD_voidSendNumber(Local_s8SecsTenth);
			}
			Local_s8SecsUnit--;
		}
	}


}

