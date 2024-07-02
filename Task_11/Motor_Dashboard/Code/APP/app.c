/*
 * app.c
 * Created: 6/30/2024 6:55:47 PM
 *  Author: Mostafa Asaad
 */ 

#include "app.h"

dc_motor_t motor_1 = 
{
	.button_pin[DC_MOTOR_PIN1].port_index = PORTC_INDEX,
	.button_pin[DC_MOTOR_PIN1].pin_index = PIN0_INDEX,
	.button_pin[DC_MOTOR_PIN1].direction = GPIO_DIRECTION_OUTPUT,
	.button_pin[DC_MOTOR_PIN1].logic = GPIO_LOW,
	
	.button_pin[DC_MOTOR_PIN2].port_index = PORTC_INDEX,
	.button_pin[DC_MOTOR_PIN2].pin_index = PIN1_INDEX,
	.button_pin[DC_MOTOR_PIN2].direction = GPIO_DIRECTION_OUTPUT,
	.button_pin[DC_MOTOR_PIN2].logic = GPIO_LOW
};

dc_motor_t motor_2 =
{
	.button_pin[DC_MOTOR_PIN1].port_index = PORTC_INDEX,
	.button_pin[DC_MOTOR_PIN1].pin_index = PIN2_INDEX,
	.button_pin[DC_MOTOR_PIN1].direction = GPIO_DIRECTION_OUTPUT,
	.button_pin[DC_MOTOR_PIN1].logic = GPIO_LOW,
	
	.button_pin[DC_MOTOR_PIN2].port_index = PORTC_INDEX,
	.button_pin[DC_MOTOR_PIN2].pin_index = PIN3_INDEX,
	.button_pin[DC_MOTOR_PIN2].direction = GPIO_DIRECTION_OUTPUT,
	.button_pin[DC_MOTOR_PIN2].logic = GPIO_LOW
};

button_t forward_button = 
{
	.button_connection = BUTTON_ACTIVE_HIGH,
	
	.button_config.port_index = PORTC_INDEX,
	.button_config.pin_index = PIN4_INDEX,
	.button_config.direction = GPIO_DIRECTION_INPUT
};

button_t right_button =
{
	.button_connection = BUTTON_ACTIVE_HIGH,
	
	.button_config.port_index = PORTC_INDEX,
	.button_config.pin_index = PIN5_INDEX,
	.button_config.direction = GPIO_DIRECTION_INPUT
};

button_t backward_button =
{
	.button_connection = BUTTON_ACTIVE_HIGH,
	
	.button_config.port_index = PORTC_INDEX,
	.button_config.pin_index = PIN6_INDEX,
	.button_config.direction = GPIO_DIRECTION_INPUT
};

button_t left_button =
{
	.button_connection = BUTTON_ACTIVE_HIGH,
	
	.button_config.port_index = PORTC_INDEX,
	.button_config.pin_index = PIN7_INDEX,
	.button_config.direction = GPIO_DIRECTION_INPUT
};

button_t stop_button =
{
	.button_connection = BUTTON_ACTIVE_HIGH,
	
	.button_config.port_index = PORTD_INDEX,
	.button_config.pin_index = PIN0_INDEX,
	.button_config.direction = GPIO_DIRECTION_INPUT
};

led_t front_left_led = { .port = PORTD_INDEX, .pin = PIN1_INDEX, .led_status = LED_OFF };
led_t front_right_led = { .port = PORTD_INDEX, .pin = PIN2_INDEX, .led_status = LED_OFF };
led_t back_left_led = { .port = PORTD_INDEX, .pin = PIN3_INDEX, .led_status = LED_OFF };
led_t back_right_led = { .port = PORTD_INDEX, .pin = PIN4_INDEX, .led_status = LED_OFF };
		
button_state_t state = BUTTON_RELEASED;

int main(void)
{
	Std_ReturnType ret = E_OK;

	ret |= app_init();	

	while(1)
	{
		state = BUTTON_RELEASED;
		ret |= button_read_state(&forward_button, &state);
		if(BUTTON_PRESSED == state)
			{ ret |= move_forward(); }
		
		ret |= button_read_state(&right_button, &state);
		if(BUTTON_PRESSED == state)
			{ ret |= move_right(); }
		
		ret |= button_read_state(&backward_button, &state);
		if(BUTTON_PRESSED == state)
			{ ret |= move_backward(); }
		
		ret |= button_read_state(&left_button, &state);
		if(BUTTON_PRESSED == state)
			{ ret |= move_left(); }
		
		ret |= button_read_state(&stop_button, &state);
		if(BUTTON_PRESSED == state)
			{ ret |= stop(); }
		/* For debugging purposes */
		if(E_NOT_OK == ret)
			{ while(1); }
	}
	return 0;
}

Std_ReturnType app_init(void)
{
	Std_ReturnType ret = E_OK;
	ret |= dc_motor_init(&motor_1);
	ret |= dc_motor_init(&motor_2);
	
	ret |= button_init(&forward_button);
	ret |= button_init(&right_button);
	ret |= button_init(&backward_button);
	ret |= button_init(&left_button);
	ret |= button_init(&stop_button);
	
	ret |= led_init(&front_right_led);
	ret |= led_init(&front_left_led);
	ret |= led_init(&back_left_led);
	ret |= led_init(&back_right_led);	
	return ret;
}

Std_ReturnType move_forward(void)
{
	Std_ReturnType ret = E_OK;
	ret |= led_turn_ON(&front_left_led);
	ret |= led_turn_ON(&front_right_led);
	ret |= led_turn_OFF(&back_left_led);
	ret |= led_turn_OFF(&back_right_led);
	
	ret |= dc_motor_move_CW(&motor_1);
	ret |= dc_motor_move_CW(&motor_2);	
	return ret;
}
Std_ReturnType move_right(void)
{
	Std_ReturnType ret = E_OK;
	ret |= led_turn_ON(&front_right_led);
	ret |= led_turn_OFF(&front_left_led);
	ret |= led_turn_ON(&back_right_led);
	ret |= led_turn_OFF(&back_left_led);
	
	ret |= dc_motor_stop(&motor_2);
	ret |= dc_motor_move_CW(&motor_1);
	return ret;
}
Std_ReturnType move_backward(void)
{
	Std_ReturnType ret = E_OK;
	ret |= led_turn_OFF(&front_right_led);
	ret |= led_turn_OFF(&front_left_led);
	ret |= led_turn_ON(&back_right_led);
	ret |= led_turn_ON(&back_left_led);
	
	ret |= dc_motor_move_CCW(&motor_1);
	ret |= dc_motor_move_CCW(&motor_2);
	return ret;
}
Std_ReturnType move_left(void)
{
	Std_ReturnType ret = E_OK;
	ret |= led_turn_OFF(&front_right_led);
	ret |= led_turn_ON(&front_left_led);
	ret |= led_turn_OFF(&back_right_led);
	ret |= led_turn_ON(&back_left_led);
	
	ret |= dc_motor_move_CCW(&motor_2);
	ret |= dc_motor_stop(&motor_1);
	return ret;
}
Std_ReturnType stop(void)
{
	Std_ReturnType ret = E_OK;
	ret |= led_turn_OFF(&front_right_led);
	ret |= led_turn_OFF(&front_left_led);
	ret |= led_turn_OFF(&back_right_led);
	ret |= led_turn_OFF(&back_left_led);
	
	ret |= dc_motor_stop(&motor_1);
	ret |= dc_motor_stop(&motor_2);
	return ret;
}