/*
 * app.c
 * Created: 6/30/2024 6:55:47 PM
 *  Author: Mostafa Asaad
 */ 
/* --------------- Section : Includes --------------- */
#include "app.h"

/* --------------- Section: Global Variables --------------- */
void pot_isr(void);

volatile uint16_t adc_res = 0;
static uint8_t number_of_leds_on = 0;

adc_t pot = 
{
	.adc_isr = pot_isr,
	.adc_channel = ADC_CHANNEL_0,
	.adc_mode = ADC_NORMAL_MODE,
	.adc_result_format = ADC_RESULT_RIGHT, 
	.division_factor = ADC_DIVIDE_BY_8,
	.voltage_reference = AVCC
};

int main(void)
{
	Std_ReturnType ret = E_OK;

	ret |= app_init();

	while(1)
	{
		ret |= ADC_Start_Conversion(&pot);
		number_of_leds_on = ((adc_res * 8) / (1024));
		if (7 == number_of_leds_on) ++number_of_leds_on;
		
		for(uint8_t l_counter = 0; l_counter < 8; ++l_counter)
		{
			if(l_counter < number_of_leds_on)
			{
				SET_BIT(PORTC, l_counter);
			}
			else
			{
				CLEAR_BIT(PORTC, l_counter);
			}
		}
		_delay_ms(100);
	}
}

/*---------------  Section: Helper Functions Definitions --------------- */
Std_ReturnType app_init(void) 
{
	Std_ReturnType ret = E_OK;

	// ret |= ecu_layer_initialize();
	
	// ret |= mcal_initialize();
	
	ret |= ADC_Init(&pot);
	
	/* Set PORTC As Output for the LEDs */
	DDRC = 0xFF;

	return ret;
}

void pot_isr(void)
{
	ADC_get_conversion_result(&pot, &adc_res);
}