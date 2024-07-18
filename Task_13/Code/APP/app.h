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
/* --------------- Section: Macro Declarations --------------- */
#ifndef F_CPU
#define F_CPU				1000000U
#include "util/delay.h"
#endif

/* --------------- Section: Extern Objects --------------- */

/*---------------  Section: Helper Functions Declarations --------------- */

/*---------------  Section: Function Declarations --------------- */
Std_ReturnType app_init(void);



#endif /* APP_H_ */