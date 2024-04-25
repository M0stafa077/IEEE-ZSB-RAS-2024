/**
 * @file problem_1.c
 * @author Mostafa Asaad
 * @brief Bit fields and typedef keyword in C language.
 */

#include <stdio.h>
#include <stdlib.h>

typedef signed int       sint32_t;

typedef struct 
{
    sint32_t real;
    sint32_t imag;
} complex_number_t;

complex_number_t* add_complex(complex_number_t *first_number, complex_number_t *second_number);

int main(void)
{
    complex_number_t first_number, second_number;
    first_number.real = 5, first_number.imag = 3;
    second_number.real = 6, second_number.imag = -6;
    complex_number_t* result = add_complex(&first_number, &second_number);

    printf("[5+3j] + [6-6j] = [%d%dj]\n", result->real, result->imag);
}

complex_number_t* add_complex(complex_number_t *first_number, complex_number_t *second_number)
{
    complex_number_t* result = NULL;
    result = (complex_number_t*) malloc(sizeof(complex_number_t));

    result -> real = (first_number -> real) + (second_number -> real);
    result -> imag = (first_number -> imag) + (second_number -> imag);

    return result;
}