/*
 * registers.h
 *
 *	Created: 5/4/2024 5:45:23 PM
 *  Author: Mostafa Asaad
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_


/* --------------- Section : Includes --------------- */
#include "MCAL_STD_TYPES.h"

/* --------------- Section: Macro Declarations --------------- */
#define HWREG(_X)	(*((volatile uint8_t*) (_X)))

		/* PORT A Registers	*/
#define PORTA		HWREG(0x3B)
#define DDRA		HWREG(0x3A)
#define PINA		HWREG(0x39)

		/* PORT B Registers */
#define PORTB		HWREG(0x38)
#define DDRB		HWREG(0x37)
#define PINB		HWREG(0x36)

		/* PORT C Registers */
#define PORTC		HWREG(0x35)
#define DDRC		HWREG(0x34)
#define PINC		HWREG(0x33)

		/* PORT D Registers */
#define PORTD		HWREG(0x32)
#define DDRD		HWREG(0x31)
#define PIND		HWREG(0x30)

#endif /* REGISTERS_H_ */
