/*
 * servo_motor.h
 *
 * Created: 7/26/2024 6:49:19 PM
 *  Author: Mostafa Asaad
 */ 


#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_

/* --------------- Section : Includes --------------- */
#include "../../MCAL/Timer1/timer1.h"
#include "../../MCAL/gpio/gpio.h"
/* --------------- Section: Macro Declarations --------------- */

/* --------------- Section: Macro Functions Declarations --------------- */

/* --------------- Section: Data Type Declarations --------------- */
typedef enum
{
	OC1A,
	OC1B
} ServoMotor_Pin_t;
/*---------------  Section: Function Declarations --------------- */
Std_ReturnType ServoMotor_Init(ServoMotor_Pin_t pin);
Std_ReturnType ServoMotor_DeInit(ServoMotor_Pin_t pin);
Std_ReturnType ServoMotor_SetAngle(uint8_t Servo_Angle);

#endif /* SERVO_MOTOR_H_ */