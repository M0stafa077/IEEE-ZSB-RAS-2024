/**
 * @file problem_1.c
 * @author Mostafa Asaad
 * @brief Bit fields and typedef keyword in C language.
 */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char   uint8_t;
typedef signed char     sint8_t;

typedef unsigned short  uint16_t;
typedef signed short    sint16_t;

typedef unsigned int    uint32_t;
typedef signed int      sint32_t;

typedef unsigned long   uint64_t;
typedef signed long     sint64_t;

typedef float           ufloat32_t;
typedef double          ufloat64_t;

/*
 * u -> unsigned
 * s -> signed
 * int -> Not float
 * float -> float 
 * 8, 16, 32, 64 -> size of data type in bits
 * _t -> for typedef
*/

int main()
{
    printf("Size of unsigned char   [uint8_t]    is %i Byte\n", sizeof(uint8_t));
    printf("Size of signed   char   [sint8_t]    is %i Byte\n", sizeof(sint8_t));
    printf("Size of unsigned short  [uint16_t]   is %i Byte\n", sizeof(uint16_t));
    printf("Size of signed short    [sint16_t]   is %i Byte\n", sizeof(sint16_t));
    printf("Size of unsigned int    [uint32_t]   is %i Byte\n", sizeof(uint32_t));
    printf("Size of signed int      [sint32_t]   is %i Byte\n", sizeof(sint32_t));
    printf("Size of unsigned long   [uint64_t]   is %i Byte\n", sizeof(uint64_t));
    printf("Size of signed long     [sint64_t]   is %i Byte\n", sizeof(sint64_t));
    printf("Size of float           [ufloat32_t] is %i Byte\n", sizeof(ufloat32_t));
    printf("Size of double          [ufloat64_t] is %i Byte\n", sizeof(ufloat64_t));
}

