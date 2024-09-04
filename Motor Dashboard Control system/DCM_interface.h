

#ifndef DCM_INTRFACE_H_
#define DCM_INTERFACE_H_

typedef struct
{
	uint8 Port;
	uint8 Pin1_4;
	uint8 Pin2_3;

}DCM_t;

uint8 DCM_u8RotateRight(const DCM_t* Object);

uint8 DCM_u8RotateLeft(const DCM_t* Object);

uint8 DCM_u8Stop(const DCM_t* Object);



#endif
