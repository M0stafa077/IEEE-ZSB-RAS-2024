/* 
 * File:   dc_motor.h
 * Author: Mostafa Asaad
 * Created on December 2, 2023, 10:03 PM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

/* ------ Includes -----*/
#include "../../MCAL/gpio/gpio.h"
/* ----------------- Macro Declarations -----------------*/
#define DC_MOTOR_ON_STATUS		0x01U
#define DC_MOTOR_OFF_STATUS		0x00U

#define DC_MOTOR_PIN1			0x00U
#define DC_MOTOR_PIN2			0x01U
/* ----------------- Data Type Declarations -----------------*/
typedef struct 
{
    pin_config_t button_pin[2];
} dc_motor_t;

/* ----------------- Software Interfaces Declarations -----------------*/

/**
 * @brief A software Interface initializes a dc-motor object.
 * @param led : A pointer to structure describes the motor object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_init(const dc_motor_t *_dc_motor);
/**
 * @brief A software Interface moves a dc-motor Clock-Wise.
 * @param led : A pointer to structure describes the motor object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_CW(const dc_motor_t *_dc_motor);
/**
 * @brief A software Interface moves a dc-motor Counter Clock-Wise.
 * @param led : A pointer to structure describes the motor object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_CCW(const dc_motor_t *_dc_motor);
/**
 * @brief A software Interface stops a dc-motor.
 * @param led : A pointer to structure describes the motor object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);

#endif	/* DC_MOTOR_H */

