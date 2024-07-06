/* 
 * File:   mcal_init.c
 * Author: Mostafa_Asaad
 *
 * Created on December 8, 2023
 */

/* --------------- Section : Includes --------------- */
#include "mcal_init.h"

/*---------------  Section: Global Variables Definition --------------- */
EXTI_t reset_button = { reset_isr, EXTI_INT0, RISING_EDGE };
	
/*---------------  Section: Function Definition --------------- */
Std_ReturnType mcal_initialize(void)
{
	Std_ReturnType ret = E_OK;
	ret |= EXTI_init(&reset_button);
	return ret;
}

void reset_isr(void)
{
	reset_flag = 1;
}
