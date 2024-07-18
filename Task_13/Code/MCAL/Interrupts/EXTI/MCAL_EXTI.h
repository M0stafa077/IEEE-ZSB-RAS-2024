/*
 * MCAL_EXTI.h
 *
 * Created: 7/5/2024 3:54:52 PM
 *  Author: Mostafa Asaad
 */ 

#ifndef MCAL_EXTI_H_
#define MCAL_EXTI_H_

/* --------------- Section : Includes --------------- */
#include "../MCAL_interrupt_cfg.h"
/* --------------- Section: Macro Declarations --------------- */

/* --------------- Section: Macro Functions Declarations --------------- */
#define EXTI_INT0_INTERRUPT_ENABLE()			(GICRbits.INT0 = INTERRUPT_ENABLE)
#define EXTI_INT0_INTERRUPT_DISABLE()			(GICRbits.INT0 = INTERRUPT_DISABLE)
#define EXTI_INT0_CLR_FLAG()					(GIFRbits.INTF0 = STD_LOW)
	
#define EXTI_INT1_INTERRUPT_ENABLE()			(GICRbits.INT1 = INTERRUPT_ENABLE)
#define EXTI_INT1_INTERRUPT_DISABLE()			(GICRbits.INT1 = INTERRUPT_DISABLE)
#define EXTI_INT1_CLR_FLAG()					(GIFRbits.INTF1 = STD_LOW)

#define EXTI_INT2_INTERRUPT_ENABLE()			(GICRbits.INT2 = INTERRUPT_ENABLE)
#define EXTI_INT2_INTERRUPT_DISABLE()			(GICRbits.INT2 = INTERRUPT_DISABLE)
#define EXTI_INT2_CLR_FLAG()					(GIFRbits.INTF2 = STD_LOW)
/* --------------- Section: Data Type Declarations --------------- */
typedef enum
{
	EXTI_INT0,
	EXTI_INT1,
	EXTI_INT2
} EXTI_pin_t;

typedef enum
{
	LOW_STATE = 0,
	ON_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
} EXTI_source_t;

typedef struct  
{
	interrupt_handler_t interrupt_handler;
	EXTI_pin_t pin;
	EXTI_source_t interrupt_source;
} EXTI_t;
/*---------------  Section: Function Declarations --------------- */

/**
 * A software interface initializes an external interrupt pin.
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @ref: EXTI_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EXTI_init(const EXTI_t* obj);
/**
 * A software interface De-initializes an external interrupt pin.
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @ref: EXTI_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EXTI_DeInit(const EXTI_t* obj);

#endif /* MCAL_EXTI_H_ */