/* 
 * File:   button.c
 * Author: Mostafa_Asaad
 *
 * Created on November 23, 2023, 1:49 PM
 */

/* Includes */
#include "button.h"


/* Functions Declaration */

/**
 * @brief A software Interface initializes a push-button object.
 * @param _button : A pointer to structure describes the push-button object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_init(const button_t* _button)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _button || ((_button->button_config).pin_index) > PIN_MAX_NUMBER - 1)
		{ ret = E_NOT_OK; } 
	else 
	{
        ret = gpio_pin_direction_init(&(_button->button_config));
    }
    return ret;
}
/**
 * @brief A software Interface reads the state of a push-button.
 * @param _button : A pointer to structure describes the push-button object.
 * @param value : A pointer to a button_state_t value which will hold the button state.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_read_state(const button_t* _button, button_state_t* value)
{
    Std_ReturnType ret = E_OK;
    if((NULL == _button) || (((_button->button_config).pin_index) > PIN_MAX_NUMBER - 1)
                       || (NULL == value))
		{ ret = E_NOT_OK; } 
	else 
	{
        uint8_t button_state = 0;
        switch(_button->button_connection)
		{
            case BUTTON_ACTIVE_HIGH:
                ret = gpio_pin_read_logic(&(_button->button_config), &button_state);
                *value = button_state;
                break;
            case BUTTON_ACTIVE_LOW:
                ret = gpio_pin_read_logic(&(_button->button_config), &button_state);
                if(GPIO_LOW == button_state)
					{ *value = BUTTON_PRESSED; }
				else if (GPIO_HIGH == button_state)
					{ *value = BUTTON_RELEASED; } 
				else
					{ ret = E_NOT_OK; }
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}