/* 
 * File:   ecu_layer_init.C
 * Author: Mostafa_Asaad
 *
 * Created on December 8, 2023, 11:47 PM
 */
#include "ecu_layer_init.h"

/*---------------  Section: Global Variables Definition --------------- */
lcd_4bit_t lcd =
{
	.lcd_rs_pin = {PORTC_INDEX, PIN0_INDEX, GPIO_DIRECTION_OUTPUT},
	.lcd_en_pin = {PORTC_INDEX, PIN1_INDEX, GPIO_DIRECTION_OUTPUT},
	.lcd_data_pins =
	{
		{PORTC_INDEX, PIN2_INDEX, GPIO_DIRECTION_OUTPUT},
		{PORTC_INDEX, PIN3_INDEX, GPIO_DIRECTION_OUTPUT},
		{PORTC_INDEX, PIN4_INDEX, GPIO_DIRECTION_OUTPUT},
		{PORTC_INDEX, PIN5_INDEX, GPIO_DIRECTION_OUTPUT}
	}
};

keypad_t keypad =
{
	.keypad_row_pins =
	{
		{PORTC_INDEX, PIN0_INDEX, GPIO_DIRECTION_OUTPUT},
		{PORTC_INDEX, PIN1_INDEX, GPIO_DIRECTION_OUTPUT},
		{PORTC_INDEX, PIN2_INDEX, GPIO_DIRECTION_OUTPUT},
		{PORTC_INDEX, PIN3_INDEX, GPIO_DIRECTION_OUTPUT}
	},
	.keypad_columns_pins =
	{
		{PORTD_INDEX, PIN2_INDEX, GPIO_DIRECTION_INPUT},
		{PORTD_INDEX, PIN3_INDEX, GPIO_DIRECTION_INPUT},
		{PORTB_INDEX, PIN2_INDEX, GPIO_DIRECTION_INPUT}
	}
};
/*---------------  Section: Function Definition --------------- */
Std_ReturnType ecu_layer_initialize(void)
{
	Std_ReturnType ret = E_OK;
	
	ret |= lcd_4bit_initialize(&lcd);
	ret |= lcd_4bit_initialize(&lcd);
	uint8_t message[] = "Temperature:\0";
	ret |= lcd_4bit_send_string_pos(&lcd, 1, 1, message);
		
	return ret;
}

