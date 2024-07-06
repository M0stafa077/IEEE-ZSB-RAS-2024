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

/*---------------  Section: External Global Variables --------------- */
extern uint8_t message[];
extern uint8_t new_op_flag;
/*---------------  Section: Function Declarations --------------- */
Std_ReturnType ecu_layer_initialize(void);
void display_result(int result);
void display_message(const char *message);

#endif /* ECU_LAYER_INIT_H_ */