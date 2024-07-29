/*
 * timer0.c
 *
 * Created: 7/21/2024 7:49:15 PM
 *  Author: Mostafa Asaad
 */ 
/* --------------- Section : Includes --------------- */
#include "timer0.h"
/* --------------- Section: Global Variables --------------- */

/* !< Default interrupt handler for timer 0 module */
static interrupt_handler_t Timer0_Default_Interrupt_Handler = NULL;
/*---------------  Section: Function Definitions --------------- */

/**
 * @brief: A Software Interface initializes Timer 0.
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_Init(const Timer0_Configurations_t * tmr0_cfg)
{
	Std_ReturnType ret = E_OK;
	if(NULL == tmr0_cfg)
		{ ret = E_NOT_OK; }
	else
	{
		/* Disable Timer 0 Module */
		TMR0_SET_DISABLE();
		/* Set the timer 0 module mode */
		switch(tmr0_cfg->timer_mode)
		{
			case TIMER0_NORMAL_MODE: TCCR0bits.WGM01 = 0, TCCR0bits.WGM00 = 0;
								break;
			case TIMER0_PWM_PHASE_CORRECT_MODE: TCCR0bits.WGM01 = 0, TCCR0bits.WGM00 = 1;
								break;
			case TIMER0_CTC_MODE: TCCR0bits.WGM01 = 1, TCCR0bits.WGM00 = 0;
								break;
			case TIMER0_FAST_PWM_MODE: TCCR0bits.WGM01 = 1, TCCR0bits.WGM00 = 1;
								break;
			default: TCCR0bits.WGM01 = 0, TCCR0bits.WGM00 = 0;	/* !< Normal Mode */
								break;
		}
		/* Set the OC0 pin behavior */
		TCCR0bits.COM0 = tmr0_cfg->oc0_pin_behavior;
		if(tmr0_cfg->oc0_pin_behavior)	/* !< Not equal zero, which means not in the normal port operation */
		{
			SET_BIT(DDRB, PIN3_INDEX);
		}
		/* Set the TCNT0 Pre-Loaded Value */
		TCNT0 = tmr0_cfg->timer0_preload_value;
		/* Set the OCR0 Pre-Loaded Value */
		OCR0 = tmr0_cfg->timer0_ocr_value;
		/* Configure Timer 0 Interrupt */
		// 1. Enable Global Interrupts
		INTERRUPT_GI_ENABLE();	
		// 2. Clear the Interrupt Flags
		INTI_TMR0_OC_CLR_FLAG();
		INTI_TMR0_OF_CLR_FLAG();
		// 3. Set the default interrupt handler
		Timer0_Default_Interrupt_Handler = tmr0_cfg->timer0_isr;
		// 4. Enable The Timer 0 Interrupts
		if(TIMER0_NORMAL_MODE == tmr0_cfg->timer_mode)
			{ INTI_TMR0_OF_INTERRUPT_ENABLE(); }
		else
			{ INTI_TMR0_OC_INTERRUPT_ENABLE(); }
		/* Enable Timer 0 Module By Setting the clock source */
		TMR0_SET_CLK_SRC(tmr0_cfg->timer0_clk_src);
	}
	return ret;
}
/**
 * @brief: A Software De-Interface initializes Timer 0.
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_DeInit(const Timer0_Configurations_t * tmr0_cfg)
{
	Std_ReturnType ret = E_OK;
	if(NULL == tmr0_cfg)
		{ ret = E_NOT_OK; }
	else
	{
		/* Disable The Timer 0 Interrupts */
		INTI_TMR0_OC_INTERRUPT_DISABLE();
		INTI_TMR0_OF_INTERRUPT_DISABLE();
		/* Disable The Timer 0 Module */
		TMR0_SET_DISABLE();
	}
	return ret;
}
/**
 * @brief : A software interface writes a value to the timer 0 register.
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @param tcnt_value : The value to be written into the timer 0 register.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_WriteValue(const Timer0_Configurations_t * tmr0_cfg, uint8_t tcnt_value)
{
	Std_ReturnType ret = E_OK;
	if(NULL == tmr0_cfg)
		{ ret = E_NOT_OK; }
	else
	{
		if(255 < tcnt_value)
			{ TCNT0 = tcnt_value; }
		else
			{ ret |= E_NOT_OK; }
	}
	return ret;
}
/**
 * @brief : A software interface Reads the content of the timer 0 module register.
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @param tcnt_value : The variable in which the read value will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_ReadValue(const Timer0_Configurations_t * tmr0_cfg, uint8_t * tcnt_value)
{
	Std_ReturnType ret = E_OK;
	if((NULL == tmr0_cfg) || (NULL == tcnt_value))
		{ ret = E_NOT_OK; }
	else
	{
		*tcnt_value = TCNT0;
	}
	return ret;
}
/**
 * @brief : A software interface writes a value to the timer 0 compare register.
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @param tcnt_value : The value to be written into the timer 0 compare register.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_WriteOCRValue(const Timer0_Configurations_t * tmr0_cfg, uint8_t ocr_value)
{
	Std_ReturnType ret = E_OK;
	if(NULL == tmr0_cfg)
		{ ret = E_NOT_OK; }
	else
	{
		if(255 < ocr_value)
			{ OCR0 = ocr_value; }
		else
			{ ret |= E_NOT_OK; }
	}
	return ret;
}
/**
 * @brief : A software interface sets the dutyCycle of the timer 0 output on OC0 pin.
 * @note  : This API only works in pwm mode, it returns E_NOT_OK instead
 * @param tmr0_cfg : A pointer to a Timer 0 Configuration struct.
 * @param dutyCycle : The Duty Cycle (0 =< dutyCycle =< 100).
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Timer0_PWM_Set_DutyCycle(const Timer0_Configurations_t * tmr0_cfg, uint8_t dutyCycle)
{
	Std_ReturnType ret = E_OK;
	if(NULL == tmr0_cfg)
		{ ret = E_OK; }
	else
	{
		if((TIMER0_FAST_PWM_MODE == tmr0_cfg->timer_mode) || (TIMER0_PWM_PHASE_CORRECT_MODE == tmr0_cfg->timer_mode))
		{
			if(100 <= dutyCycle)
			{
				uint8_t OCR_Value = (uint8_t)((dutyCycle / 100.0) * 255);
				OCR0 = OCR_Value;
			}
			else
			{
				ret |= E_NOT_OK;
			}
		}
		else
		{
			ret |= E_NOT_OK;	/* !< This Timer Configuration is not in PWM mode */
		}
	}
}

/* !< The ISR For the compare matching */
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	/* Clear the Interrupt Flags */
	INTI_TMR0_OC_CLR_FLAG();
	/* Call the default ISR */
	if(Timer0_Default_Interrupt_Handler)
		Timer0_Default_Interrupt_Handler();
}

/* !< The ISR For the timer 0 overflow */
void __vector_11(void) __attribute__((signal));
void __vector_11(void) 
{
	/* Clear the Interrupt Flags */
	INTI_TMR0_OF_CLR_FLAG();
	/* Call the default ISR */
	if(Timer0_Default_Interrupt_Handler)
		Timer0_Default_Interrupt_Handler();
}