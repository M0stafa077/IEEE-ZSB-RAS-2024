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
typedef struct
{
		unsigned PA0		:1;
		unsigned PA1		:1;
		unsigned PA2		:1;
		unsigned PA3		:1;
		unsigned PA4		:1;
		unsigned PA5		:1;
		unsigned PA6		:1;
		unsigned PA7		:1;
} PINAbits_t;
#define PINAbits			(*(volatile PINAbits_t *)0x39)

		/* PORT B Registers */
#define PORTB				HWREG(0x38)
#define DDRB				HWREG(0x37)
#define PINB				HWREG(0x36)
typedef struct
{
		unsigned PB0		:1;
		unsigned PB1		:1;
		unsigned PB2		:1;
		unsigned PB3		:1;
		unsigned PB4		:1;
		unsigned PB5		:1;
		unsigned PB6		:1;
		unsigned PB7		:1;
} PINBbits_t;
#define PINBbits			(*(volatile PINBbits_t *)0x36)

		/* PORT C Registers */
#define PORTC				HWREG(0x35)
#define DDRC				HWREG(0x34)
#define PINC				HWREG(0x33)
typedef struct
{
		unsigned PC0		:1;
		unsigned PC1		:1;
		unsigned PC2		:1;
		unsigned PC3		:1;
		unsigned PC4		:1;
		unsigned PC5		:1;
		unsigned PC6		:1;
		unsigned PC7		:1;
} PINCbits_t;
#define PINCbits			(*(volatile PINCbits_t *)0x33)

		/* PORT D Registers */
#define PORTD				HWREG(0x32)
#define DDRD				HWREG(0x31)
#define PIND				HWREG(0x30)
typedef struct
{
		unsigned PD0		:1;
		unsigned PD1		:1;
		unsigned PD2		:1;
		unsigned PD3		:1;
		unsigned PD4		:1;
		unsigned PD5		:1;
		unsigned PD6		:1;
		unsigned PD7		:1;
} PINDbits_t;
#define PINDbits			(*(volatile PINDbits_t *)0x30)

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
	unsigned  				:3;
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
		unsigned 			:4;
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

/* --------- Section: (A/D) Converter Registers -------------- */
/*
 * ADC Multiplexer
 * - Selection Register –
 * ADMUX
*/
#define ADMUX				HWREG(0X27)
typedef union
{
	struct
	{
		/* Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits */
		unsigned MUX0		:1;
		unsigned MUX1		:1;
		unsigned MUX2		:1;
		unsigned MUX3		:1;
		unsigned MUX4		:1;
		/* Bit 5 – ADLAR: ADC Left Adjust Result */
		unsigned ADLAR		:1;
		/* 
		 * Bit 7:6 – REFS1:0: Reference Selection Bits 
		 * 00 => AREF, Internal Vref turned off
		 * 01 => AVCC with external capacitor at AREF pin
		 * 10 => Reserved
		 * 11 => Internal 2.56V Voltage Reference with external capacitor at AREF pin
		 */
		unsigned REFS0		:1;
		unsigned REFS1		:1;
	};
	struct
	{
		unsigned MUX		:5;
		unsigned			:1;
		unsigned REF		:2;				
	};
} ADMUXbits_t;
#define ADMUXbits (*(volatile ADMUXbits_t *)0x27)


/*
 * ADC Control and
 * Status Register A
 * ADCSRA
 * ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
 */
#define ADCSRA				HWREG(0x26)
typedef union
{
	struct  
	{
		/* 
		 * Bits 2:0 – ADPS2:0: ADC Pre-scaler Select Bits 
		 * ADPS		Division Factor
		 * 000		2
		 * 001		2
		 * 010		4
		 * 011		8
		 * 100		16
		 * 101		32
		 * 110		64
		 * 111		128
		 */
		unsigned ADPS0		:1;
		unsigned ADPS1		:1;
		unsigned ADPS2		:1;
		/* Bit 3 – ADIE: ADC Interrupt Enable */
		unsigned ADIE		:1;
		/* Bit 4 – ADIF: ADC Interrupt Flag */
		unsigned ADIF		:1;
		/* Bit 5 – ADATE: ADC Auto Trigger Enable */
		unsigned ADATE		:1;
		/* Bit 6 – ADSC: ADC Start Conversion */
		unsigned ADSC		:1;
		/* Bit 7 – ADEN: ADC Enable */
		unsigned ADEN		:1;
	};
	struct
	{
		unsigned ADPS		:3;
		unsigned			:1;
		unsigned 			:1;
		unsigned 			:1;
		unsigned 			:1;
		unsigned 			:1;
	};	
} ADCSRAbits_t;
#define ADCSRAbits (*(volatile ADCSRAbits_t *)0x26)

#define ADCH				HWREG(0x25)
#define ADCL				HWREG(0x24)

