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
#include "../MCAL/Timer0/timer0.h"
#include "../MCAL/Timer1/timer1.h"
#include "../MCAL/UART/uart.h"
#include "../MCAL/SPI/spi.h"
/* --------------- Section: Macro Declarations --------------- */


/* --------------- Section: Extern Objects --------------- */
extern lcd_4bit_t lcd;
/*---------------  Section: Function Declarations --------------- */
Std_ReturnType app_init(void);
void TC72_Send_Command(char spiData);
char TC72_Read(void);
void TC72_Init(void);
uint16_t Get_Temperature(void);

#endif /* APP_H_ */