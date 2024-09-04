#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"
#include "CLCD_interface.h"
void ChangeRacket1Pos(void);
void ChangeRacket2Pos(void);
void BallPos(void);
uint8 Global_u8Racket1=0;
uint8 Global_u8Racket2=0;
uint8 Global_u8Ball=0;
uint8 Local_u8WinnerIndicator=0;
void main(void)
{
	uint8 Local_u8Counter1;
	PORT_voidInit();
	CLCD_voidInit();
	_delay_ms(100);
	GIE_voidEnableGlobal();
	EXTI_voidInit();
	EXTI_u8SetCallBack(EXTI_u8INT0,&ChangeRacket1Pos);
	EXTI_u8SetCallBack(EXTI_u8INT1,&ChangeRacket2Pos);
	EXTI_u8SetCallBack(EXTI_u8INT2,&BallPos);
	CLCD_voidGoToXY(0,Global_u8Racket1);
	CLCD_voidSendData('Y');
	CLCD_voidGoToXY(15,Global_u8Racket2);
	CLCD_voidSendData('Y');

	while(1)
	{
		if(Local_u8WinnerIndicator==0)
		{
		for(Local_u8Counter1=1;Local_u8Counter1<=14;Local_u8Counter1++)
		{
			CLCD_voidGoToXY(Local_u8Counter1,Global_u8Ball);
			CLCD_voidSendData('.');
			_delay_ms(100);
			CLCD_voidGoToXY(Local_u8Counter1,Global_u8Ball);
			CLCD_voidSendData(' ');
		}
		if(Global_u8Ball!=Global_u8Racket2)
		{
			Local_u8WinnerIndicator=1;
			CLCD_voidSendComd(1);
			CLCD_u8SendString("Left player wins");
		}
		}
		if(Local_u8WinnerIndicator==0)
		{
		for(Local_u8Counter1=14;Local_u8Counter1>=1;Local_u8Counter1--)
		{
			CLCD_voidGoToXY(Local_u8Counter1,Global_u8Ball);
			CLCD_voidSendData('.');
			_delay_ms(100);
			CLCD_voidGoToXY(Local_u8Counter1,Global_u8Ball);
			CLCD_voidSendData(' ');
		}
		if(Global_u8Ball!=Global_u8Racket1)
		{
			Local_u8WinnerIndicator=1;
			CLCD_voidSendComd(1);
			CLCD_u8SendString("Right player wins");
		}
		}
	}
}
void ChangeRacket1Pos(void)
{
	if(Local_u8WinnerIndicator==0)
	{
	if(Global_u8Racket1==0)
	{
		CLCD_voidGoToXY(0,Global_u8Racket1);
		CLCD_voidSendData(' ');
		Global_u8Racket1=1;
		CLCD_voidGoToXY(0,Global_u8Racket1);
		CLCD_voidSendData('Y');
	}
	else if(Global_u8Racket1==1)
	{
		CLCD_voidGoToXY(0,Global_u8Racket1);
		CLCD_voidSendData(' ');
		Global_u8Racket1=0;
		CLCD_voidGoToXY(0,Global_u8Racket1);
		CLCD_voidSendData('Y');
	}
	}
}
void ChangeRacket2Pos(void)
{
	if(Local_u8WinnerIndicator==0)
	{
	if(Global_u8Racket2==0)
	{
		CLCD_voidGoToXY(15,Global_u8Racket2);
		CLCD_voidSendData(' ');
		Global_u8Racket2=1;
		CLCD_voidGoToXY(15,Global_u8Racket2);
		CLCD_voidSendData('Y');
	}
	else if(Global_u8Racket2==1)
	{
		CLCD_voidGoToXY(15,Global_u8Racket2);
		CLCD_voidSendData(' ');
		Global_u8Racket2=0;
		CLCD_voidGoToXY(15,Global_u8Racket2);
		CLCD_voidSendData('Y');
	}
	}
}
void BallPos(void)
{
	if(Local_u8WinnerIndicator==0)
	{
	if(Global_u8Ball==0)
	{
		Global_u8Ball=1;
		CLCD_voidGoToXY(1,0);
		CLCD_u8SendString("              ");
		CLCD_voidGoToXY(1,1);
		CLCD_u8SendString("              ");
	}
	else if(Global_u8Ball==1)
	{
		Global_u8Ball=0;
		CLCD_voidGoToXY(1,0);
		CLCD_u8SendString("              ");
		CLCD_voidGoToXY(1,1);
		CLCD_u8SendString("              ");
	}
	}
}
