/*******************************************************/
/*******************************************************/
/**********      Author: Faissal Mahmoud      **********/  
/**********      File: KPD_prog.c	          **********/ 
/**********      Version: 1.00                **********/ 
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "KPD_cfg.h"
#include "KPD_interface.h"
#include "KPD_prv.h"


/*required all row pins are input pulledup and cols pins are output high*/
uint8 KPD_u8GetPressedKey(void)
{
	uint8 Local_u8PressedKey=KPD_u8NO_PRESSED_KEY_VAL;
	uint8 Local_u8RowCouter;
	uint8 Local_u8ColCouter;
	uint8 Local_u8KeyState;
	static uint8 Local_u8ColArr[KPD_COLS_NUM]={KPD_u8COL1_PIN,KPD_u8COL2_PIN,KPD_u8COL3_PIN,KPD_u8COL4_PIN};
	static uint8 Local_u8RowArr[KPD_ROWS_NUM]={KPD_u8ROW1_PIN,KPD_u8ROW2_PIN,KPD_u8ROW3_PIN,KPD_u8ROW4_PIN};
	static uint8 Local_u8KPDArr[KPD_ROWS_NUM][KPD_COLS_NUM]=KPD_u8BUTTON_ARR;
	for(Local_u8ColCouter=0;Local_u8ColCouter<KPD_COLS_NUM;Local_u8ColCouter++)
	{
		DIO_u8SetPinValue(KPD_u8PORT,Local_u8ColArr[Local_u8ColCouter],DIO_u8PIN_LOW);
		for(Local_u8RowCouter=0;Local_u8RowCouter<KPD_ROWS_NUM;Local_u8RowCouter++)
		{
			DIO_u8GetPinValue(KPD_u8PORT,Local_u8RowArr[Local_u8RowCouter],&Local_u8KeyState);
			if(Local_u8KeyState==DIO_u8PIN_LOW)
			{
				Local_u8PressedKey=Local_u8KPDArr[Local_u8RowCouter][Local_u8ColCouter];
				/*wait until the key is released*/
				while(Local_u8KeyState==DIO_u8PIN_LOW)
				{
					DIO_u8GetPinValue(KPD_u8PORT,Local_u8RowArr[Local_u8RowCouter],&Local_u8KeyState);
				}
				return Local_u8PressedKey;
			}
		}
		DIO_u8SetPinValue(KPD_u8PORT,Local_u8ColArr[Local_u8ColCouter],DIO_u8PIN_HIGH);
	}
	return Local_u8PressedKey;
}
