/*******************************************************/
/*******************************************************/
/**********      Author: Faissal Mahmoud      **********/  
/**********      File: SSD_interface.h        **********/ 
/**********      Version: 1.00                **********/ 
/*******************************************************/
/*******************************************************/
#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define ANODE   0u
#define CATHODE 1u

#define OK 			 0u
#define NOK 		 1u
#define NULL_PTR_ERR 2u

typedef struct
{
	uint8 Type;
	uint8 Port;
	uint8 Pin;
	uint8 EnablePort;
	uint8 EnablePin;

}SSD_t;

uint8 SSD_u8SetNumber(const SSD_t* Copy_SSDObject,uint8 Copy_u8Number);

#endif