/*
 * Special FunctionIO
 * Register – SFIOR
 * ADTS2 ADTS1 ADTS0 – ACME PUD PSR2 PSR10
*/
#define  SFIOR				HWREG(0X50)
typedef union
{
	struct  
	{
		unsigned PSR10		:1;
		unsigned PSR2		:1;
		unsigned PUD		:1;
		unsigned ACME		:1;
		unsigned			:1;
		/* 
		 * Bit 7:5 – ADTS2:0: ADC Auto Trigger Source 
		 * 000 Free Running mode
		 * 001 Analog Comparator
		 * 010 External Interrupt Request 0
		 * 011 Timer/Counter0 Compare Match
		 * 100 Timer/Counter0 Overflow
		 * 101 Timer/Counter1 Compare Match B
		 * 110 Timer/Counter1 Overflow
		 * 111 Timer/Counter1 Capture Event
		 */
		unsigned ADTS0		:1;
		unsigned ADTS1		:1;
		unsigned ADTS2		:1;		
	};
	
	struct
	{
		unsigned			:5;
		unsigned ADTS		:3;
	};
} SFIORbits_t;

#define SFIORbits (*(volatile SFIORbits_t *)0x50)
/* --------- Section: Timer 0 Registers -------------- */
/*
 * Timer/Counter Control
 * Register
 * FOC0 WGM00 COM01 COM00 WGM01 CS02 CS01 CS00
*/
#define TCCR0				HWREG(53)
typedef union
{
	struct
	{
		unsigned CS00		:1;
		unsigned CS01		:1;
		unsigned CS02		:1;
		unsigned WGM01		:1;
		unsigned COM00		:1;
		unsigned COM01		:1;
		unsigned WGM00		:1;
		unsigned FOC0		:1;	/* !< Force Output Compare (WO) */
	};
	struct
	{
		unsigned CS0		:3;
		unsigned			:1;
		unsigned COM0		:2; /* !< These bits control the Output Compare pin (OC0) behavior. */
		unsigned			:2;
	};
} TCCR0bits_t;
#define TCCR0bits (*(volatile TCCR0bits_t *)0x53)

/*
 * Timer/Counter
 * Register
 */
#define TCNT0				HWREG(0x52)

/*
 * Output Compare
 * Register
*/
#define OCR0				HWREG(0x5C)

/*
 * Timer/Counter
 * Interrupt Mask
 * Register
 *	OCIE2 TOIE2 TICIE1 OCIE1A OCIE1B TOIE1 OCIE0 TOIE0
*/
#define TIMSK				HWREG(0x59)
typedef struct
{
	unsigned TOIE0			:1; /* !< Timer/Counter0 Overflow Interrupt Enable */
	unsigned OCIE0			:1; /* !< Timer/Counter0 Output Compare Match Interrupt Enable */
	unsigned TOIE1			:1; /* !< Timer/Counter1, Input Capture Interrupt Enable */
	unsigned OCIE1B			:1; /* !< Timer/Counter1 B Output Compare Match Interrupt Enable */
	unsigned OCIE1A			:1; /* !< Timer/Counter1 A Output Compare Match Interrupt Enable */
	unsigned TICIE1			:1;	/* !< Timer/Counter1, Overflow Interrupt Enable */
	unsigned TOIE2			:1;  
	unsigned OCIE2			:1; 
} TIMSKbits_t;
#define TIMSKbits			(*(volatile TIMSKbits_t *) (0x59))

/*
 * Timer/Counter
 * Interrupt Flag Register
 * OCF2 TOV2 ICF1 OCF1A OCF1B TOV1 OCF0 TOV0
*/
#define	TIFR				HWREG(0x58)
typedef struct
{
	unsigned TOV0			:1; /* !< Timer/Counter0 Overflow Flag */
	unsigned OCF0			:1; /* !< Timer/Counter0 Output Compare Flag 0 */
	unsigned TOV1			:1; 
	unsigned OCF1B			:1; 
	unsigned OCF1A			:1; 
	unsigned ICF1			:1;
	unsigned TOV2			:1;
	unsigned OCF2			:1;
} TIFRbits_t;
#define TIFRbits			(*(volatile TIFRbits_t *) (0x58))

/* --------- Section: Timer 1 Registers -------------- */
/* COM1A1 COM1A0 COM1B1 COM1B0 FOC1A FOC1B WGM11 WGM10 */
#define TCCR1A				HWREG(0x4F)
typedef union
{
	struct
	{
		unsigned WGM10			:1;
		unsigned WGM11			:1;
		unsigned FOC1B			:1;
		unsigned FOC1A			:1;
		unsigned COM1B0			:1;
		unsigned COM1B1			:1;
		unsigned COM1A0			:1;
		unsigned COM1A1			:1;
	};
	struct
	{
		unsigned				:4;
		unsigned COM1B			:2;
		unsigned COM1A			:2;		
	};
} TCCR1Abits_t;
#define TCCR1Abits			(*(volatile TCCR1Abits_t *) (0x4F))

