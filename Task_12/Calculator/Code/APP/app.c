/*
 * app.c
 * Created: 6/30/2024 6:55:47 PM
 *  Author: Mostafa Asaad
 */ 
/* --------------- Section : Includes --------------- */
#include "app.h"

/* --------------- Section: Global Variables --------------- */
uint8_t message[16];					/* A helper buffer used in displaying on the LCD */
sint32_t last_result = 0;				/* A helper Global Variable used to hold the last op. result */
sint32_t operand1 = 0, operand2 = 0;	/* Two helper Global Variables used to hold current op. operands */
uint8_t operator = 0;					/* A helper Global Variable used to hold the current op. operator */
uint8_t current_state = 0;				/* A helper Global Variable used to indicate which member in the op. is an i/p */
uint8_t new_op_flag = 0;				/* A helper Global Variable used to indicate if a new op. is attempt without reset */
volatile uint8_t reset_flag = 0;		/* A helper Global Variable used to indicate if a reset request is requested */

int main(void)
{
	Std_ReturnType ret = E_OK;

	ret |= app_init();
	lcd_4bit_send_command(&lcd, LCD_CLEAR);
	display_message("Enter: Operand1");

	while(1)
	{
		if(reset_flag)
			{ reset(); }
		handle_input();
	}
}

/*---------------  Section: Helper Functions Definitions --------------- */
Std_ReturnType app_init(void) 
{
	Std_ReturnType ret = E_OK;

	ret |= ecu_layer_initialize();
	
	ret |= mcal_initialize();

	return ret;
}

void handle_input(void) 
{
	uint8_t key = 15;
	
	while(key == 15)
	{
		if(reset_flag)
			{ reset(); return; }
		keypad_get_value(&keypad, &key);
	}
	if (key >= '0' && key <= '9') 
	{
		new_op_flag = 0;
		if (current_state == 0) 
		{
			operand1 = operand1 * 10 + (key - '0');
			lcd_4bit_send_char_data(&lcd, key);
		}
		else if (current_state == 2) 
		{
			new_op_flag = 0;
			operand2 = operand2 * 10 + (key - '0');
			lcd_4bit_send_char_data(&lcd, key);
		}
	} 
	else if (key == '+' || key == '-' || key == '*' || key == '/')
	{
		if(new_op_flag)
		{
			operand1 = last_result;
			operand2 = 0;
			lcd_4bit_send_command(&lcd, LCD_CLEAR);
			
			operator = key;
			current_state = 2;
			memcpy(message, "ANS \0", 5);
			lcd_4bit_send_string_pos(&lcd, 1, 1, message);
			lcd_4bit_send_char_data(&lcd, key);
			lcd_4bit_send_char_data(&lcd, ' ');		
		}
		if (current_state == 0)
		{
			operator = key;
			current_state = 2;
			lcd_4bit_send_char_data(&lcd, ' ');
			lcd_4bit_send_char_data(&lcd, key);
			lcd_4bit_send_char_data(&lcd, ' ');
		}
	}
	else if (key == '=')
	{
		if(2 == current_state)
			{ calculate_result(operand1, operand2, operator); }

	}
	else if (key == '#')
	{
		operand1 = 0;
		operand2 = 0;
		operator = 0;
		current_state = 0;
		new_op_flag = 0;
		lcd_4bit_send_command(&lcd, LCD_CLEAR);
		display_message("Enter: Operand1");
	}
	_delay_ms(50);
}

void calculate_result(int operand1, int operand2, char operator) 
{
	int result = 0;
	switch (operator) 
	{
		case '+':
			result = operand1 + operand2;
			break;
		case '-':
			result = operand1 - operand2;
			break;
		case '*':
			result = operand1 * operand2;
			break;
		case '/':
			if (operand2 != 0)
			{
				result = operand1 / operand2;
			}
			else
			{
				memcpy(message, "Err: Div by 0", 13);
				lcd_4bit_send_string_pos(&lcd, 2, 0, message);
				uint8_t value = 0;
				while('#' != value)
				{
					if(reset_flag)
						{ reset(); return; }
					keypad_get_value(&keypad, &value);
				}
				return;
			}
			break;
	}
	display_result(result);
	last_result = result;
}

void reset(void)
{
	lcd_4bit_send_command(&lcd, LCD_CLEAR);
	operand1 = 0;
	operand2 = 0;
	operator = 0;
	current_state = 0;
	last_result = 0;
	new_op_flag = 0;
	reset_flag = 0;
}