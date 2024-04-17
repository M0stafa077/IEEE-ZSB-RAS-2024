/**
 * @file operations.c
 * @author Mostafa Asaad
 * @brief A source file contains the implementation
 * of the software interfaces for the calculator app.
*/

/* ----------- Includes ----------- */
#include "operations.h"

/* ----------- Functions Definitions ----------- */
void header_msg(void)
{
    printf(" ------------------------------\n");
    printf("|           Calculator         |\n");
    printf(" ------------------------------\n");
    printf("Operations: \n");
    printf("[1] Addition.\t\t[2] Subtraction\n");
    printf("[3] Multiplication.\t[4] Division\n");
    printf("Chose Operation: ");
}

void add(float first_num, float second_num)
{
    printf("%.2f + %.2f = %.2f\n", first_num, second_num, (first_num + second_num));
}

void sub(float first_num, float second_num)
{
    printf("%.2f - %.2f = %.2f\n", first_num, second_num, (first_num - second_num));
}

void mul(float first_num, float second_num)
{
    printf("%.2f * %.2f = %.2f\n", first_num, second_num, (first_num * second_num));
}

void divide(float first_num, float second_num)
{
    if(0 == second_num)
        printf("Arithematic error: [Division by zero]\n");
        
    else
        printf("%.2f / %.2f = %.2f\n", first_num, second_num, (first_num / second_num));
}
