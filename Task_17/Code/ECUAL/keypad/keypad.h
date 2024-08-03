/*
 * keypad.h
 *
 * Created: 5/5/2024 3:12:20 PM
 *  Author: User
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_


/* Section : Includes */
#include "keypad_cfg.h"
#include "..\..\MCAL\GPIO\gpio.h"

/* Section: Macro Declarations */

#if KEYPAD_TYPE == KEYPAD_FOUR_BY_FOUR

#define KEYPAD_ROWS					4
#define KEYPAD_COLUMNS				4

#elif KEYPAD_TYPE == KEYPAD_FOUR_BY_THREE

#define KEYPAD_ROWS					4
#define KEYPAD_COLUMNS				3

#endif


/* Section: Data Type Declarations */
typedef struct 
{
    pin_config_t keypad_row_pins[KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[KEYPAD_COLUMNS];
} keypad_t;

/* Section: Function Declarations */

/**
 * @brief A software interface initializes a keypad object
 * @param _keypad : A pointer to a keypad object.
 * @brief : A software interface initializes the keypad object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType keypad_initialize(keypad_t* _keypad);
/**
 * @brief A software interface gets the value of the key pressed on
 * the keypad.
 * @param _keypad : A pointer to a keypad object.
 * @param value : The variable in which the value will be stored.
 * @brief : A software interface gets the clicked button on the keypad.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_get_value(keypad_t* _keypad, uint8_t* value);

Std_ReturnType keypad_Start_With_Interrupts(keypad_t* _keypad);


#endif /* KEYPAD_H_ */