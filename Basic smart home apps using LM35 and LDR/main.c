#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "defines.h"
#include "util/delay.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "ADC_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "DCM_interface.h"
#include "LDR_interface.h"
#include "LM35_interface.h"
#define TRIALS 3u
void Reset(void);
uint8 Local_u8Reset=0;
void main(void)
{
	PORT_voidInit();
	CLCD_voidInit();
	ADC_voidInit();
	GIE_voidEnableGlobal();
	EXTI_voidInit();
	EXTI_u8SetCallBack(EXTI_u8INT2,&Reset);
	DCM_t DCM_Object={DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN1};
	uint8 Local_u8PressedKey;
	uint8 Local_u8IDArr[10];
	uint8 Local_u8PassArr[10];
	uint8 Local_u8IDLen=0;
	uint8 Local_u8IDCounter=0;
	uint8 Local_u8PassLen=0;
	uint8 Local_u8PassCounter=0;
	uint32 Local_u8EnteredID;
	uint32 Local_u8EnteredPass;
	uint32 Local_u8RealID=12;
	uint32 Local_u8RealPass=12;
	uint16 Local_u16Temp;
	uint16 Local_u16Light;
	uint8 Local_u8Trials=TRIALS;
	uint8 Local_u8indicator=0;
	CLCD_u8SendString("WELCOME!");
	_delay_ms(1000);
	while(1)
	{
		if(Local_u8Trials!=0)
		{
		Local_u8EnteredPass=0;
		Local_u8EnteredID=0;
		DCM_u8Stop(&DCM_Object);
		DIO_u8SetPortValue(DIO_u8PORTC,0);
		Local_u8Reset=0;
		Local_u8IDLen=0;
		Local_u8PassLen=0;
		CLCD_voidSendComd(1);
		Local_u8PressedKey=KPD_u8GetPressedKey();
		CLCD_u8SendString("ID:");
		while(Local_u8PressedKey!='e'&&Local_u8Reset==0)
		{
		if(Local_u8PressedKey!=0xff)
		{
			while(KPD_u8GetPressedKey()!=0xff);
			CLCD_voidSendNumber(Local_u8PressedKey);
			Local_u8IDArr[Local_u8IDLen]=Local_u8PressedKey;
			Local_u8IDLen++;
		}
		Local_u8PressedKey=KPD_u8GetPressedKey();
		}
		CLCD_voidSendComd(1);
		Local_u8PressedKey=KPD_u8GetPressedKey();
		CLCD_u8SendString("Pass:");
		while(Local_u8PressedKey!='e'&&Local_u8Reset==0)
		{
		if(Local_u8PressedKey!=0xff)
		{
			while(KPD_u8GetPressedKey()!=0xff);
			CLCD_voidSendNumber(Local_u8PressedKey);
			Local_u8PassArr[Local_u8PassLen]=Local_u8PressedKey;
			Local_u8PassLen++;
			Local_u8PressedKey=KPD_u8GetPressedKey();
		}
		Local_u8PressedKey=KPD_u8GetPressedKey();
		}
		CLCD_voidSendComd(1);
		if(Local_u8IDLen>0)Local_u8EnteredID=Local_u8IDArr[0];
		for(Local_u8IDCounter=1;Local_u8IDCounter<Local_u8IDLen;Local_u8IDCounter++)
		{
			Local_u8EnteredID=Local_u8EnteredID*10+Local_u8IDArr[Local_u8IDCounter];
		}
		if(Local_u8PassLen>0)Local_u8EnteredPass=Local_u8PassArr[0];
		for(Local_u8PassCounter=1;Local_u8PassCounter<Local_u8PassLen;Local_u8PassCounter++)
		{
			Local_u8EnteredPass=Local_u8EnteredPass*10+Local_u8PassArr[Local_u8PassCounter];
		}
		while(Local_u8EnteredPass==Local_u8RealPass&&Local_u8EnteredID==Local_u8RealID&&Local_u8Reset==0)
		{
			Local_u8Trials=TRIALS;
			Local_u16Temp=LM35_u16GetTemp(ADC_SINGLE_ENDED_CH3);
			_delay_us(1);
			Local_u16Light=LDR_u16GetAnalogmilVolt(ADC_SINGLE_ENDED_CH4);
			CLCD_voidGoToXY(0,0);
			CLCD_voidSendNumber(Local_u16Temp);
			CLCD_u8SendString("  ");
			CLCD_voidGoToXY(0,1);
			CLCD_voidSendNumber(Local_u16Light);
			CLCD_u8SendString("   ");
			if(Local_u16Temp>=35)
			{
				DCM_u8RotateRight(&DCM_Object);
				CLCD_voidGoToXY(15,0);
				CLCD_voidSendData('M');
			}
			if(Local_u16Temp<30)
			{
				DCM_u8Stop(&DCM_Object);
				CLCD_voidGoToXY(15,0);
				CLCD_voidSendData(' ');
			}
			if(Local_u16Light<625)DIO_u8SetPortValue(DIO_u8PORTC,0);
			else if(Local_u16Light>=625&&Local_u16Light<1250)DIO_u8SetPortValue(DIO_u8PORTC,1);
			else if(Local_u16Light>=1250&&Local_u16Light<1875)DIO_u8SetPortValue(DIO_u8PORTC,3);
			else if(Local_u16Light>=1875&&Local_u16Light<2500)DIO_u8SetPortValue(DIO_u8PORTC,7);
			else if(Local_u16Light>=2500&&Local_u16Light<3125)DIO_u8SetPortValue(DIO_u8PORTC,15);
			else if(Local_u16Light>=3125&&Local_u16Light<3750)DIO_u8SetPortValue(DIO_u8PORTC,31);
			else if(Local_u16Light>=3750&&Local_u16Light<4375)DIO_u8SetPortValue(DIO_u8PORTC,63);
			else if(Local_u16Light>=4375&&Local_u16Light<4500)DIO_u8SetPortValue(DIO_u8PORTC,127);
			else if(Local_u16Light>=4500&&Local_u16Light<5000)DIO_u8SetPortValue(DIO_u8PORTC,255);
		}
		}
		else if(Local_u8Trials==0)
		{
			if(Local_u8indicator==0)
			{
			Local_u8indicator=1;
			CLCD_voidSendComd(1);
			CLCD_u8SendString("System Blocked!");
			}
		}
		if((Local_u8EnteredPass!=Local_u8RealPass||Local_u8EnteredID!=Local_u8RealID)&&Local_u8Trials!=0&&Local_u8Reset==0)
		{
			CLCD_u8SendString("wrong Pass");
			_delay_ms(1000);
			Local_u8Trials--;
		}

}
}

void Reset(void)
{
	Local_u8Reset=1;
}
