/*******************************************************/
/*******************************************************/
/**********      Author: Faissal Mahmoud      **********/  
/**********      File: CLCD_program.c      **********/ 
/**********      Version: 1.00               **********/ 
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_prv.h"
#include "CLCD_cfg.h"
#include "CLCD_prv.h"

static void voidSendEnablePulse(void)
{
	/*set enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}

static void voidSetLCDHalfDataPort(uint8 Copy_u8Nipple)
{
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D4_PIN,GET_BIT(Copy_u8Nipple,0));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D5_PIN,GET_BIT(Copy_u8Nipple,1));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D6_PIN,GET_BIT(Copy_u8Nipple,2));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D7_PIN,GET_BIT(Copy_u8Nipple,3));
}

void CLCD_voidSendComd(uint8 Copy_Cmd)
{
	/*set RS pin as low for command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);
    #if CLCD_RW_CTRL_EN==ENABLED
	/*set RW pin as low for write operation*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	#endif
	/*set command at data port*/
	#if CLCD_OP_MODE==EIGHT_BIT_MODE
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_Cmd);
	voidSendEnablePulse();
	#elif CLCD_OP_MODE==FOUR_BIT_MODE
	voidSetLCDHalfDataPort(Copy_Cmd>>4);
	voidSendEnablePulse();
	voidSetLCDHalfDataPort(Copy_Cmd);
	voidSendEnablePulse();
	#endif
}

void CLCD_voidSendData(uint8 Copy_Data)
{
	/*set RS pin as high for data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);
	#if CLCD_RW_CTRL_EN==ENABLED
	/*set RW pin as low for write operation*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	#endif
	/*set data at data port*/
	#if CLCD_OP_MODE==EIGHT_BIT_MODE
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_Data);
	voidSendEnablePulse();
	#elif CLCD_OP_MODE==FOUR_BIT_MODE
	voidSetLCDHalfDataPort(Copy_Data>>4);
	voidSendEnablePulse();
	voidSetLCDHalfDataPort(Copy_Data);
	voidSendEnablePulse();
	#endif

}

void CLCD_voidInit(void) /*from datasheet*/
{
	/*wait for more than 30 ms after power on*/
	_delay_ms(40);
	/*function set command: 2lines(DB3 high) and small font(DB2 low)*/
	#if CLCD_OP_MODE==EIGHT_BIT_MODE
	CLCD_voidSendComd(0b00111000);
	#elif CLCD_OP_MODE==FOUR_BIT_MODE
	voidSetLCDHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetLCDHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetLCDHalfDataPort(0b1000);
	voidSendEnablePulse();
	#endif

	/*display on/off control command: display enable(DB2 high),cursor(DB1 low),blink(DB0 low)*/
	CLCD_voidSendComd(0b00001100);
	/*display clear command*/
	CLCD_voidSendComd(0b00000001);
	
}
uint8 CLCD_u8SendString(char Copy_chstring[])
{
	uint8 Local_u8StateError=OK;
	if(Copy_chstring!=NULL)
	{
	for(uint8 Local_u8LoopCounter=0;Copy_chstring[Local_u8LoopCounter]!='\0';Local_u8LoopCounter++)
	{
		CLCD_voidSendData(Copy_chstring[Local_u8LoopCounter]);
	}
	}
	else
	{
		Local_u8StateError=NULL_PTR_ERR;
	}
	return Local_u8StateError;
}
void CLCD_voidSendNumber(sint32 Copy_s32Number)
{
	char Local_chArray[10];
	sint8 Local_s8Remainder,Local_s8ArrayIndex=0;
	if(Copy_s32Number==0)
	{
		CLCD_voidSendData(48);
	}
	else if(Copy_s32Number>0)
	{
	while(Copy_s32Number!=0)
	{
		Local_s8Remainder=Copy_s32Number%10;
		Local_chArray[Local_s8ArrayIndex]=Local_s8Remainder;
		Local_s8ArrayIndex++;
		Copy_s32Number/=10;
	}
	}
	else
	{
		CLCD_voidSendData('-');
		while(Copy_s32Number!=0)
		{
			Local_s8Remainder=-Copy_s32Number%10;
			Local_chArray[Local_s8ArrayIndex]=Local_s8Remainder;
			Local_s8ArrayIndex++;
			Copy_s32Number/=10;
		}
	}

	{
	for(sint8 Local_s8Counter=Local_s8ArrayIndex-1;Local_s8Counter>=0;Local_s8Counter--)
	{
		CLCD_voidSendData(Local_chArray[Local_s8Counter]+48);
	}
	}
}
void CLCD_voidGoToXY(uint8 Copy_u8XPos,uint8 Copy_u8YPos)
{
	uint8 Local_u8DDRAMAdd;
	if(Copy_u8YPos==0u)
	{
		Local_u8DDRAMAdd=Copy_u8XPos;
	}
	else if(Copy_u8YPos==1u)
	{
		Local_u8DDRAMAdd=Copy_u8XPos+0x40;
	}
	Local_u8DDRAMAdd|=1<<7;
	CLCD_voidSendComd(Local_u8DDRAMAdd);
}
uint8 CLCD_u8SinWaveSendString(char Copy_chstring[])
{
	uint8 Local_u8StateError=OK;
	uint8 Local_u8XCoordinate=0;
	uint8 Local_u8YCoordinate=0;
	if(Copy_chstring!=NULL)
	{
	for(uint8 Local_u8LoopCounter=0;Copy_chstring[Local_u8LoopCounter]!='\0';Local_u8LoopCounter++,Local_u8XCoordinate++)
	{
		CLCD_voidGoToXY(Local_u8XCoordinate,Local_u8YCoordinate);
		CLCD_voidSendData(Copy_chstring[Local_u8LoopCounter]);
		if(Local_u8YCoordinate==0)Local_u8YCoordinate=1;
		else Local_u8YCoordinate=0;
	}
	}
	else
	{
		Local_u8StateError=NULL_PTR_ERR;
	}
	return Local_u8StateError;
}

void CLCD_voidSendSpecialCharacter(uint8 Copy_u8Pattern[],uint8 Copy_u8PatternNum,uint8 Copy_u8XPos,uint8 Copy_u8YPos)
{
	uint8 Local_u8CGRAMAdd=Copy_u8PatternNum*8u;
	uint8 Local_u8LoopCounter;
	SET_BIT(Local_u8CGRAMAdd,6);
	CLCD_voidSendComd(Local_u8CGRAMAdd);
	for(Local_u8LoopCounter=0;Local_u8LoopCounter<8;Local_u8LoopCounter++)
	{
		CLCD_voidSendData(Copy_u8Pattern[Local_u8LoopCounter]);
	}
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);
	CLCD_voidSendData(Copy_u8PatternNum);

}
