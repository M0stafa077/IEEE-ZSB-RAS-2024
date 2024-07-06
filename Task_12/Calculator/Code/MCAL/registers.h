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
#define HWREG(_X)			(*((volatile uint8_t*) (_X)))

		/* PORT A Registers	*/
#define PORTA				HWREG(0x3B)
#define DDRA				HWREG(0x3A)
#define PINA				HWREG(0x39)

		/* PORT B Registers */
#define PORTB				HWREG(0x38)
#define DDRB				HWREG(0x37)
#define PINB				HWREG(0x36)

		/* PORT C Registers */
#define PORTC				HWREG(0x35)
#define DDRC				HWREG(0x34)
#define PINC				HWREG(0x33)

		/* PORT D Registers */
#define PORTD				HWREG(0x32)
#define DDRD				HWREG(0x31)
#define PIND				HWREG(0x30)

/* --------- This code section is for interrupts registers --------- */

/*
 * Status Register
 * bits: I T H S V N Z C
 * I: Global Interrupt enable bit.
 */
#define SREG				HWREG(0x5F)
typedef struct
{
	unsigned C				:1;
	unsigned Z				:1;
	unsigned N				:1;
	unsigned V				:1;
	unsigned S				:1;
	unsigned H				:1;
	unsigned T				:1;
	unsigned I				:1;
} SREGbits_t;
#define SREGbits (*(volatile SREGbits_t *)0x5F)

/*
 *  Global Interrupt Control Register.
 * bits: INT1	INT0	INT2	–	–	–	IVSEL	IVCE
 */
#define GICR				HWREG(0x5B)
typedef struct
{
	unsigned IVCE			:1;
	unsigned IVSEL			:1;
	unsigned  				:1;
	unsigned  				:1;
	unsigned  				:1;
	unsigned INT2			:1;
	unsigned INT0			:1;
	unsigned INT1			:1;
} GICRbits_t;
#define GICRbits (*(volatile GICRbits_t *)0x5B)

/**
 * Global Interrupt Flag Register.
 * bits: INTF1	INTF0	INTF2	–	–	–	–	–
*/
#define GIFR		HWREG(0x5A)
typedef struct
{
	unsigned				:5;
	unsigned INTF2			:1;
	unsigned INTF0			:1;
	unsigned INTF1			:1;
} GIFRbits_t;
#define GIFRbits (*(volatile GIFRbits_t *)0x5A)
/*
 * MCU Control Register.
 * bits: SE SM2 SM1 SM0 ISC11 ISC10 ISC01 ISC00
*/
/*
    ISC01 ISC00 Description
	0	  0		The low level of INT0 generates an interrupt request.
	0	  1		Any logical change on INT0 generates an interrupt request.
	1	  0		The falling edge of INT0 generates an interrupt request.
	1	  1		The rising edge of INT0 generates an interrupt request.
*/
#define MCUCR				HWREG(0x55)
typedef union
{
	struct
	{
		unsigned ISC00		:1;
		unsigned ISC01		:1;
		unsigned ISC10 		:1;
		unsigned ISC11		:1;
		unsigned SM0		:1;
		unsigned SM1		:1;
		unsigned SM2		:1;
		unsigned SE			:1;	
	};
	struct
	{
		unsigned ISC0x		:2;
		unsigned ISC1x		:2;
		unsigned 			:1;
		unsigned 			:1;
		unsigned 			:1;
		unsigned 			:1;
	};
} MCUCRbits_t;
#define MCUCRbits			(*(volatile MCUCRbits_t *)0x55)
/**
 * MCU Control and Status Register.
 * bits: JTD	ISC2	–	JTRF	WDRF	BORF	EXTRF	PORF
 * ISC2: Interrupt Sense Control 2
*/
#define MCUCSR				HWREG(0x54)
typedef struct
{
	unsigned PORF			:1;
	unsigned EXTRF			:1;
	unsigned BORF 			:1;
	unsigned WDRF			:1;
	unsigned JTRF			:1;
	unsigned				:1;
	unsigned ISC2			:1;
	unsigned JTD			:1;
} MCUCSRbits_t;
#define MCUCSRbits (*(volatile MCUCSRbits_t *)0x54)

#endif /* REGISTERS_H_ */
