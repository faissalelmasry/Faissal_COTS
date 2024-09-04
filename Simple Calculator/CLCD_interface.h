/*******************************************************/
/*******************************************************/
/**********      Author: Faissal Mahmoud      **********/  
/**********      File: CLCD_interface.h       **********/
/**********      Version: 1.00                **********/
/*******************************************************/
/*******************************************************/


#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendComd(uint8 Copy_Cmd);

void CLCD_voidSendData(uint8 Copy_Data);

void CLCD_voidInit(void);

uint8 CLCD_u8SendString(char Copy_chstring[]);

void CLCD_voidSendNumber(sint32 Copy_u32Number);

void CLCD_voidGoToXY(uint8 Copy_u8XPos,uint8 Copy_u8YPos);

void CLCD_voidSendSpecialCharacter(uint8 Copy_u8Pattern[],uint8 Copy_u8PatternNum,uint8 Copy_u8XPos,uint8 Copy_u8YPos);

#endif
