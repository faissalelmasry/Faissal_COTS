#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "SSD_interface.h"
#include "DCM_interface.h"
#include "STEPPER_interface.h"
#define TRIALS 3u
void EmergencyStop(void);
uint8 Local_u8EmergencyIndicator=0;
DCM_t Object1={DIO_u8PORTD,DIO_u8PIN5,DIO_u8PIN4};
void main(void)
{
	uint8 Local_u8PressedKey;
	uint8 Local_u8Counter1=0;
	uint8 Local_u8Counter2=0;
	uint32 Local_u8EnteredID=0;
	uint32 Local_u32RealPass=1;
	uint32 Local_u32RealID=1;
	uint32 Local_u8EnteredPass=0;
	uint8 Local_u8IDArr[16];
	uint8 Local_u8PassArr[16];
	uint8 Local_u8DCMIndicator=0;
	uint8 Local_u8StepperIndicator=0;
	uint8 Local_u8Counter=0;
	uint32 Local_u8Stepperangle=0;
	uint8 Local_Arr[10];
	sint8 Local_ArrCounter;
	sint8 Local_u8PassTrials=TRIALS;
	STEPPER_t Object2={DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN5,DIO_u8PIN6,DIO_u8PIN7};
	SSD_t Object3={CATHODE,DIO_u8PORTA,DIO_u8PIN0,DIO_u8PORTD,DIO_u8PIN7};
	PORT_voidInit();
	CLCD_voidInit();
	CLCD_voidGoToXY(0,0);
	CLCD_u8SendString("Welcome!");
	_delay_ms(1000);
	CLCD_voidSendComd(1);
	GIE_voidEnableGlobal();
	EXTI_voidInit();
	EXTI_u8SetCallBack(EXTI_u8INT0,&EmergencyStop);

	while(1)
	{
		Local_u8EmergencyIndicator=0;
		Local_u8EnteredID=0;
		Local_u8EnteredPass=0;
		Local_u8Counter1=0;
		Local_u8Counter2=0;
		while(Local_u8EmergencyIndicator==0)
		{
			if(Local_u8PassTrials>0)
			{
			CLCD_voidGoToXY(0,0);
			CLCD_u8SendString("Enter ID:");
			SSD_u8SetNumber(&Object3,Local_u8PassTrials);
			Local_u8PressedKey=KPD_u8GetPressedKey();
			Local_u8Counter1=0;
			while(Local_u8PressedKey!='e'&&Local_u8EmergencyIndicator==0)
			{
				if(Local_u8PressedKey!=0xff)
				{
					if(KPD_u8GetPressedKey()!=0xff)
					{
						KPD_u8GetPressedKey();
					}
					CLCD_voidSendNumber(Local_u8PressedKey);
					Local_u8IDArr[Local_u8Counter1]=Local_u8PressedKey;
					Local_u8Counter1++;
				}
				Local_u8PressedKey=KPD_u8GetPressedKey();
			}
			if(Local_u8Counter1>0)Local_u8EnteredID=Local_u8IDArr[0];
			for(Local_u8Counter2=1;Local_u8Counter2<Local_u8Counter1;Local_u8Counter2++)
			{
				Local_u8EnteredID=Local_u8EnteredID*10+Local_u8IDArr[Local_u8Counter2];
			}
		CLCD_voidSendComd(1);
		Local_u8Counter1=0;
		CLCD_voidGoToXY(0,0);
		CLCD_u8SendString("Enter Pass:");
		Local_u8PressedKey=KPD_u8GetPressedKey();
		while(Local_u8PressedKey!='e'&&Local_u8EmergencyIndicator==0)
		{
			if(Local_u8PressedKey!=0xff)
			{
				if(KPD_u8GetPressedKey()!=0xff)
				{
					KPD_u8GetPressedKey();
				}
				CLCD_voidSendNumber(Local_u8PressedKey);
				Local_u8PassArr[Local_u8Counter1]=Local_u8PressedKey;
				Local_u8Counter1++;
			}
			Local_u8PressedKey=KPD_u8GetPressedKey();
		}
		if(Local_u8Counter1>0)Local_u8EnteredPass=Local_u8PassArr[0];
		for(Local_u8Counter2=1;Local_u8Counter2<Local_u8Counter1;Local_u8Counter2++)
		{
			Local_u8EnteredPass=Local_u8EnteredPass*10+Local_u8PassArr[Local_u8Counter2];
		}
		CLCD_voidSendComd(1);
		if(Local_u8EnteredPass==Local_u32RealPass&&Local_u8EnteredID==Local_u32RealID)
		{
			 Local_u8PassTrials=TRIALS;
			while(Local_u8EmergencyIndicator==0)
			{
			Local_ArrCounter=0;
			Local_u8Counter=0;
			Local_u8Stepperangle=0;
			CLCD_voidGoToXY(0,0);
			CLCD_u8SendString("1->DC MOTOR");
			CLCD_voidGoToXY(0,1);
			CLCD_u8SendString("2->STEPPER MOTOR");
			Local_u8PressedKey=KPD_u8GetPressedKey();
			if(Local_u8PressedKey!=0xff)
			{
				CLCD_voidSendComd(1);
				while(KPD_u8GetPressedKey()!=0xff);
				if(Local_u8PressedKey==1)
				{
					Local_u8DCMIndicator=1;
					Local_u8StepperIndicator=0;
				}
				else if(Local_u8PressedKey==2)
				{
					Local_u8DCMIndicator=0;
					Local_u8StepperIndicator=1;
				}
				else if(Local_u8PressedKey==3)
				{
					Local_u8DCMIndicator=0;
					Local_u8StepperIndicator=0;
				}
				while(Local_u8DCMIndicator==1&&Local_u8EmergencyIndicator==0)
				{
					CLCD_voidGoToXY(0,0);
					if(Local_u8Counter==0)
					{
					CLCD_u8SendString("1->CW");
					CLCD_voidGoToXY(0,1);
					CLCD_u8SendString("2->CCW");
					Local_u8Counter++;
					}
					Local_u8PressedKey=KPD_u8GetPressedKey();
					if(Local_u8PressedKey!=0xff)
					{
						while(KPD_u8GetPressedKey()!=0xff);
						if(Local_u8PressedKey==1)
						{
							DCM_u8RotateRight(&Object1);
							CLCD_voidSendComd(1);
							CLCD_voidGoToXY(0,0);
							CLCD_u8SendString("DC MOTOR CW ON!");
							CLCD_voidGoToXY(0,1);
							CLCD_u8SendString("2->CCW,3->Stop");
						}
						else if(Local_u8PressedKey==2)
						{
							DCM_u8RotateLeft(&Object1);
							CLCD_voidSendComd(1);
							CLCD_voidGoToXY(0,0);
							CLCD_u8SendString("DC MOTOR CCW ON!");
							CLCD_voidGoToXY(0,1);
							CLCD_u8SendString("1->CW,3->Stop");
						}
						else if(Local_u8PressedKey==3)
						{
							DCM_u8Stop(&Object1);
							Local_u8DCMIndicator=0;
							CLCD_voidSendComd(1);
						}


					}

				}
				while(Local_u8StepperIndicator==1&&Local_u8EmergencyIndicator==0)
				{
					CLCD_voidGoToXY(0,0);
					if(Local_u8Counter==0)
					{
					CLCD_u8SendString("1->CW");
					CLCD_voidGoToXY(0,1);
					CLCD_u8SendString("2->CCW");
					Local_u8Counter++;
					}
					Local_u8PressedKey=KPD_u8GetPressedKey();
					if(Local_u8PressedKey!=0xff)
					{
						while(KPD_u8GetPressedKey()!=0xff);
						if(Local_u8PressedKey==1)
						{
							CLCD_voidSendComd(1);
							CLCD_u8SendString("angle=");
							while(Local_u8PressedKey!='e'&&Local_u8EmergencyIndicator==0)
							{
								Local_u8PressedKey=KPD_u8GetPressedKey();
								if(Local_u8PressedKey!=0xff&&Local_u8PressedKey!='e'&&Local_u8EmergencyIndicator==0)
								{
								Local_Arr[Local_ArrCounter]=Local_u8PressedKey;
								CLCD_voidSendNumber(Local_u8PressedKey);
								Local_ArrCounter++;
								}
							}
							Local_u8Stepperangle=Local_Arr[0];
							for(sint8 LoopCounter=1;LoopCounter<Local_ArrCounter;LoopCounter++)
							{
								Local_u8Stepperangle=Local_u8Stepperangle*10+Local_Arr[LoopCounter];
							}
							if(Local_u8EmergencyIndicator==0)
							{
							CLCD_voidSendComd(1);
							CLCD_voidGoToXY(0,0);
							CLCD_u8SendString("Step MOTOR CW!");
							CLCD_voidGoToXY(0,1);
							CLCD_u8SendString("angle=");
							CLCD_voidSendNumber(Local_u8Stepperangle);
							STEPPER_u8Rotate(&Object2,Local_u8Stepperangle,CW);
							CLCD_voidSendComd(1);
							CLCD_voidGoToXY(0,0);
							CLCD_u8SendString("FINISHED!");
							_delay_ms(1000);
							}
							Local_u8StepperIndicator=0;

						}
						else if(Local_u8PressedKey==2)
						{
							CLCD_voidSendComd(1);
							CLCD_u8SendString("angle=");
							while(Local_u8PressedKey!='e'&&Local_u8EmergencyIndicator==0)
							{
								Local_u8PressedKey=KPD_u8GetPressedKey();
								if(Local_u8PressedKey!=0xff&&Local_u8PressedKey!='e')
								{
								Local_Arr[Local_ArrCounter]=Local_u8PressedKey;
								CLCD_voidSendNumber(Local_u8PressedKey);
								Local_ArrCounter++;
								}
							}
							Local_u8Stepperangle=Local_Arr[0];
							for(sint8 LoopCounter=1;(LoopCounter<Local_ArrCounter&&Local_u8EmergencyIndicator==0);LoopCounter++)
							{
								Local_u8Stepperangle=Local_u8Stepperangle*10+Local_Arr[LoopCounter];
							}
							if(Local_u8EmergencyIndicator==0)
							{
							CLCD_voidSendComd(1);
							CLCD_voidGoToXY(0,0);
							CLCD_u8SendString("Step MOTOR CCW!");
							CLCD_voidGoToXY(0,1);
							CLCD_u8SendString("angle=");
							CLCD_voidSendNumber(Local_u8Stepperangle);
							STEPPER_u8Rotate(&Object2,Local_u8Stepperangle,CCW);
							CLCD_voidSendComd(1);
							CLCD_voidGoToXY(0,0);
							CLCD_u8SendString("FINISHED!");
							_delay_ms(1000);
							}
						Local_u8StepperIndicator=0;
						}
						else if(Local_u8PressedKey==3)
						{
							Local_u8StepperIndicator=0;
							CLCD_voidSendComd(1);
						}

					}

				}
				}
		}
			CLCD_voidSendComd(1);
		}

		else if(Local_u8EmergencyIndicator==0)
		{
			CLCD_u8SendString("Wrong ID or Pass");
			_delay_ms(1000);
			Local_u8PassTrials--;
			CLCD_voidSendComd(1);
		}
		CLCD_voidSendComd(1);
			}
			else if(Local_u8PassTrials==0)
			{
				SSD_u8SetNumber(&Object3,Local_u8PassTrials);
				CLCD_u8SendString("System Blocked!");
				Local_u8PassTrials--;
			}
	}
	}
}
void EmergencyStop(void)
{
	Local_u8EmergencyIndicator=1;
	DCM_u8Stop(&Object1);
}
