/*
 * MCAL_EXTI.c
 *
 * Created: 7/5/2024 3:54:43 PM
 *  Author: Mostafa Asaad
 */ 
/* -------------- Section: Includes -------------- */
#include "MCAL_EXTI.h"
/* -------------- Section: Global Variables -------------- */
static interrupt_handler_t EXTI_INT0_ISR = NULL;
static interrupt_handler_t EXTI_INT1_ISR = NULL;
static interrupt_handler_t EXTI_INT2_ISR = NULL;
/* -------------- Section: Function Definitions -------------- */

/**
 * A software interface initializes an external interrupt pin.
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @ref: EXTI_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EXTI_init(const EXTI_t* obj)
{
	Std_ReturnType ret = E_OK;
	if(NULL == obj)
		{ ret = E_NOT_OK; }
	else
	{
		pin_config_t exti_pin;
		/* Configure the external interrupt pin */
		switch(obj->pin)
		{
			case EXTI_INT0:
				/* 1. Disable INT0 interrupts  */
				EXTI_INT0_INTERRUPT_DISABLE();
				exti_pin.port_index=PORTD_INDEX, exti_pin.pin_index=PIN2_INDEX, exti_pin.direction=GPIO_DIRECTION_INPUT;
				/* 2. Initialize the DIO pin */
				ret = gpio_pin_initialize(&exti_pin);
				/* 3. Configure the interruption source */
				if(obj->interrupt_source > 3 || obj->interrupt_source < 0)
				{
					ret = E_NOT_OK;
					goto end;
				}
				else
				{
					MCUCRbits.ISC0x = obj->interrupt_source;	
				}
				/* 4. Assign the Interrupt Handler */
				EXTI_INT0_ISR = obj->interrupt_handler;
				/* 5. Enable Global Interrupts */
				INTERRUPT_GI_ENABLE();
				/* 6. Enable external interrupts for INT0 */
				EXTI_INT0_INTERRUPT_ENABLE();
				break;
			case EXTI_INT1:
				/* 1. Disable INT0 interrupts  */
				EXTI_INT1_INTERRUPT_DISABLE();
				exti_pin.port_index=PORTD_INDEX, exti_pin.pin_index=PIN3_INDEX, exti_pin.direction=GPIO_DIRECTION_INPUT;
				/* 2. Initialize the DIO pin */
				ret = gpio_pin_initialize(&exti_pin);
				/* 3. Configure the interruption source */
				if(obj->interrupt_source > 3 || obj->interrupt_source < 0)
				{
					ret = E_NOT_OK;
					goto end;
				}
				else
				{
					MCUCRbits.ISC1x = obj->interrupt_source;
				}				
				/* 4. Assign the Interrupt Handler */
				EXTI_INT1_ISR = obj->interrupt_handler;
				/* 5. Enable Global Interrupts */
				INTERRUPT_GI_ENABLE();
				/* 6. Enable external interrupts for INT1 */
				EXTI_INT1_INTERRUPT_ENABLE();
				break;
			case EXTI_INT2:
				/* 1. Disable INT2 interrupts  */
				EXTI_INT2_INTERRUPT_DISABLE();
				exti_pin.port_index=PORTB_INDEX, exti_pin.pin_index=PIN2_INDEX, exti_pin.direction=GPIO_DIRECTION_INPUT;
				/* 1. Initialize the DIO pin */
				ret = gpio_pin_initialize(&exti_pin);
				/* 2. Configure the interruption source */
				if(obj->interrupt_source != 2 || obj->interrupt_source != 3)	/* INT2 is edge triggered only */
				{
					ret = E_NOT_OK;
					goto end;
				}
				else
				{
					MCUCSRbits.ISC2 = obj->interrupt_source;
				}
				/* 4. Assign the Interrupt Handler */
				EXTI_INT2_ISR = obj->interrupt_handler;
				/* 5. Enable Global Interrupts */
				INTERRUPT_GI_ENABLE();
				/* 6. Enable external interrupts for INT0 */
				EXTI_INT2_INTERRUPT_ENABLE();
				break;
		}
	}
end:
	return ret;
}
/**
 * A software interface De-initializes an external interrupt pin.
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @ref: EXTI_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EXTI_DeInit(const EXTI_t* obj)
{
	Std_ReturnType ret = E_OK;
	if(NULL == obj)
		{ ret = E_NOT_OK; }
	else
	{
		/* Disable EXTI */
		switch(obj->pin)
		{
			case EXTI_INT0:
				EXTI_INT0_INTERRUPT_DISABLE();
				break;
			case EXTI_INT1:
				EXTI_INT1_INTERRUPT_DISABLE();
				break;
			case EXTI_INT2:
				EXTI_INT2_INTERRUPT_DISABLE();
				break;
		}
	}
	return ret;
}

/* ----------- Section: Interrupt-Service-Routines Definition ----------- */ 
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	/* 1. Clear Interrupt flag */
	EXTI_INT0_CLR_FLAG();
	
	if(EXTI_INT0_ISR)
	{
		EXTI_INT0_ISR();
	}
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	/* 1. Clear Interrupt flag */
	EXTI_INT1_CLR_FLAG();
	if(EXTI_INT1_ISR)
	{
		EXTI_INT1_ISR();
	}
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	/* 1. Clear Interrupt flag */
	EXTI_INT2_CLR_FLAG();
	if(EXTI_INT2_ISR)
	{
		EXTI_INT2_ISR();
	}
}
