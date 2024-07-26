/*
 * adc.h
 * brief: A/D Converter Interface.
 * Created: 7/16/2024 9:06:40 PM
 *  Author: Mostafa Asaad
 */ 

#ifndef ADC_H
#define ADC_H
/* --------------- Section : Includes --------------- */
#include "../Interrupts/INTI/MCAL_INTI.h"
#include "../registers.h"
/* --------------- Section: Macro Declarations --------------- */
#define ADC_ENABLE						STD_ENABLE
#define ADC_DISABLE						STD_DISABLE

#define ADC_NORMAL_MODE					0x00
#define ADC_AUTO_TRIGGER				0x01

#define ADC_RESULT_RIGHT				0x00	
#define ADC_RESULT_LEFT					0x01

#define ADC_CONVERSION_IN_PROGRESS		0x01
#define ADC_CONVERSION_DONE				0X00
/* --------------- Section: Macro Functions Declarations --------------- */
#define ADC_SET_ENABLE()				(ADCSRAbits.ADEN = ADC_ENABLE)
#define ADC_SET_DISABLE()				(ADCSRAbits.ADEN = ADC_DISABLE)

#define ADC_ENABLE_CHANNEL(CH)			(ADMUXbits.MUX = (CH))

#define ADC_GET_CONVERSION_RESULT()		((ADCL) | (ADCH << 8))

#define ADC_SET_MODE_AUTO_TRIGGER()		(ADCSRAbits.ADATE = ADC_AUTO_TRIGGER)
#define ADC_SET_MODE_NORMAL()			(ADCSRAbits.ADATE = ADC_NORMAL_MODE)

#define ADC_SET_AUTO_TRIGGER_SRC(SRC)	(SFIORbits.ADTS = SRC)

#define ADC_SET_RESULT_FORMAT_LEFT()	(ADMUXbits.ADLAR = ADC_RESULT_LEFT)
#define ADC_SET_RESULT_FORMAT_RIGHT()	(ADMUXbits.ADLAR = ADC_RESULT_RIGHT)

#define ADC_SET_DIVISION_FACTOR(_X_)	(ADCSRAbits.ADPS = _X_)

#define ADC_SET_VOLTAGE_REFERENCE(X)	(ADMUXbits.REF = X)

#define ADC_SET_CHANNEL_AS_INPUT(CH)	(CLEAR_BIT(DDRA, CH))

#define ADC_START_CONVERSION()			(ADCSRAbits.ADSC = STD_ACTIVE)
/* --------------- Section: Data Type Declarations --------------- */
typedef enum 
{
	ADC_CHANNEL_0 = 0x00,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7
} ADC_Channel_t;

typedef enum
{
	ADC_DIVIDE_BY_2   = 0X01,
	ADC_DIVIDE_BY_4   = 0X02,
	ADC_DIVIDE_BY_8   = 0X03,
	ADC_DIVIDE_BY_16  = 0X04,
	ADC_DIVIDE_BY_32  = 0X05,
	ADC_DIVIDE_BY_64  = 0X06,
	ADC_DIVIDE_BY_128 = 0X07
} ADC_Division_Factor_t;

typedef enum 
{
	FREE_RUNNING_MODE = 0,
	ANALOG_COMPARATOR,
	EXTI_0,
	TMR0_CMP_MATCH,
	TMR0_OVERFLOW,
	TMR1_CMP_MATCH_B,
	TMR1_OVERFLOW,
	TMR1_CAPTURE_EVENT
} ADC_AutoTrigger_Source_t;

typedef enum
{
	AREF = 0,
	AVCC = 1,
	INTERNA_2_56 = 3
} ADC_Voltage_Ref_t;

typedef struct
{
	/* The Interrupt-Service-Routine for the adc */
	interrupt_handler_t adc_isr;
	/*
	 * ---- FOR ADC in Auto-Trigger Mode Only ----
	*/
	ADC_AutoTrigger_Source_t auto_trigger_src;
	/* The adc channel */
	ADC_Channel_t adc_channel;
	/* The ADC Division Factor */
	ADC_Division_Factor_t division_factor;
	/* The ADC Module Voltage Reference Source */
	ADC_Voltage_Ref_t voltage_reference;
		/* 
	* The Operation mode of the adc module 
	* ADC_NORMAL_MODE or ADC_AUTO_TRIGGER
	*/
	uint8_t adc_mode			:1;
	/* 
	* The Result format of the adc data registers 
	* ADC_RESULT_RIGHT or ADC_RESULT_LEFT
	*/
	uint8_t adc_result_format	:1;
	uint8_t reserved			:6;
} adc_t;
/*---------------  Section: Function Declarations --------------- */

/**
 * @brief A software interface initializes the 
 * A/D module.
 * @param adc_obj : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Init(const adc_t * adc_obj);
/**
 * @brief A software interface de-initializes the ADC module. 
 * @param adc_obj : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType ADC_DeInit(const adc_t * adc_obj);
/*
 * @brief A software interface selects the channel for the ADC module.
 * @param adc_obj : Pointer to the adc module object.
 * @param adc_new_channel : The channel to be selected.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Select_Channel(adc_t * adc_obj, ADC_Channel_t adc_new_channel);
/**
 * @brief A software interface starts the A/D Module conversion.
 * @param adc_obj : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Start_Conversion(const adc_t * adc_obj);
/**
 * @brief A software interface checks the status
 * of the A/D conversion.
 * @param adc_obj : Pointer to the adc module object.
 * @param conversion_status : The variable ref to store the status in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Is_Conversion_Done(const adc_t * adc_obj, uint8_t * conversion_status);
/**
 * @brief A software interface gets the
 * result of the A/D conversion
 * @param adc_obj : Pointer to the adc module object.
 * @param conversion_result : The variable ref to store the result in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_get_conversion_result(const adc_t * adc_obj, uint16_t * conversion_result);
/*
 * @brief A software interface gets the
 * result of the A/D conversion by blocking.
 * @param adc_obj : Pointer to the adc module object.
 * @param conversion_result : The variable ref to store the status in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Get_Conversion_Blocking(const adc_t * adc_obj, uint16_t * conversion_result);

#endif // ADC_H