#ifndef STEPPER_INTERFACE_H_
#define STEPPER_INTERFACE_H_

typedef struct
{
	uint8 Port;
	uint8 BluePin;
	uint8 PinkPin;
	uint8 YellowPin;
	uint8 OrangePin;

}STEPPER_t;

#define CCW 0u
#define CW  1u

uint8 STEPPER_u8Rotate(STEPPER_t* Object,uint16 Copy_u16Angle,uint8 Copy_Directon);

#endif
