/*
 * app.c
 *
 * Created: 6/30/2024 6:55:47 PM
 *  Author: Mostafa Asaad
 */ 

#include "app.h"

seven_segment_t segment = 
{
	.segment_pins[0].port_index = PORTC_INDEX,
	.segment_pins[0].pin_index = PIN0_INDEX,
	.segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
	.segment_pins[0].logic = GPIO_LOW,
	
	.segment_pins[1].port_index = PORTC_INDEX,
	.segment_pins[1].pin_index = PIN1_INDEX,
	.segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
	.segment_pins[1].logic = GPIO_LOW,
	
	.segment_pins[2].port_index = PORTC_INDEX,
	.segment_pins[2].pin_index = PIN2_INDEX,
	.segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
	.segment_pins[2].logic = GPIO_LOW,
	
	.segment_pins[3].port_index = PORTC_INDEX,
	.segment_pins[3].pin_index = PIN3_INDEX,
	.segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
	.segment_pins[3].logic = GPIO_LOW,
	
	.segment_type = SEGMENT_COMMON_ANODE
};

led_t red_led = { .port = PORTD_INDEX, .pin = PIN0_INDEX, .led_status = LED_OFF };
led_t yell_led = { .port = PORTD_INDEX, .pin = PIN1_INDEX, .led_status = LED_OFF };
led_t green_led = { .port = PORTD_INDEX, .pin = PIN2_INDEX, .led_status = LED_OFF };
pin_config_t seg_tens_en = 
	{.port_index = PORTC_INDEX, .pin_index = PIN4_INDEX, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW };
pin_config_t seg_ones_en = 
	{.port_index = PORTC_INDEX, .pin_index = PIN5_INDEX, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW  };



int time_taken = ONE_SECOND_DELAY;

int main(void)
{
	Std_ReturnType ret = E_OK;
	uint8_t counter = 0;

	ret |= app_init();

	while(1)
	{
		/* Start With STOP with 15 seconds */
		ret |= led_turn_ON(&red_led);
		counter = 15;
		while(counter > 0)
		{
			time_taken = ONE_SECOND_DELAY;
			while(time_taken > 0)
			{
				ret |= seven_segment_write_num(&segment, (uint8_t) (counter / 10));
				ret |= gpio_pin_write_logic(&seg_tens_en, GPIO_HIGH);
				_delay_ms(DISPLAY_REFRESH_INTERVAL);
				ret |= gpio_pin_write_logic(&seg_tens_en, GPIO_LOW);

				ret |= seven_segment_write_num(&segment, (uint8_t) (counter % 10));
				ret |= gpio_pin_write_logic(&seg_ones_en, GPIO_HIGH);
				_delay_ms(DISPLAY_REFRESH_INTERVAL);
				ret |= gpio_pin_write_logic(&seg_ones_en, GPIO_LOW);
				
				time_taken -= DISPLAY_REFRESH_INTERVAL * 2;
			}
			counter--;
		}
		ret |= led_turn_OFF(&red_led);
		ret |= seven_segment_write_num(&segment, 0);
		
		_delay_ms(250);
		
		/* 2. Yellow LED with 5 Seconds */
		ret |= led_turn_ON(&yell_led);
		counter = 5;
		ret |= gpio_pin_write_logic(&seg_ones_en, GPIO_HIGH);
		ret |= gpio_pin_write_logic(&seg_tens_en, GPIO_LOW);
		while(counter > 0)
		{
			ret |= gpio_pin_write_logic(&seg_ones_en, GPIO_HIGH);
			ret |= gpio_pin_write_logic(&seg_tens_en, GPIO_LOW);
			ret |= seven_segment_write_num(&segment, counter);
			_delay_ms(ONE_SECOND_DELAY);
			counter--;
		}
		ret |= led_turn_OFF(&yell_led);
		
		/* 3. Green led for 10 Seconds */
		ret |= led_turn_ON(&green_led);
		counter = 10;
		while(counter > 0)
		{
			time_taken = ONE_SECOND_DELAY;
			while(time_taken > 0)
			{
				ret |= seven_segment_write_num(&segment, (uint8_t) (counter / 10));
				ret |= gpio_pin_write_logic(&seg_tens_en, GPIO_HIGH);
				_delay_ms(DISPLAY_REFRESH_INTERVAL);
				ret |= gpio_pin_write_logic(&seg_tens_en, GPIO_LOW);

				ret |= seven_segment_write_num(&segment, (uint8_t) (counter % 10));
				ret |= gpio_pin_write_logic(&seg_ones_en, GPIO_HIGH);
				_delay_ms(DISPLAY_REFRESH_INTERVAL);
				ret |= gpio_pin_write_logic(&seg_ones_en, GPIO_LOW);
				
				time_taken -= DISPLAY_REFRESH_INTERVAL * 2;
			}
			counter--;
		}
		ret |= led_turn_OFF(&green_led);
		ret |= seven_segment_write_num(&segment, 0);

		_delay_ms(250);
	}

}

Std_ReturnType app_init(void)
{
	Std_ReturnType ret = E_OK;
	
	ret |= seven_segment_initialize(&segment);
	ret |= led_init(&red_led);
	ret |= led_init(&yell_led);
	ret |= led_init(&green_led);
	ret |= gpio_pin_initialize(&seg_tens_en);
	ret |= gpio_pin_initialize(&seg_ones_en);
	
	return ret;
}