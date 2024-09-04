/*******************************************************/
/*******************************************************/
/**********      Author: Faissal Mahmoud      **********/
/**********      File: CLCD_prv.h             **********/
/**********      Version: 1.00                **********/
/*******************************************************/
/*******************************************************/

#ifndef CLCD_PRV_H_
#define CLCD_PRV_H_

#define EIGHT_BIT_MODE 1u
#define FOUR_BIT_MODE 0u

#define ENABLED 1u
#define DISABLED 0u

static void voidSendEnablePulse(void);
static void voidSetLCDHalfDataPort(uint8 Copy_u8Nipple);

#endif
