/*
 * app.c
 * Created: 6/30/2024 6:55:47 PM
 *  Author: Mostafa Asaad
 */ 
/* --------------- Section : Includes --------------- */
#include "app.h"
/* --------------- Section: Global Variables --------------- */
const uint8_t password[] = "1234";
volatile uint8_t pressedKey = 0, mutex_lock = 0;
uint8_t message[100];		/* Initialized with zeros (.bss) */


int main(void)
{
	Std_ReturnType ret = E_OK;

	ret |= app_init();
	
	/* Wait for the User to log-in */	
	LogIn();
	
	/* Welcome the user */
	lcd_4bit_send_command(&lcd, LCD_CLEAR);
	memcpy(message, "       Welcome\0", 15);
	ret |= lcd_4bit_send_string_pos(&lcd, 1, 1, message);
	
	/* Open the door ') */
	ServoMotor_SetAngle(180);
	
	while(1)
	{
		
	}
}

/*---------------  Section: Helper Functions Definitions --------------- */
Std_ReturnType app_init(void) 
{
	Std_ReturnType ret = E_OK;

	ret |= ecu_layer_initialize();
	
	EXTI_t int0_obj = {
		.interrupt_handler = EXTI_INT0_ISR,
		.pin = EXTI_INT0,
		.interrupt_source = RISING_EDGE
	};
	EXTI_t int1_obj = {
		.interrupt_handler = EXTI_INT1_ISR,
		.pin = EXTI_INT1,
		.interrupt_source = RISING_EDGE
	};
	EXTI_t int2_obj = {
		.interrupt_handler = EXTI_INT2_ISR,
		.pin = EXTI_INT2,
		.interrupt_source = RISING_EDGE
	};
	
	EXTI_init(&int0_obj);
	EXTI_init(&int1_obj);
	EXTI_init(&int2_obj);

	return ret;
}

void EXTI_INT0_ISR()
{
	if(!mutex_lock)
	{
		mutex_lock = 1;
		if(PINCbits.PC0)
		{
			pressedKey = buttons_values[0][0];
		}
		else if(PINCbits.PC1)
		{
			pressedKey = buttons_values[1][0];
		}
		else if(PINCbits.PC2)
		{
			pressedKey = buttons_values[2][0];
		}
		else if(PINCbits.PC3)
		{
			pressedKey = buttons_values[3][0];
		}
		mutex_lock = 0;
	}
}
void EXTI_INT1_ISR()
{
	if(!mutex_lock)
	{
		mutex_lock = 1;
		if(PINCbits.PC0)
		{
			pressedKey = buttons_values[0][1];
		}
		else if(PINCbits.PC1)
		{
			pressedKey = buttons_values[1][1];
		}
		else if(PINCbits.PC2)
		{
			pressedKey = buttons_values[2][1];
		}
		else if(PINCbits.PC3)
		{
			pressedKey = buttons_values[3][1];
		}
		mutex_lock = 0;
	}
}
void EXTI_INT2_ISR()
{
	if(!mutex_lock)
	{
		mutex_lock = 1;
		if(PINCbits.PC0)
		{
			pressedKey = buttons_values[0][2];
		}
		else if(PINCbits.PC1)
		{
			pressedKey = buttons_values[1][2];
		}
		else if(PINCbits.PC2)
		{
			pressedKey = buttons_values[2][2];
		}
		else if(PINCbits.PC3)
		{
			pressedKey = buttons_values[3][2];
		}
		mutex_lock = 0;
	}
}

void LogIn()
{
	uint8_t Entered_Password[4] = { 0 };
	uint8_t counter = 0, entered_chars = 0;

logging_in:
	counter = 0, entered_chars = 0;
	lcd_4bit_send_command(&lcd, LCD_CLEAR);
	memcpy(message, " Enter Your password\0", 19);
	lcd_4bit_send_string_pos(&lcd, 1, 1, (uint8_t *)message);
	
	lcd_4bit_set_cursor(&lcd, 2, 1);
	while(entered_chars < 4)
	{
		keypad_Start_With_Interrupts(&keypad);
		if(pressedKey != 0)
		{
			lcd_4bit_send_char_data(&lcd, '*');
			Entered_Password[counter++] = pressedKey;
			entered_chars++;
		}
		pressedKey = 0;
		_delay_ms(50);
	}
	for(uint8_t i = 0; i < 4; ++i)
	{
		if(password[i] != Entered_Password[i])
		{
			lcd_4bit_send_command(&lcd, LCD_CLEAR);
			memcpy(message, " Incorrect Password\0", 19);
			lcd_4bit_send_string_pos(&lcd, 1, 1, (uint8_t *)message);
			_delay_ms(2500);
			goto logging_in;
		}
	}
	return;
}