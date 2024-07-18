/* 
 * File:   button.h
 * Author: Mostafa_Asaad
 * Created on November 23, 2023, 1:42 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

/* Includes : */
#include "../../MCAL/gpio/gpio.h"
/* Datatype Declaration :*/
typedef enum{
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED
} button_state_t;

typedef enum
{
    BUTTON_ACTIVE_LOW  = 0,
    BUTTON_ACTIVE_HIGH
} button_active_state_t;

typedef struct
{
    pin_config_t button_config;
    button_active_state_t button_connection;
} button_t;

/* Functions Prototypes */

/**
 * @brief A software Interface initializes a push-button object.
 * @param _button : A pointer to structure describes the push-button object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_init(const button_t* _button);
/**
 * @brief A software Interface reads the state of a push-button.
 * @param _button : A pointer to structure describes the push-button object.
 * @param value : A pointer to a button_state_t value which will hold the button state.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */  
Std_ReturnType button_read_state(const button_t* _button, button_state_t* value); 


#endif	/* BUTTON_H */

