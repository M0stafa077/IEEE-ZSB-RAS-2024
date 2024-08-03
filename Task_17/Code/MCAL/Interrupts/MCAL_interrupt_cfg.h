/*
 * MCAL_interrupt_cfg.h
 *
 * Created: 7/5/2024 3:55:52 PM
 *  Author: Mostafa Asaad
 */ 


#ifndef MCAL_INTERRUPT_CFG_H_
#define MCAL_INTERRUPT_CFG_H_

/* -------------- Section : Includes -------------- */
#include "../registers.h"
#include "../gpio/gpio.h"

/* -------------- Section: Macro Declarations -------------- */
#define INTERRUPT_ENABLE                        STD_ENABLE
#define INTERRUPT_DISABLE                       STD_DISABLE

#define INTERRUPT_OCCURED                       STD_HIGH
#define INTERRUPT_NOT_OCCURED                   STD_LOW

#define EXTI_INTx_ARE_ENABLED                   INTERRUPT_ENABLE

/* -------------- Section: Macro Functions Declarations -------------- */


/* Enables Global Interrupts */
#define INTERRUPT_GI_ENABLE()                 (SREGbits.I = INTERRUPT_ENABLE)

/* Disables Global Interrupts */
#define INTERRUPT_GI_DISABLE()                (SREGbits.I = INTERRUPT_DISABLE)

/* -------------- Section: Data Type Declarations -------------- */
typedef void (*interrupt_handler_t)(void);

/* -------------- Section: Function Declarations -------------- */

#endif /* MCAL_INTERRUPT_CFG_H_ */