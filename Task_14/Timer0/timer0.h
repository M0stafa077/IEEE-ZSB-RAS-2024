/*
 * timer0.h
 *
 * Created: 7/21/2024 7:49:15 PM
 *  Author: Mostafa Asaad
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_
/* --------------- Section : Includes --------------- */
#include "../Interrupts/INTI/MCAL_INTI.h"
#include "../registers.h"
/* --------------- Section: Macro Declarations --------------- */

/* --------------- Section: Macro Functions Declarations --------------- */
#define TMR0_SET_DISABLE()				(TCCR0bits.CS0 = (uint8_t)TMR0_NO_CLOCK)
#define TMR0_SET_CLK_SRC(SRC)			(TCCR0bits.CS0 = (uint8_t)SRC)
/* --------------- Section: Data Type Declarations --------------- */
typedef enum 
{
	TIMER0_NORMAL_MODE = 0,		/* !< The simplest mode of operation is the normal mode */
	TIMER0_PWM_PHASE_CORRECT_MODE = 1,
	TIMER0_CTC_MODE = 2,		/* !< In CTC mode, the counter is cleared when the TCNT0 value matches the OCR0 */
	TIMER0_FAST_PWM_MODE = 3	/* !< The Fast PWM mode provides a high frequency PWM waveform generation option. */
} Timer0_mode_t;

typedef enum
{
	NON_PWM_NORMAL_PORT_OPERATION,
	TOGGLE_ON_MATCH,
	CLEAR_ON_MATCH,
	SET_ON_MATCH
} OC0_Behavior_Non_PWM_t;

typedef enum
{
	FAST_PWM_NORMAL_PORT_OPERATION,
	CLR_ON_MATCH_SET_AT_BOTTOM = 2,
	SET_ON_MATCH_CLR_AT_BOTTOM
} OC0_Behavior_Fast_PWM_t;

typedef enum
{
	PHASE_CORRECT_NORMAL_PORT_OPERATION,
	CLR_UP_COUNT_SET_DOWN_COUNT = 2,
	SET_UP_COUNT_CLR_DOWN_COUNT
} OC0_Behavior_PhaseCorrect_PWM_t;

typedef uint8_t OC0_Behavior_t;

typedef enum
{
	TMR0_NO_CLOCK,
	TMR0_PRESCALER_1,
	TMR0_PRESCALER_8,
	TMR0_PRESCALER_64,
	TMR0_PRESCALER_256,
	TMR0_PRESCALER_1024,
	TMR0_EXT_FALLING_EDGE,
	TMR0_EXT_RISING_EDGE
} Timer0_Clock_Select_t;

typedef struct
{
	/* !< Timer 0 Module Interrupt-Service-Routine */
	interrupt_handler_t timer0_isr;
	/* !< Timer 0 Module Mode. @ref: Timer0_mode_t */
	Timer0_mode_t timer_mode;
	/* !< Timer 0 Module oc0 pin behavior on compare match. @ref: OC0_Behavior_t */
	OC0_Behavior_t oc0_pin_behavior;
	/* !< Timer 0 Module clock source. @ref: Timer0_Clock_Select_t */
	Timer0_Clock_Select_t timer0_clk_src;
	/* !< Timer 0 Module Counter Register pre-loaded value */
	uint8_t timer0_preload_value;
	/* !< Timer 0 Module OCR0 Register pre-loaded value */
	uint8_t timer0_ocr_value;
} Timer0_Configurations_t;
/*---------------  Section: Function Declarations --------------- */

/**
 * @brief: A Software Interface initializes Timer 0.
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_Init(const Timer0_Configurations_t * tmr0_cfg);
/**
 * @brief: A Software De-Interface initializes Timer 0.
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_DeInit(const Timer0_Configurations_t * tmr0_cfg);
/**
 * @brief : A software interface writes a value to the timer 0 register.
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @param tcnt_value : The value to be written into the timer 0 register.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_WriteValue(const Timer0_Configurations_t * tmr0_cfg, uint8_t tcnt_value);
/**
 * @brief : A software interface Reads the content of the timer 0 module register.
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @param tcnt_value : The variable in which the read value will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_ReadValue(const Timer0_Configurations_t * tmr0_cfg, uint8_t * tcnt_value);
/**
 * @brief : A software interface writes a value to the timer 0 compare register.
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @param tcnt_value : The value to be written into the timer 0 compare register.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_WriteOCRValue(const Timer0_Configurations_t * tmr0_cfg, uint8_t ocr_value);
/**
 * @brief : A software interface sets the dutyCycle of the timer 0 output on OC0 pin.
 * @note  : This API only works in pwm mode, it returns E_NOT_OK instead
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @param dutyCycle : The Duty Cycle (0 =< dutyCycle =< 100).
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_PWM_Set_DutyCycle(const Timer0_Configurations_t * tmr0_cfg, uint8_t dutyCycle);

#endif /* TIMER0_H_ */