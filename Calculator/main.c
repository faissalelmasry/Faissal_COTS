#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"


void main(void)
{
	uint8 Local_u8PressedKey;
	PORT_voidInit();
	CLCD_voidInit();
	uint8 Local_Num1Arr[16];
	uint8 Local_Arr1Counter=0;
	sint32 Local_Num1;
	sint8 Local_Loop1Counter;
	uint32 Local_Num1Unit=1;
	uint8 Local_Num2Arr[16];
	uint8 Local_Arr2Counter=0;
	sint32 Local_Num2;
	sint8 Local_Loop2Counter;
	uint32 Local_Num2Unit=1;
	uint8 Local_Operator='0';
	uint8 Local_CalcOperator;
	sint32 Local_Res;
	sint32 Local_Remainder;
	uint8 Local_FloatIndicator1=0;
	uint8 Local_FloatIndicator2=0;
	uint16 Local_FloatCounter1=1;
	uint16 Local_FloatCounter2=1;


	while(1)
	{
		while(Local_Operator!='=')
		{
		Local_u8PressedKey=KPD_u8GetPressedKey();
		if(Local_u8PressedKey!=0xff)
		{
			CLCD_voidSendData(Local_u8PressedKey);
			if(Local_u8PressedKey>='0'&&Local_u8PressedKey<='9'&&Local_Operator=='0')
			{
				if(Local_FloatIndicator1==1)Local_FloatCounter1=Local_FloatCounter1*10;
				Local_Num1Arr[Local_Arr1Counter]=Local_u8PressedKey-'0';
				Local_Arr1Counter++;
			}
			else if(Local_u8PressedKey>='0'&&Local_u8PressedKey<='9'&&Local_Operator!='0')
			{
				if(Local_FloatIndicator2==1)Local_FloatCounter2=Local_FloatCounter2*10;
				Local_Num2Arr[Local_Arr2Counter]=Local_u8PressedKey-'0';
				Local_Arr2Counter++;
			}
			else if(Local_u8PressedKey=='.'&&Local_Operator=='0')
			{
				Local_FloatIndicator1=1;
			}
			else if(Local_u8PressedKey=='.'&&Local_Operator!='0')
			{
				Local_FloatIndicator2=1;
			}
			else
			{
				 Local_Operator=Local_u8PressedKey;
				 if(Local_Operator!='=')
				 {
					 Local_CalcOperator=Local_Operator;
				 }
			}
		}
		}

			if(Local_Operator=='=')
			{
				Local_Num1=0;
				Local_Num2=0;
				for(Local_Loop1Counter=Local_Arr1Counter-1;Local_Loop1Counter>=0;Local_Loop1Counter--)
				{
					Local_Num1=Local_Num1+Local_Num1Arr[Local_Loop1Counter]*Local_Num1Unit;
					Local_Num1Unit=Local_Num1Unit*10;
				}
				for(Local_Loop2Counter=Local_Arr2Counter-1;Local_Loop2Counter>=0;Local_Loop2Counter--)
				{
					Local_Num2=Local_Num2+Local_Num2Arr[Local_Loop2Counter]*Local_Num2Unit;
					Local_Num2Unit=Local_Num2Unit*10;;
				}
				switch(Local_CalcOperator)
				{
				case '+':if(Local_FloatIndicator1==0&&Local_FloatIndicator2==0)
						{
							Local_Res=Local_Num1+Local_Num2;
							CLCD_voidSendNumber(Local_Res);
						}
						else
						{
							Local_Res=(Local_Num1/Local_FloatCounter1)+(Local_Num2/Local_FloatCounter2);
							if(Local_FloatCounter1==10)
								{
									Local_FloatCounter1*=10;
									Local_Num1*=10;
								}
							if(Local_FloatCounter2==10)
							{
								Local_FloatCounter2*=10;
								Local_Num2*=10;
							}
							Local_Remainder=(Local_Num1%Local_FloatCounter1)+(Local_Num2%Local_FloatCounter2);

				if(Local_Remainder>=110)
				{
					CLCD_voidSendNumber(Local_Res+1);
					CLCD_voidSendData('.');
					CLCD_voidSendNumber(Local_Remainder-100);
				}
				else if(Local_Remainder<110&&Local_Remainder>=100)
				{
					CLCD_voidSendNumber(Local_Res+1);
					CLCD_voidSendData('.');
					CLCD_voidSendData('0');
					CLCD_voidSendNumber(Local_Remainder-100);
				}
				else if(Local_Remainder<10)
				{
					CLCD_voidSendNumber(Local_Res);
					CLCD_voidSendData('.');
					CLCD_voidSendData('0');
					CLCD_voidSendNumber(Local_Remainder);
				}
				else
				{
					CLCD_voidSendNumber(Local_Res);
					CLCD_voidSendData('.');
					CLCD_voidSendNumber(Local_Remainder);
				}
						}
						 break;
				case '-':if(Local_FloatIndicator1==0&&Local_FloatIndicator2==0)
				{
					Local_Res=Local_Num1-Local_Num2;
					CLCD_voidSendNumber(Local_Res);
				}
				else
				{
					Local_Res=(Local_Num1/Local_FloatCounter1)-(Local_Num2/Local_FloatCounter2);
					if(Local_FloatCounter1==10)
						{
							Local_FloatCounter1*=10;
							Local_Num1*=10;
						}
					if(Local_FloatCounter2==10)
					{
						Local_FloatCounter2*=10;
						Local_Num2*=10;
					}
					Local_Remainder=(Local_Num1%Local_FloatCounter1)-(Local_Num2%Local_FloatCounter2);

		if(Local_Remainder<=-10&&Local_Res==0)
		{
			CLCD_voidSendData('-');
			CLCD_voidSendNumber(Local_Res);
			CLCD_voidSendData('.');
			CLCD_voidSendNumber(-Local_Remainder);
		}
		else if(Local_Remainder<=-10&&Local_Res<0)
		{
			CLCD_voidSendNumber(Local_Res);
			CLCD_voidSendData('.');
			CLCD_voidSendNumber(-Local_Remainder);
		}
		else if(Local_Remainder>=90&&Local_Remainder<100&&Local_Res<0)
		{
			CLCD_voidSendNumber(Local_Res+1);
			CLCD_voidSendData('.');
			CLCD_voidSendData('0');
			CLCD_voidSendNumber(100-Local_Remainder);
		}
		else if(Local_Remainder>0&&Local_Remainder<90&&Local_Res<0)
		{
			CLCD_voidSendNumber(Local_Res+1);
			CLCD_voidSendData('.');
			CLCD_voidSendNumber(100-Local_Remainder);
		}
		else if(Local_Remainder<=-10)
		{
			CLCD_voidSendNumber(Local_Res-1);
			CLCD_voidSendData('.');
			CLCD_voidSendNumber(Local_Remainder+100);
		}
		else if(Local_Remainder<10&&Local_Remainder>=0)
		{
			CLCD_voidSendNumber(Local_Res);
			CLCD_voidSendData('.');
			CLCD_voidSendData('0');
			CLCD_voidSendNumber(Local_Remainder);
		}
		else if(Local_Remainder<0&&Local_Remainder>-10&&Local_Res==0)
		{
			CLCD_voidSendData('-');
			CLCD_voidSendNumber(Local_Res);
			CLCD_voidSendData('.');
			CLCD_voidSendData('0');
			CLCD_voidSendNumber(-Local_Remainder);
		}
		else if(Local_Remainder<0&&Local_Remainder>-10)
		{
			CLCD_voidSendNumber(Local_Res);
			CLCD_voidSendData('.');
			CLCD_voidSendData('0');
			CLCD_voidSendNumber(-Local_Remainder);
		}
		else
		{
			CLCD_voidSendNumber(Local_Res);
			CLCD_voidSendData('.');
			CLCD_voidSendNumber(Local_Remainder);
		}
				}

				 break;
				case '*':if(Local_FloatIndicator1==0&&Local_FloatIndicator2==0)
						{
							Local_Res=Local_Num1*Local_Num2;
							CLCD_voidSendNumber(Local_Res);
						}
						else
						{

						}
						break;
				case '/':if(Local_Num2==0)
						{
						   CLCD_u8SendString("undefined");
						}
						 else
						 {
							 Local_Res=(Local_Num1)/Local_Num2;
							 CLCD_voidSendNumber(Local_Res);
							 CLCD_voidSendData('.');
							 Local_Res=((Local_Num1*100)/Local_Num2)%100;
							 CLCD_voidSendNumber(Local_Res);
						 }
						 break;
				}
				while(KPD_u8GetPressedKey()==0xff);
			}
			CLCD_voidSendComd(1);
			Local_Operator='0';
			Local_Arr1Counter=0;
			Local_Num1Unit=1;
			Local_Arr2Counter=0;
			Local_Num2Unit=1;
			Local_FloatIndicator1=0;
			Local_FloatIndicator2=0;
			Local_FloatCounter1=1;
			Local_FloatCounter2=1;

	}
}

