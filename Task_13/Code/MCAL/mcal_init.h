/* 
 * File:   mcal_init.h
 * Author: Mostafa_Asaad
 *
 * Created on December 8, 2023
 */

#ifndef MCAL_INIT_H_
#define MCAL_INIT_H_

/* --------------- Section : Includes --------------- */
#include "Interrupts/EXTI/MCAL_EXTI.h"
#include "Interrupts/INTI/MCAL_INTI.h"
#include "ADC/adc.h"

/*---------------  Section: External Global Variables --------------- */

/*---------------  Section: Function Declarations --------------- */
Std_ReturnType mcal_initialize(void);

#endif /* MCAL_INIT_H_ */