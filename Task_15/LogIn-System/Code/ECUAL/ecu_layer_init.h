/* 
 * File:   ecu_layer_init.h
 * Author: Mostafa_Asaad
 *
 * Created on December 8, 2023, 11:47 PM
 */


#ifndef ECU_LAYER_INIT_H_
#define ECU_LAYER_INIT_H_

/* --------------- Section : Includes --------------- */
#include "../ECUAL/lcd/lcd.h"
#include "../ECUAL/keypad/keypad.h"
#include "Servo_Motor/servo_motor.h"

/*---------------  Section: External Global Variables --------------- */

/*---------------  Section: Function Declarations --------------- */
Std_ReturnType ecu_layer_initialize(void);


#endif /* ECU_LAYER_INIT_H_ */