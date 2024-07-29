/*
 * timer1.c
 *
 * Created: 7/25/2024 11:33:07 PM
 *  Author: Mostafa Asaad
 */ 
/*---------------  Section: Includes --------------- */
#include "timer1.h"
/*---------------  Section: Private Macros --------------- */
#define NORMAL				(uint8_t)0
#define CTC_A				(uint8_t)1
#define CTC_B				(uint8_t)2
#define INPUT_CAPTURE		(uint8_t)3

/*---------------  Section: Global Variables --------------- */
static interrupt_handler_t Timer1_Default_Interrupt_Handler = NULL;
static volatile uint8_t Timer_Mode = NORMAL;
/*---------------  Section: Static Helper Functions Declaration --------------- */
static void Timer1_Select_Mode(const Timer1_Configurations_t * timer_cfgs);
/*---------------  Section: Function Definitions --------------- */

Std_ReturnType Timer1_Init(const Timer1_Configurations_t * timer_cfgs)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == timer_cfgs)
		{ retVal = E_NOT_OK; }
	else
	{
		/* Disable Timer 1 Module */
		TMR1_SET_DISABLE();
		/* Set the timer 1 module mode */
		Timer1_Select_Mode(timer_cfgs);
		if(timer_cfgs->timer_mode == TIMER1_NORMAL_MODE)
			{ Timer_Mode = NORMAL; }
		else if(timer_cfgs->timer_mode == TIMER1_CTC_OCR1A_TOP_MODE)
			{ Timer_Mode = CTC_A; }
		else if(timer_cfgs->timer_mode == TIMER1_CTC_ICR1_TOP_MODE)
			{ Timer_Mode = CTC_B; }
		else
			{ Timer_Mode = INPUT_CAPTURE; }
		/* Set the OC1 pin behavior */
		TCCR1Abits.COM1A = timer_cfgs->oc1A_pin_behavior;
		TCCR1Abits.COM1B = timer_cfgs->oc1B_pin_behavior;
		if(timer_cfgs->oc1A_pin_behavior)	/* !< Not equal zero, which means not in the normal port operation */
			{ SET_BIT(DDRD, PIN5_INDEX); }
		if(timer_cfgs->oc1B_pin_behavior)	/* !< Not equal zero, which means not in the normal port operation */
			{ SET_BIT(DDRD, PIN4_INDEX); }
		/* Set the TCNT1 Pre-Loaded Value */
		TCNT1 = timer_cfgs->timer1_preload_value;
		/* Set the OCR1A Pre-Loaded Value */
		OCR1A = timer_cfgs->timer1_ocra_value;
		/* Set the OCR1B Pre-Loaded Value */
		OCR1B = timer_cfgs->timer1_ocrb_value;
		/* Configure Timer 1 Interrupt */
		// 1. Enable Global Interrupts
		INTERRUPT_GI_ENABLE();
		// 2. Clear the Interrupt Flags
		INTI_TMR1_OF_CLR_FLAG();
		INTI_TMR1_OCA_CLR_FLAG();
		INTI_TMR1_OCB_CLR_FLAG();
		INTI_TMR1_IC_CLR_FLAG();
		// 3. Set the default interrupt handler
		Timer1_Default_Interrupt_Handler = timer_cfgs->timer1_isr;
		// 4. Enable The Timer 1 Interrupts
		if(TIMER1_NORMAL_MODE == timer_cfgs->timer_mode)
			{ INTI_TMR1_OF_INTERRUPT_ENABLE(); }
		else
		{ 
			INTI_TMR1_OCA_INTERRUPT_ENABLE(); 
			INTI_TMR1_OCB_INTERRUPT_ENABLE();
			INTI_TMR1_IC_INTERRUPT_ENABLE(); 
		}
		/* Enable Timer 1 Module By Setting the clock source */
		TMR1_SET_CLK_SRC(timer_cfgs->timer1_clk_src);
	}
	return retVal;
}
Std_ReturnType Timer1_DeInit(const Timer1_Configurations_t * timer_cfgs)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == timer_cfgs)
	{ retVal = E_NOT_OK; }
	else
	{
		
	}
	return retVal;
}
Std_ReturnType Timer1_Write_Value(const Timer1_Configurations_t * timer_cfgs, uint16_t TCNT_Preload_Value)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == timer_cfgs)
	{ retVal = E_NOT_OK; }
	else
	{
		
	}
	return retVal;
}
Std_ReturnType Timer1_ReadValue(const Timer1_Configurations_t * timer_cfgs, uint8_t * TCNT_Value)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == timer_cfgs)
	{ retVal = E_NOT_OK; }
	else
	{


	}
	return retVal;
}
Std_ReturnType Timer1_WriteOCRAValue(const Timer1_Configurations_t * timer_cfgs, uint8_t OCRA_Value)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == timer_cfgs)
	{ retVal = E_NOT_OK; }
	else
	{
		
	}
	return retVal;
}
Std_ReturnType Timer1_WriteOCRBValue(const Timer1_Configurations_t * timer_cfgs, uint8_t OCRA_Value)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == timer_cfgs)
	{ retVal = E_NOT_OK; }
	else
	{
		
	}
	return retVal;
}
Std_ReturnType Timer1_PWM_Set_DutyCycle(const Timer1_Configurations_t * timer_cfgs, uint8_t dutyCycle)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == timer_cfgs)
	{ retVal = E_NOT_OK; }
	else
	{
		
	}
	return retVal;
}

/*---------------  Section: Static Helper Functions Definitions --------------- */
static void Timer1_Select_Mode(const Timer1_Configurations_t * timer_cfgs)
{
	/* Write WGM10 and WGM11 */
	TCCR1A |= (uint8_t)(((uint16_t)(timer_cfgs->timer_mode)) & ((uint16_t)(0X0003)));
	/* Write WGM12 and WGM13 */
	TCCR1B |= (uint8_t) ((((uint16_t)((timer_cfgs->timer_mode) >> 2)) & ((uint16_t)(0X0003))) << 3);
}

/* !< Timer/Counter1 Overflow ISR */
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	/* !< Clear the interrupt flag */
	INTI_TMR1_OF_CLR_FLAG();
	if(Timer1_Default_Interrupt_Handler && (Timer_Mode == NORMAL))
		{ Timer1_Default_Interrupt_Handler(); }
}

/* !< Timer/Counter1 Compare Match B ISR */
void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
	/* !< Clear the interrupt flag */
	INTI_TMR1_OCB_CLR_FLAG();
	if(Timer1_Default_Interrupt_Handler && (Timer_Mode == CTC_B))
		{ Timer1_Default_Interrupt_Handler(); }
}

/* !< Timer/Counter1 Compare Match A ISR */
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	/* !< Clear the interrupt flag */
	INTI_TMR1_OCA_CLR_FLAG();
	if(Timer1_Default_Interrupt_Handler && (Timer_Mode == CTC_A))
		{ Timer1_Default_Interrupt_Handler(); }
}

/* !< Timer/Counter1 Capture Event ISR */
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	/* !< Clear the interrupt flag */
	INTI_TMR1_IC_CLR_FLAG();
	if(Timer1_Default_Interrupt_Handler && ((Timer_Mode == INPUT_CAPTURE)))
		{ Timer1_Default_Interrupt_Handler(); }
}