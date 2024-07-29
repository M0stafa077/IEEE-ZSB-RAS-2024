/*
 * gpio.h
 * Created: 5/4/2024 5:44:37 PM
 *  Author: Mostafa Asaad
 */ 


#ifndef GPIO_H_
#define GPIO_H_

/* --------------- Section : Includes --------------- */
#include "..\MCAL_STD_TYPES.h"
#include "..\registers.h"
#include "..\std_libraries.h"
/* --------------- Section : Macros Declaration --------------- */
#define BIT_MASK                    (uint8_t)0x01

#define PORTA_MASK                  (uint8_t)0xFF
#define PORTB_MASK                  (uint8_t)0xFF
#define PORTC_MASK                  (uint8_t)0xFF
#define PORTD_MASK                  (uint8_t)0xFF

#define PIN_MAX_NUMBER              8
#define PORT_MAX_NUMBER             4

/* ----------------------- Section: Function-like Macros ------------ */
#define SET_BIT(REG, BIT_POS)       REG |= (BIT_MASK << BIT_POS)
#define CLEAR_BIT(REG, BIT_POS)     REG &= ~(BIT_MASK << BIT_POS)
#define TOGGLE_BIT(REG, BIT_POS)    REG ^= (BIT_MASK << BIT_POS)
#define READ_BIT(REG, BIT_POS)      ((REG >> BIT_POS) & BIT_MASK)

#define SET_REGISTER(REG)			((REG)  = (0XFF))
#define	CLEAR_REGISTER(REG)			((REG)  = (0X00))
#define TOGGLE_REGISTER(REG)		((REG) ^= (0XFF))

/* ------------- Data-type Declarations ----------------------- */
typedef enum
{
	GPIO_LOW                        = 0x00,
	GPIO_HIGH                       = 0x01
} logic_t;

typedef enum
{
	GPIO_DIRECTION_OUTPUT           = 1,
	GPIO_DIRECTION_INPUT			= 0
} direction_t;

typedef enum
{
	PIN0_INDEX                      = 0,
	PIN1_INDEX,
	PIN2_INDEX,
	PIN3_INDEX,
	PIN4_INDEX,
	PIN5_INDEX,
	PIN6_INDEX,
	PIN7_INDEX
} pin_index_t;

typedef enum
{
	PORTA_INDEX                     = 0,
	PORTB_INDEX,
	PORTC_INDEX,
	PORTD_INDEX
} port_index_t;

typedef struct
{
	port_index_t port_index			:3;
	pin_index_t pin_index           :3;
	direction_t direction           :1;
	logic_t logic                   :1;
} pin_config_t;


/* --------- Section: Functions Prototypes --------------- */

/**
 * @brief: --> Sets The direction of the pin (i/p or o/p) <--
 * @param _pin_config : an object describes the pin configurations.
 * @param direction : The direction of the pin.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_direction_init(const pin_config_t* _pin_config);
/**
 * @brief             : --> READS THE DIRECTION OF THE PIN <--
 * @param _pin_config : an object describes the pin configurations.
 * @param dir_status  : a pointer to the variable receiving the direction 
 *                      status of the pin 
 * @return Status of the function 
 *          (E_OK)    : The function done successfully
 *          (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t* _pin_config, direction_t *dir_status);
/**
 * @brief             : --> Writes desired logic on a pin. <--
 * @param _pin_config : an object describes the pin configurations.
 * @param logic       : The logic wanted to be written on the pin.
 * @return Status of the function
 *          (E_OK)    : The function done successfully
 *          (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t* _pin_config, logic_t logic);
/**
 * @brief              : --> Reads the logic on a pin. <-- 
 * @param _pin_config  : an object describes the pin configurations.
 * @param logic        : a pointer to the variable in which the logic 
 *                      state of the pin should be stored.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t* _pin_config, uint8_t *logic);
/**
 * @brief              : --> Toggles the logic on a pin. <--
 * @param _pin_config  : an object describes the pin configurations.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t* _pin_config);
/**
 * @brief              : --> Initializes the direction of the pin
 *                          and writes the desired logic on it also. <--
 * @param _pin_config  : an object describes the pin configurations.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_initialize(const pin_config_t* _pin_config);
/**
 * @brief              : --> Initializes the direction of the whole port <--
 * @param port         : The port number or name.
 * @param direction    : The direction of the port (Input or Output)
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_direction_init(const port_index_t port, uint8_t direction);
/**
 * @brief              : --> Reads the direction of the whole port <-- 
 * @param port         : The port number or name.
 * @param dir_status   : A pointer to the variable in which the logic 
 *                      state of the pin should be stored.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_get_direction_status(const port_index_t port, uint8_t* dir_status);
/**
 * @brief              : --> Writes the desired logic on the whole port <-- 
 * @param port         : The port number or name.
 * @param logic        : The logic to be written on the port
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_write_logic(const port_index_t port, logic_t logic);
/**
 * @brief              : --> Reads the logic on the whole port <-- 
 * @param port         : The port number or name.
 * @param value        : a pointer to the variable in which the logic 
 *                       state of the port should be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_read_logic(const port_index_t port, uint8_t *value);
/**
 * @brief              : --> Toggles the logic on the whole port <--
 * @param port         : The port number or name.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_toggle_logic(const port_index_t port);

#endif /* GPIO_H_ */
