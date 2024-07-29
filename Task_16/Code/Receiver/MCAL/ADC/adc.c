/*
 * adc.c 
 * brief: A/D Converter Code Implementation.
 * Created: 7/16/2024 9:06:40 PM
 *  Author: Mostafa Asaad
 */ 
/* --------------- Section : Includes --------------- */
#include "adc.h"
/* --------------- Section : Global Variables --------------- */
static interrupt_handler_t adc_interrupt_handler = NULL;
/*---------------  Section: Function Declarations --------------- */

/**
 * @brief A software interface initializes the 
 * A/D module.
 * @param adc_obj : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Init(const adc_t * adc_obj)
{
	Std_ReturnType ret = E_OK;
	if(NULL == adc_obj)
		{ ret = E_NOT_OK; }
	else
	{
		/* 1. Disable the ADC module */
		ADC_SET_DISABLE();
		/* 2. Configure ADC Channel */
		ADC_ENABLE_CHANNEL(adc_obj->adc_channel);
		ADC_SET_CHANNEL_AS_INPUT(adc_obj->adc_channel);
		/* 3. Configure the ADC Interrupt */
		// 1. Enable Global Interrupts
		INTERRUPT_GI_ENABLE();
		// 2. Clear the ADC Interrupt Flag
		INTI_ADC_CLR_FLAG();
		// 3. Assign the interrupt-service-routine
		adc_interrupt_handler = adc_obj	-> adc_isr;
		// 4. Enable the ADC Module Interrupts
		INTI_ADC_INTERRUPT_ENABLE();
		/* 4. Configure the ADC Module Mode */
		switch(adc_obj->adc_mode)
		{
			case ADC_AUTO_TRIGGER:
				ADC_SET_MODE_AUTO_TRIGGER();
				ADC_SET_AUTO_TRIGGER_SRC(adc_obj -> auto_trigger_src);
				break;
			case ADC_NORMAL_MODE:
			default: ADC_SET_MODE_NORMAL();
				break;
		}
		/* 5. Configure the ADC Module Result format */
		switch(adc_obj->adc_result_format)
		{
			case ADC_RESULT_LEFT: ADC_SET_RESULT_FORMAT_LEFT();
							break;
			case ADC_RESULT_RIGHT:
			default: ADC_SET_RESULT_FORMAT_RIGHT();
				break;
		}
		/* 6. Configure the division factor */
		ADC_SET_DIVISION_FACTOR(adc_obj->division_factor);
		/* 7. Configure the Voltage reference */
		ADC_SET_VOLTAGE_REFERENCE(adc_obj->voltage_reference);
		/* 8. Enable the ADC Module */
		ADC_SET_ENABLE();
	}
	return ret;
}
/**
 * @brief A software interface de-initializes the ADC module. 
 * @param adc_obj : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType ADC_DeInit(const adc_t * adc_obj)
{
	Std_ReturnType ret = E_OK;
	if(NULL == adc_obj)
		{ ret = E_NOT_OK; }
	else
	{
		/* Disable the ADC Module Interrupts */
		INTI_ADC_INTERRUPT_DISABLE();
		/* Make the default interrupt isr NULL again */
		adc_interrupt_handler = NULL;
		/* Disable the ADC Module */
		ADC_SET_DISABLE();
	}
	return ret;
}
/*
 * @brief A software interface selects the channel for the ADC module.
 * @param adc_obj : Pointer to the adc module object.
 * @param adc_new_channel : The channel to be selected.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Select_Channel(adc_t * adc_obj, ADC_Channel_t adc_new_channel)
{
	Std_ReturnType ret = E_OK;
	if(NULL == adc_obj)
		{ ret = E_NOT_OK; }
	else
	{
		/* Assign the new channel to the adc object */
		adc_obj->adc_channel = adc_new_channel;
		/* Enable the Analog functionality for the new channel */
		ADC_ENABLE_CHANNEL(adc_new_channel);
		/* Set the new channel pin as input */
		ADC_SET_CHANNEL_AS_INPUT(adc_new_channel);
	}
	return ret;
}
/**
 * @brief A software interface starts the A/D Module conversion.
 * @param adc_obj : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Start_Conversion(const adc_t * adc_obj)
{
	Std_ReturnType ret = E_OK;
	if(NULL == adc_obj)
		{ ret = E_NOT_OK; }
	else
	{
		ADC_START_CONVERSION();
	}
	return ret;
}
/**
 * @brief A software interface checks the status
 * of the A/D conversion.
 * @param adc_obj : Pointer to the adc module object.
 * @param conversion_status : The variable ref to store the status in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Is_Conversion_Done(const adc_t * adc_obj, uint8_t * conversion_status)
{
	Std_ReturnType ret = E_OK;
	if((NULL == adc_obj) || (NULL == conversion_status))
		{ ret = E_NOT_OK; }
	else
	{
		*conversion_status = !ADCSRAbits.ADSC;
	}
	return ret;
}
/**
 * @brief A software interface gets the
 * result of the A/D conversion
 * @param adc_obj : Pointer to the adc module object.
 * @param conversion_result : The variable ref to store the result in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_get_conversion_result(const adc_t * adc_obj, uint16_t * conversion_result)
{
	Std_ReturnType ret = E_OK;
	if((NULL == adc_obj) || (NULL == conversion_result))
	{ ret = E_NOT_OK; }
	else
	{
		switch(adc_obj->adc_result_format)
		{
			case ADC_RESULT_LEFT: *conversion_result = (uint16_t)(((ADCH << 8) + ADCL) >> 6);
								break;
			case ADC_RESULT_RIGHT: 
			default: *conversion_result = ADC_GET_CONVERSION_RESULT();
					break;
		}
	}
	return ret;
}
/*
 * @brief A software interface gets the
 * result of the A/D conversion by blocking.
 * @param adc_obj : Pointer to the adc module object.
 * @param conversion_result : The variable ref to store the status in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Get_Conversion_Blocking(const adc_t * adc_obj, uint16_t * conversion_result)
{
	Std_ReturnType ret = E_OK;
	if((NULL == adc_obj) || (NULL == conversion_result))
		{ ret = E_NOT_OK; }
	else
	{
		ret |= ADC_START_CONVERSION();
		while(!ADCSRAbits.ADSC);
		ret |= ADC_get_conversion_result(adc_obj, conversion_result);
	}
	return ret;
}

/* Default ISR for the ADC Module */ 
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	/* 1. Clear the ADC interrupt flag */
	INTI_ADC_CLR_FLAG();
	/* 2. Call the interrupt handler */
	if(adc_interrupt_handler)
		{ adc_interrupt_handler(); }
}