/*
 * MCAL_STD_TYPES.h
 *
 * Created: 5/4/2024 5:49:18 PM
 *  Author: Mostafa Asaad
 */ 


#ifndef MCAL_STD_TYPES_H_
#define MCAL_STD_TYPES_H_


/* Data-type Declarations: */
typedef unsigned char		uint8_t;
typedef unsigned int		uint16_t;
typedef unsigned long		uint32_t;

typedef signed char			sint8_t;
typedef signed short		sint16_t;
typedef signed long			sint32_t;

typedef uint8_t				Std_ReturnType;

/* Macros Declaration */
#define STD_TRUE            (1U)
#define STD_FALSE           (0U)

#define STD_HIGH            STD_TRUE
#define STD_LOW             STD_FALSE

#define STD_ENABLE          STD_HIGH
#define STD_DISABLE         STD_LOW

#define STD_RISING_EDGE     STD_TRUE
#define STD_FALLING_EDGE    STD_FALSE

#define STD_ON              STD_HIGH
#define STD_OFF             STD_LOW

#define E_OK                (Std_ReturnType)STD_FALSE
#define E_NOT_OK            (Std_ReturnType)STD_TRUE

#define STD_ACTIVE          STD_ON
#define STD_IDLE            STD_OFF

#define ZERO_INIT           STD_FALSE

#endif /* MCAL_STD_TYPES_H_ */
