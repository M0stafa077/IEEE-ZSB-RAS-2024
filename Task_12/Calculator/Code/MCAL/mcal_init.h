/* 
 * File:   mcal_init.h
 * Author: Mostafa_Asaad
 *
 * Created on December 8, 2023
 */

#ifndef MCAL_INIT_H_
#define MCAL_INIT_H_

/* --------------- Section : Includes --------------- */
#include "../MCAL/Interrupts/EXTI/MCAL_EXTI.h"

/*---------------  Section: External Global Variables --------------- */
extern volatile uint8_t reset_flag;

/*---------------  Section: Function Declarations --------------- */
Std_ReturnType mcal_initialize(void);
void reset_isr(void);

#endif /* MCAL_INIT_H_ */