/**
 * @file enums.c
 * @author Mostafa Asaad
 * @brief Enums in C
 */

#include <stdio.h>

typedef enum 
{
    ADD = 0x2B,
    SUB = 0x2D,
    MUL = 0x2A,
    DIV = 0x2F,
    AND = 0x26,
    OR  = 0x7C,
    NOT = 0x21
} operation_t;

int main()
{
    float first_number = 0, second_number = 0;
    char choice = '\0';

    printf("Size = %d\n", sizeof(enum operation));

    printf("Enter the first  number: ");
    scanf("%f", &first_number);
    
    printf("Enter the second number: ");
    scanf("%f", &second_number);

    printf("Choose the operation\n");
    printf("+\t-\t*\n/\t&\t|\n!\n");
    fflush(stdin);
    scanf("%c", &choice);

    switch (choice)
    {
    case ADD:
        printf("%.2f + %.2f = %.2f\n", first_number, second_number, (first_number + second_number));
        break;
    case SUB:
        printf("%.2f - %.2f = %.2f\n", first_number, second_number, (first_number - second_number));
        break;
    case MUL:
        printf("%.2f * %.2f = %.2f\n", first_number, second_number, (first_number * second_number));
        break;
    case DIV: 
        if(second_number != 0)
            printf("%.2f / %.2f = %.2f\n", first_number, second_number, (first_number / second_number));
        else
            printf("Error!! Division by zero\n");
        break;
    case AND :
        printf("%d & %d = %d\n", (unsigned int)first_number, (unsigned int)second_number, 
                                    ((unsigned int)first_number & (unsigned int) second_number));
        break;
    case OR:
        printf("%d | %d = %d\n", (unsigned int)first_number, (unsigned int)second_number, 
                                    ((unsigned int)first_number | (unsigned int)second_number));
        break;
    case NOT:
        printf("!(%d) = %d\n!(%d) = %d\n", (unsigned int)first_number, !(unsigned int)first_number, 
                                            (unsigned int)second_number, !(unsigned int)second_number);
        break;
    default:
        printf("INVALID INPUT\n");
        break;
    }
    
    printf("==================================================\n");
    printf("Size of the enum is %d\n", sizeof(operation_t));
    /*
     * The size of this enum is 4 Bytes
     * as its members are assigned to int type
     * Adding more members will not affect the size of the enum 
    */
}