/*
 * gpio.c
 *
 *  Created: 5/4/2024 5:44:46 PM
 *  Author: Mostafa Asaad
 */ 

#include "gpio.h"
/* -------------Functions Definitions------------- */
/**
 * @brief: --> Sets The direction of the pin (i/p or o/p) <--
 * @param _pin_config : an object describes the pin configurations.
 * @param direction : The direction of the pin.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_direction_init(const pin_config_t* _pin_config){ 
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config -> pin_index > PIN_MAX_NUMBER - 1)
	{
        ret = E_NOT_OK;
    }
    else 
	{
        switch(_pin_config -> direction)
		{
            case GPIO_DIRECTION_OUTPUT:
				switch(_pin_config -> port_index)
				{
					case PORTA_INDEX: SET_BIT(DDRA, _pin_config -> pin_index);
								break;
					case PORTB_INDEX: SET_BIT(DDRB, _pin_config -> pin_index);
								break;
					case PORTC_INDEX: SET_BIT(DDRC, _pin_config -> pin_index);
								break;
					case PORTD_INDEX: SET_BIT(DDRD, _pin_config -> pin_index);
								break;														
				}
                break;
            case GPIO_DIRECTION_INPUT:
				switch(_pin_config -> port_index)
				{
					case PORTA_INDEX: CLEAR_BIT(DDRA, _pin_config -> pin_index);
								break;
					case PORTB_INDEX: CLEAR_BIT(DDRB, _pin_config -> pin_index);
								break;
					case PORTC_INDEX: CLEAR_BIT(DDRC, _pin_config -> pin_index);
								break;
					case PORTD_INDEX: CLEAR_BIT(DDRD, _pin_config -> pin_index);
								break;
				}
				break;
            default:
                ret = E_NOT_OK;
                break;
        }           
    }
    return ret;
}

/**
 * @brief             : --> READS THE DIRECTION OF THE PIN <--
 * @param _pin_config : an object describes the pin configurations.
 * @param dir_status  : a pointer to the variable receiving the direction 
 *                      status of the pin 
 * @return Status of the function 
 *          (E_OK)    : The function done successfully
 *          (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t* _pin_config, direction_t *dir_status){  
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config -> pin_index) > PIN_MAX_NUMBER - 1)
	{
	    ret = E_NOT_OK;
    }
    else 
	{
		switch(_pin_config -> port_index)
		{
			case PORTA_INDEX: 
				*dir_status = READ_BIT(DDRA, _pin_config -> pin_index);
				break;
			case PORTB_INDEX: 
				*dir_status = READ_BIT(DDRB, _pin_config -> pin_index);
				break;
			case PORTC_INDEX: 
				*dir_status = READ_BIT(DDRC, _pin_config -> pin_index);
				break;
			case PORTD_INDEX: 
				*dir_status = READ_BIT(DDRD, _pin_config -> pin_index);
				break;
		}
    }
    return ret;
}


/**
 * @brief             : --> Writes desired logic on a pin. <--
 * @param _pin_config : an object describes the pin configurations.
 * @param logic       : The logic wanted to be written on the pin.
 * @return Status of the function
 *          (E_OK)    : The function done successfully
 *          (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t* _pin_config, logic_t logic){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config -> pin_index) > PIN_MAX_NUMBER - 1)
	{
	    ret = E_NOT_OK;
    }
    else 
	{
	    switch(logic)
		{
		    case STD_HIGH:
				switch(_pin_config -> port_index)
				{
					case PORTA_INDEX: 
						SET_BIT(PORTA, _pin_config -> pin_index);
						break;
					case PORTB_INDEX: 
						SET_BIT(PORTB, _pin_config -> pin_index);
						break;
					case PORTC_INDEX: 
						SET_BIT(PORTC, _pin_config -> pin_index);
						break;
					case PORTD_INDEX: 
						SET_BIT(PORTD, _pin_config -> pin_index);
						break;
				}
				break;
		    case STD_LOW:
				switch(_pin_config -> port_index)
				{
					case PORTA_INDEX:
						CLEAR_BIT(PORTA, _pin_config -> pin_index);
						break;
					case PORTB_INDEX:
						CLEAR_BIT(PORTB, _pin_config -> pin_index);
						break;
					case PORTC_INDEX:
						CLEAR_BIT(PORTC, _pin_config -> pin_index);
						break;
					case PORTD_INDEX:
						CLEAR_BIT(PORTD, _pin_config -> pin_index);
						break;
				}
				break;
		    default: 
				ret = E_NOT_OK;
				break;
	    }
    }
    return ret;
}

/**
 * @brief              : --> Reads the logic on a pin. <-- 
 * @param _pin_config  : an object describes the pin configurations.
 * @param logic        : a pointer to the variable in which the logic 
 *                      state of the pin should be stored.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t* _pin_config, uint8_t *logic){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config -> pin_index > PIN_MAX_NUMBER - 1 || NULL == logic)
    {
	    ret = E_NOT_OK;
    } 
	else
    {
		switch(_pin_config -> port_index)
		{
			case PORTA_INDEX:
				*logic = READ_BIT(PINA, _pin_config -> pin_index);
				break;
			case PORTB_INDEX:
				*logic = READ_BIT(PINB, _pin_config -> pin_index);
				break;
			case PORTC_INDEX:
				*logic = READ_BIT(PINC, _pin_config -> pin_index);
				break;
			case PORTD_INDEX:
				*logic = READ_BIT(PIND, _pin_config -> pin_index);
				break;
			default:
				ret = E_NOT_OK;
				break;
		}
    }
    return ret;
}

/**
 * @brief              : --> Toggles the logic on a pin. <--
 * @param _pin_config  : an object describes the pin configurations.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t* _pin_config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config -> pin_index) > PIN_MAX_NUMBER - 1 )
	{
	    ret = E_NOT_OK;
	} 
	else
	{
	    switch(_pin_config -> port_index)
	    {
		    case PORTA_INDEX:
				TOGGLE_BIT(PORTA, _pin_config -> pin_index);
				break;
		    case PORTB_INDEX:
				TOGGLE_BIT(PORTB, _pin_config -> pin_index);
				break;
		    case PORTC_INDEX:
				TOGGLE_BIT(PORTC, _pin_config -> pin_index);
				break;
		    case PORTD_INDEX:
				TOGGLE_BIT(PORTD, _pin_config -> pin_index);
				break;
	    }
    }
    return ret;
}
/**
 * @brief              : --> Initializes the direction of the pin
 *                          and writes the desired logic on it also. <--
 * @param _pin_config  : an object describes the pin configurations.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_initialize(const pin_config_t* _pin_config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config -> pin_index) > PIN_MAX_NUMBER - 1)
    {
	    ret = E_NOT_OK;
    }
    else
    {
	    ret = gpio_pin_direction_init(_pin_config);
	    ret = gpio_pin_write_logic(_pin_config, _pin_config -> logic);
    }
    return ret;
}

/**
 * @brief              : --> Initializes the direction of the whole port <--
 * @param port         : The port number or name.
 * @param direction    : The direction of the port (Input or Output)
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_direction_init(const port_index_t port, uint8_t direction){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER - 1)
	{
        ret = E_NOT_OK;
    }
    else 
	{
		switch (direction)
		{
			case GPIO_DIRECTION_INPUT:
				switch(port)
				{
					case PORTA_INDEX: DDRA = 0x00;
								break;
					case PORTB_INDEX: DDRB = 0x00;
								break;
					case PORTC_INDEX: DDRC = 0x00;
								break;
					case PORTD_INDEX: DDRD = 0x00;
								break;
				}
				break;
			case GPIO_DIRECTION_OUTPUT:
				switch(port)
				{
					case PORTA_INDEX: DDRA = PORTA_MASK;
								break;
					case PORTB_INDEX: DDRB = PORTB_MASK;
								break;
					case PORTC_INDEX: DDRC = PORTC_MASK;
								break;
					case PORTD_INDEX: DDRD = PORTD_MASK;
								break;
				}
				break;
			default:
				ret = E_NOT_OK;
				break;
		}
    } 
    return ret;
}

/**
 * @brief              : --> Reads the direction of the whole port <-- 
 * @param port         : The port number or name.
 * @param dir_status   : A pointer to the variable in which the logic 
 *                      state of the pin should be stored.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_get_direction_status(const port_index_t port, uint8_t* dir_status)
{
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER - 1)
	{
	    ret = E_NOT_OK;
    }
    else 
	{
		switch(port)
		{
			case PORTA_INDEX: *dir_status = DDRA;
				break;
			case PORTB_INDEX: DDRB = *dir_status = DDRB;
				break;
			case PORTC_INDEX: DDRC = *dir_status = DDRC;
				break;
			case PORTD_INDEX: DDRD = *dir_status = DDRD;
				break;
		}
    }
    
    return ret;
}
/**
 * @brief              : --> Writes the desired logic on the whole port <-- 
 * @param port         : The port number or name.
 * @param logic        : The logic to be written on the port
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_write_logic(const port_index_t port, logic_t logic)
{
    Std_ReturnType ret = E_OK;
	if(port > PORT_MAX_NUMBER - 1)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch (logic)
		{
			case STD_HIGH:
				switch(port)
				{
					case PORTA_INDEX: SET_REGISTER(PINA);
						break;
					case PORTB_INDEX: SET_REGISTER(PINB);
						break;
					case PORTC_INDEX: SET_REGISTER(PINC);
						break;
					case PORTD_INDEX: SET_REGISTER(PIND);
						break;
				}
				break;
			case STD_LOW:
				switch(port)
				{
					case PORTA_INDEX: CLEAR_REGISTER(PINA);
						break;
					case PORTB_INDEX: CLEAR_REGISTER(PINB);
						break;
					case PORTC_INDEX: CLEAR_REGISTER(PINC);
						break;
					case PORTD_INDEX: CLEAR_REGISTER(PIND);
						break;
				}
				break;
			default:
				ret = E_NOT_OK;
					break;
		}
	}
    return ret;
}

/**
 * @brief              : --> Reads the logic on the whole port <-- 
 * @param port         : The port number or name.
 * @param value        : a pointer to the variable in which the logic 
 *                       state of the port should be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_read_logic(const port_index_t port, uint8_t *value)
{
    Std_ReturnType ret = E_OK;
    if((port > PORT_MAX_NUMBER - 1 )|| (NULL == value) ){
	    ret = E_NOT_OK;
    }
    else 
	{
	    switch(port)
	    {
		    case PORTA_INDEX: *value = PINA;
				break;
		    case PORTB_INDEX: *value = PINB;
				break;
		    case PORTC_INDEX: *value = PINC;
				break;
		    case PORTD_INDEX: *value = PIND;
				break;
	    }
    }
    return ret;
}

/**
 * @brief              : --> Toggles the logic on the whole port <--
 * @param port         : The port number or name.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_toggle_logic(const port_index_t port){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER - 1) 
	{
	    ret = E_NOT_OK;
    }
    else
    {
	    switch(port)
	    {
		    case PORTA_INDEX: TOGGLE_REGISTER(PORTA);
				break;
		    case PORTB_INDEX: TOGGLE_REGISTER(PORTB);
				break;
		    case PORTC_INDEX: TOGGLE_REGISTER(PORTC);
				break;
		    case PORTD_INDEX: TOGGLE_REGISTER(PORTD);
				break;
	    }
    }
    return ret;
}