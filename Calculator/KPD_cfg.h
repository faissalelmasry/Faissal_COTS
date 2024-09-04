/*******************************************************/
/*******************************************************/
/**********      Author: Faissal Mahmoud      **********/
/**********      File: KPD_cfg.h        	  **********/
/**********      Version: 1.00                **********/
/*******************************************************/
/*******************************************************/
#ifndef KPD_CFG_H_
#define KPD_CFG_H_

/*define the number of rows and cols */
#define KPD_ROWS_NUM 4u
#define KPD_COLS_NUM 4u


/*configure keypad port,options:1-DIO_u8PORTA
 *                              2-DIO_u8PORTB
 *                              3-DIO_u8PORTC
 *                              4-DIO_u8PORTD
 */
#define KPD_u8PORT      DIO_u8PORTA

/*configure keypad pins,options:1-DIO_u8PIN0
 *                              2-DIO_u8PIN1
 *                              3-DIO_u8PIN2
 *                              4-DIO_u8PIN3
 *                              5-DIO_u8PIN4
 *                              6-DIO_u8PIN5
 *                              7-DIO_u8PIN6
 *                              8-DIO_u8PIN7
 */
#define KPD_u8ROW1_PIN      DIO_u8PIN0
#define KPD_u8ROW2_PIN      DIO_u8PIN1
#define KPD_u8ROW3_PIN      DIO_u8PIN2
#define KPD_u8ROW4_PIN      DIO_u8PIN3
#define KPD_u8COL1_PIN      DIO_u8PIN4
#define KPD_u8COL2_PIN      DIO_u8PIN5
#define KPD_u8COL3_PIN      DIO_u8PIN6
#define KPD_u8COL4_PIN      DIO_u8PIN7

/*configure keypad button values*/
#define KPD_u8BUTTON_ARR	    {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'.','0','=','+'}}

#define KPD_u8NO_PRESSED_KEY_VAL   0xff

#endif
