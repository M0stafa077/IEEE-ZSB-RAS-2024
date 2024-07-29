/*
 * servo_motor.c
 *
 * Created: 7/26/2024 6:49:41 PM
 *  Author: Mostafa Asaad
 */ 
/* --------------- Section : Includes --------------- */
#include "servo_motor.h"
/*---------------  Section: Function Definitions --------------- */
Std_ReturnType ServoMotor_Init(ServoMotor_Pin_t pin)
{
	Std_ReturnType retVal = E_OK;
	Timer1_Configurations_t Timer_Cfgs = 
	{
		NULL,
		TIMER1_FAST_PWM_ICR1_TOP_MODE,
		0,
		0,
		TMR1_PRESCALER_1,		// For 1MHz clock
		0,
		0,
		0
	};
	switch(pin)
	{
		case OC1A:
			Timer_Cfgs.oc1A_pin_behavior = TMR1_CLR_ON_MATCH_SET_AT_BOTTOM;
			Timer_Cfgs.oc1B_pin_behavior = TMR1_FAST_PWM_NORMAL_PORT_OPERATION;
			break;
		case OC1B:
			Timer_Cfgs.oc1B_pin_behavior = TMR1_CLR_ON_MATCH_SET_AT_BOTTOM;
			Timer_Cfgs.oc1A_pin_behavior = TMR1_FAST_PWM_NORMAL_PORT_OPERATION;
			break;
		default:
			retVal |= E_NOT_OK;
			break;
	}
	Timer1_Init(&Timer_Cfgs);
	INTI_TMR1_OF_INTERRUPT_DISABLE();
	INTI_TMR1_OCB_INTERRUPT_DISABLE();
	INTI_TMR1_OCA_INTERRUPT_DISABLE();
	INTI_TMR1_IC_INTERRUPT_DISABLE();
	
	/* !< 20 ms */
	ICR1 = (uint16_t)((F_CPU / 50.0) - 1);
	
}
Std_ReturnType ServoMotor_DeInit(ServoMotor_Pin_t pin)
{
	
}
Std_ReturnType ServoMotor_SetAngle(uint8_t Servo_Angle)
{
	uint32_t pulse_width = 0;
	pulse_width = ((uint32_t)Servo_Angle) * 1000;
	pulse_width = (uint32_t)(pulse_width / 180.0);
	pulse_width = 2000 - pulse_width;
	OCR1A = (uint16_t)((pulse_width) - 1); // Scale to match ICR1 value
}