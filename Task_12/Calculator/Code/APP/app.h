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
/* --------------- Section: Macro Declarations --------------- */
#ifndef F_CPU
#define F_CPU				1000000U
#include "util/delay.h"
#endif

/* --------------- Section: Extern Objects --------------- */
extern lcd_4bit_t lcd;
extern keypad_t keypad;
extern EXTI_t reset_button;
/*---------------  Section: Function Declarations --------------- */
Std_ReturnType app_init(void);
/*---------------  Section: Helper Functions Declarations --------------- */
void handle_input(void);
void calculate_result(int operand1, int operand2, char operator);
void reset(void);

#endif /* APP_H_ */