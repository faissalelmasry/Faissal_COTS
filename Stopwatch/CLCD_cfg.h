/*******************************************************/
/*******************************************************/
/**********      Author: Faissal Mahmoud      **********/
/**********      File: CLCD_cfg.h             **********/
/**********      Version: 1.00                **********/
/*******************************************************/
/*******************************************************/

#ifndef CLCD_CFG_H_
#define CLCD_CFG_H_

/*please choose which port to be connected to ctrl pins:RS,RW,E
 *options:DIO_u8PORTA
 *		  DIO_u8PORTB
 *		  DIO_u8PORTC
 *		  DIO_u8PORTD
 */

#define CLCD_CTRL_PORT DIO_u8PORTC

/*please choose which pin to be connected to ctrl pin:RS
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_RS_PIN DIO_u8PIN0

#define CLCD_RW_CTRL_EN ENABLED

#if CLCD_RW_CTRL_EN==ENABLED

/*please choose which pin to be connected to ctrl pin if enabled:RW
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_RW_PIN DIO_u8PIN1
#endif

/*please choose which pin to be connected to ctrl pin:E
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_E_PIN DIO_u8PIN2

/*please choose which port to be connected to data pins:D0,D1,D2,D3,D4,D5,D6,D7
 *options:DIO_u8PORTA
 *		  DIO_u8PORTB
 *		  DIO_u8PORTC
 *		  DIO_u8PORTD
 */

#define CLCD_DATA_PORT DIO_u8PORTB

/*please choose the operation mode:
 *options:EIGHT_BIT_MODE
 *		  FOUR_BIT_MODE
 *
 *
 */

#define CLCD_OP_MODE FOUR_BIT_MODE

#if CLCD_OP_MODE==EIGHT_BIT_MODE

/*please choose which pin to be connected to data pin:D0
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D0_PIN DIO_u8PIN0

/*please choose which pin to be connected to data pin:D1
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D1_PIN DIO_u8PIN1

/*please choose which pin to be connected to data pin:D2
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D2_PIN DIO_u8PIN2

/*please choose which pin to be connected to data pin:D3
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D3_PIN DIO_u8PIN3

/*please choose which pin to be connected to data pin:D4
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D4_PIN DIO_u8PIN4

/*please choose which pin to be connected to data pin:D5
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D5_PIN DIO_u8PIN5

/*please choose which pin to be connected to data pin:D6
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D6_PIN DIO_u8PIN6

/*please choose which pin to be connected to data pin:D7
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D7_PIN DIO_u8PIN7

#endif

#if CLCD_OP_MODE==FOUR_BIT_MODE

/*please choose which pin to be connected to data pin:D4
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D4_PIN DIO_u8PIN4

/*please choose which pin to be connected to data pin:D5
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D5_PIN DIO_u8PIN5

/*please choose which pin to be connected to data pin:D6
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D6_PIN DIO_u8PIN6

/*please choose which pin to be connected to data pin:D7
 *options:DIO_u8PIN0
 *		  DIO_u8PIN1
 *		  DIO_u8PIN2
 *		  DIO_u8PIN3
 *		  DIO_u8PIN4
 *		  DIO_u8PIN5
 *		  DIO_u8PIN6
 *		  DIO_u8PIN7
 */

#define CLCD_D7_PIN DIO_u8PIN7

#endif
#endif