/* ICNC1 ICES1 – WGM13 WGM12 CS12 CS11 CS10 */
#define TCCR1B				HWREG(0x4E)
typedef union
{
	struct
	{
		unsigned CS10			:1;
		unsigned CS11			:1;
		unsigned CS12			:1;
		unsigned WGM12			:1;
		unsigned WGM13			:1;
		unsigned				:1;
		unsigned ICES1			:1;
		unsigned ICNC1			:1;
	};
	struct
	{
		unsigned CS1			:3;
		unsigned				:5;
	};

} TCCR1Bbits_t;
#define TCCR1Bbits			(*(volatile TCCR1Bbits_t *) (0x4E))

#define TCNT1H				HWREG(0x4D)
#define TCNT1L				HWREG(0x4C)
#define TCNT1				(*(volatile uint16_t *) (0x4C))

#define OCR1AH				HWREG(0x4B)
#define OCR1AL				HWREG(0x4A)
#define OCR1A				(*(volatile uint16_t *) (0x4A))

#define OCR1BH				HWREG(0x49)
#define OCR1BL				HWREG(0x48)
#define OCR1B				(*(volatile uint16_t *) (0x48))

#define ICR1H				HWREG(0x47)
#define ICR1L				HWREG(0x46)
#define ICR1				(*(volatile uint16_t *) (0x46))

/* --------------- Section: UART Registers ----------------- */

/*
 * @brief	UART Data Register
*/
#define UDR					HWREG(0x2C)
/*
 * @brief	USART Control and
 *	Status Register A
 * bits: RXC TXC UDRE FE DOR PE U2X MPCM
*/
#define UCSRA				HWREG(0x2B)
#define UCSRAbits			(*(volatile UCSRAbits_t *) (0x2B))
typedef struct
{
	unsigned MPCM			:1;	/* Multi-processor Communication Mode */
	unsigned U2X			:1; /* Double the USART Transmission Speed */
	unsigned PE				:1;	/* Parity Error */
	unsigned DOR			:1;	/* Data OverRun */
	unsigned FE				:1;	/* Frame Error */
	unsigned UDRE			:1;	/* USART Data Register Empty */
	unsigned TXC			:1;	/* USART Transmit Complete */
	unsigned RXC			:1;	/* USART Receive Complete */
} UCSRAbits_t;

/*
 * @brief	USART Control and
 Status Register B
 * bits: RXCIE TXCIE UDRIE RXEN TXEN UCSZ2 RXB8 TXB8
*/
#define UCSRB				HWREG(0x2A)
#define UCSRBbits			(*(volatile UCSRBbits_t *) (0x2A))
typedef struct
{
	unsigned TXB8			:1;	/* Transmit Data Bit 8 */
	unsigned RXB8			:1; /* Receive Data Bit 8 */
	unsigned UCSZ2			:1;	/* Character Size */
	unsigned TXEN			:1;	/* Transmitter Enable */
	unsigned RXEN			:1;	/* Receiver Enable */
	unsigned UDRIE			:1;	/* USART Data Register Empty Interrupt Enable */
	unsigned TXCIE			:1;	/* TX Complete Interrupt Enable */
	unsigned RXCIE			:1;	/* RX Complete Interrupt Enable */
} UCSRBbits_t;

/*
 * @brief	USART Control and
 Status Register C
 * bits: URSEL UMSEL UPM1 UPM0 USBS UCSZ1 UCSZ0 UCPOL
*/
#define UCSRC				HWREG(0x40)
#define UCSRCbits			(*(volatile UCSRCbits_t *) (0x40))
typedef union
{
	struct
	{
		unsigned UCPOL			:1;	/* Clock Polarity [This bit is used for Synchronous mode only] */
		unsigned UCSZ0			:1;
		unsigned UCSZ1			:1;	/* UCSZ1:0: Character Size */
		unsigned USBS			:1;	/* Stop Bit Select */
		unsigned UPM0			:1;
		unsigned UPM1			:1;	/* UPM[1:0]: Parity Mode  */
		unsigned UMSEL			:1;	/* UMSEL: USART Mode Select */
		unsigned URSEL			:1;	/* URSEL: Register Select */
	};
	struct
	{
			unsigned UCSZ		:3;
			unsigned			:1;
			unsigned UPM		:2;
			unsigned			:2;	
	};
} UCSRCbits_t;

/*
 * @brief	USART Baud Rate
 *			Register
*/
#define UBRRH				HWREG(0x40)
#define UBRRL				HWREG(0x29)


#endif /* REGISTERS_H_ */