/*
 * app.h
 *
 * Created: 6/30/2024 6:55:55 PM
 *  Author: Mostafa Asaad
 */ 


#ifndef APP_H_
#define APP_H_

#include "../ECUAL/seven_segment/seven_segment.h"
#include "../ECUAL/led/led.h"
#include "../MCAL/gpio/gpio.h"

#define F_CPU				1000000U
#include "util/delay.h"

#define DISPLAY_REFRESH_INTERVAL	10
#define ONE_SECOND_DELAY			1000

Std_ReturnType app_init(void);

#endif /* APP_H_ */