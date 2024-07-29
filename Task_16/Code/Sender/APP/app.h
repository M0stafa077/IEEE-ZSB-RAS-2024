/*
 * app.h
 *
 * Created: 6/30/2024 6:55:55 PM
 *  Author: Mostafa Asaad
 */ 


#ifndef APP_H_
#define APP_H_

/* --------------- Section : Includes --------------- */
#include "../ECUAL/ecu_layer_init.h"
#include "../MCAL/mcal_init.h"
#include "../MCAL/ADC/adc.h"
#include "../MCAL/Timer1/timer1.h"
#include "../MCAL/UART/uart.h"
/* --------------- Section: Macro Declarations --------------- */


/* --------------- Section: Extern Objects --------------- */


/*---------------  Section: Function Declarations --------------- */
Std_ReturnType app_init(void);
void timer_callBack(void);

#endif /* APP_H_ */