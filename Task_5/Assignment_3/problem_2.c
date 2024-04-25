/**
 * @file problem_1.c
 * @author Mostafa Asaad
 * @brief Preproccessor
 */

#include <stdio.h>
#include <stdlib.h>

#define ADDITION            0
#define SUBTRACTION         1

#define OPERATION           ADDITION


#define ADD(X, Y)           ((X) + (Y))
#define SUB(X, Y)           ((X) - (Y))

int main()
{
    unsigned int first_number = 0, second_number = 0;
    printf("Enter the first number: ");
    scanf("%d", &first_number);
    
    printf("Enter the second number: ");
    scanf("%d", &second_number);

#if OPERATION == ADDITION
    printf("%d + %d = %d\n", first_number, second_number, ADD(first_number, second_number));
#elif OPERATION == SUBTRACTION
    printf("%d - %d = %d\n",  first_number, second_number, SUB(first_number, second_number));
#endif
}