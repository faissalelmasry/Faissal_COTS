/*
 * GIE_prog.c
 *
 *  Created on: Aug 16, 2024
 *      Author: Acer
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GIE_reg.h"
#include "GIE_interface.h"

void GIE_voidEnableGlobal(void)
{
	__asm  __volatile("SEI");
}

void GIE_voidDisableGlobal(void)
{
	__asm  __volatile("CLI");
}
