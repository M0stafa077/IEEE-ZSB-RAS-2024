/*
 * timer1.h
 *
 * Created: 7/25/2024 11:33:18 PM
 *  Author: Mostafa Asaad
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

/* --------------- Section : Includes --------------- */
#include "../Interrupts/INTI/MCAL_INTI.h"
#include "../registers.h"
/* --------------- Section: Macro Declarations --------------- */

/* --------------- Section: Macro Functions Declarations --------------- */
#define TMR1_SET_DISABLE()				(TCCR1Bbits.CS1 = (uint8_t)(0x00))
#define TMR1_SET_CLK_SRC(SRC)			(TCCR1Bbits.CS1 = (uint8_t)SRC)
/* --------------- Section: Data Type Declarations --------------- */
typedef enum
{
	TIMER1_NORMAL_MODE = 0,
	
	TIMER1_PWM_PHASE_CORRECT_8bit_MODE,
	TIMER1_PWM_PHASE_CORRECT_9bit_MODE,
	TIMER1_PWM_PHASE_CORRECT_10bit_MODE,
	
	TIMER1_CTC_OCR1A_TOP_MODE,
	
	TIMER1_FAST_PWM_8BITS_MODE,
	TIMER1_FAST_PWM_9BITS_MODE,
	TIMER1_FAST_PWM_10BITS_MODE,
	
	TIMER1_PHASE_FRQ_CORRECT_ICR1_TOP_MODE,
	TIMER1_PHASE_FRQ_CORRECT_OCR1A_TOP_MODE,
	TIMER1_PHASE_CORRECT_ICR1_TOP_MODE,
	TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE,
	
	TIMER1_CTC_ICR1_TOP_MODE,
	
	TIMER1_FAST_PWM_ICR1_TOP_MODE = 14,
	TIMER1_FAST_PWM_OCR1A_TOP_MODE
} Timer1_mode_t;

typedef enum
{
	TMR1_NON_PWM_NORMAL_PORT_OPERATION,
	TMR1_TOGGLE_ON_MATCH,
	TMR1_CLEAR_ON_MATCH,
	TMR1_SET_ON_MATCH
} OC1_Behavior_Non_PWM_t;

typedef enum
{
	TMR1_FAST_PWM_NORMAL_PORT_OPERATION,
	TMR1_CLR_ON_MATCH_SET_AT_BOTTOM = 2,
	TMR1_SET_ON_MATCH_CLR_AT_BOTTOM
} OC1_Behavior_Fast_PWM_t;

typedef enum
{
	TMR1_PHASE_CORRECT_NORMAL_PORT_OPERATION,
	TMR1_CLR_UP_COUNT_SET_DOWN_COUNT = 2,
	TMR1_SET_UP_COUNT_CLR_DOWN_COUNT
} OC1_Behavior_PhaseCorrect_PWM_t;

typedef uint8_t OC1_Behavior_t;

typedef enum
{
	TMR1_NO_CLOCK,
	TMR1_PRESCALER_1,
	TMR1_PRESCALER_8,
	TMR1_PRESCALER_64,
	TMR1_PRESCALER_256,
	TMR1_PRESCALER_1024,
	TMR1_EXT_FALLING_EDGE,
	TMR1_EXT_RISING_EDGE
} Timer1_Clock_Select_t;

typedef struct
{
	/* !< Timer 1 Module Interrupt-Service-Routine */
	interrupt_handler_t timer1_isr;
	/* !< Timer 1 Module Mode. @ref: Timer1_mode_t */
	Timer1_mode_t timer_mode;
	/* !< Timer 1 Module oc1a pin behavior on compare match. @ref: OC1_Behavior_t */
	OC1_Behavior_t oc1A_pin_behavior;
	/* !< Timer 1 Module oc1b pin behavior on compare match. @ref: OC1_Behavior_t */
	OC1_Behavior_t oc1B_pin_behavior;
	/* !< Timer 1 Module clock source. @ref: Timer1_Clock_Select_t */
	Timer1_Clock_Select_t timer1_clk_src;
	/* !< Timer 1 Module Counter Register pre-loaded value */
	uint16_t timer1_preload_value;
	/* !< Timer 1 Module OCR1A Register pre-loaded value */
	uint16_t timer1_ocra_value;
	/* !< Timer 1 Module OCR1B Register pre-loaded value */
	uint16_t timer1_ocrb_value;
} Timer1_Configurations_t;
/*---------------  Section: Function Declarations --------------- */
Std_ReturnType Timer1_Init(const Timer1_Configurations_t * timer_cfgs);
Std_ReturnType Timer1_DeInit(const Timer1_Configurations_t * timer_cfgs);
Std_ReturnType Timer1_Write_Value(const Timer1_Configurations_t * timer_cfgs, uint16_t TCNT_Preload_Value);
Std_ReturnType Timer1_ReadValue(const Timer1_Configurations_t * timer_cfgs, uint8_t * TCNT_Value);
Std_ReturnType Timer1_WriteOCRAValue(const Timer1_Configurations_t * timer_cfgs, uint8_t OCRA_Value);
Std_ReturnType Timer1_WriteOCRBValue(const Timer1_Configurations_t * timer_cfgs, uint8_t OCRA_Value);
Std_ReturnType Timer1_PWM_Set_DutyCycle(const Timer1_Configurations_t * timer_cfgs, uint8_t dutyCycle);


#endif /* TIMER1_H_ */