/*
 * app.h
 *
 * Created: 6/30/2024 6:55:55 PM
 *  Author: Mostafa Asaad
 */ 


#ifndef APP_H_
#define APP_H_

/* --------------- Section : Includes --------------- */
#include "../ECUAL/dc_motor/dc_motor.h"
#include "../ECUAL/button/button.h"
#include "../ECUAL/led/led.h"
/* --------------- Section: Macro Declarations --------------- */
#define F_CPU				1000000U
#include "util/delay.h"
/* --------------- Section: Macro Functions Declarations --------------- */

/*---------------  Section: Function Declarations --------------- */
Std_ReturnType app_init(void);

Std_ReturnType move_forward(void);
Std_ReturnType move_right(void);
Std_ReturnType move_backward(void);
Std_ReturnType move_left(void);
Std_ReturnType stop(void);

#endif /* APP_H_ */