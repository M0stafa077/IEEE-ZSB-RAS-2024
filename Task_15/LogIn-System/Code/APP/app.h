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
extern const uint8_t buttons_values[3][3];
extern keypad_t keypad;
extern lcd_4bit_t lcd;

/*---------------  Section: Function Declarations --------------- */
Std_ReturnType app_init(void);
void LogIn();
void EXTI_INT0_ISR();
void EXTI_INT1_ISR();
void EXTI_INT2_ISR();

#endif /* APP_H_ */