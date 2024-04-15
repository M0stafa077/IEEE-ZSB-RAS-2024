/**
 * @file calculator.c
 * @author Mostafa Asaad
 * @brief A simple calculator in C.
*/

/* ----------- Includes ----------- */
#include "operations\operations.h"

/* ----------- Global Variables ----------- */

/**
 * @brief A pointer to function dynamically
 * calls the specified operation. 
 */
void (*operation)(float, float) = NULL;
/**
 * @brief Working variable holds the chosen
 * operation by the user. 
 */
uint8_t choice = 0;
/**
 * @brief The first number for the operation
 */
float first_num = 0.0;
/**
 * @brief The second number for the operation
 */
float second_num = 0.0;

/* ----------- Main Function ----------- */
int main()
{
    while (1)
    {
        /* Display the header message */
        header_msg();   

        /* Get the choice from user */
        fflush(stdin); scanf("%d", &choice);

        /* Process the choice */
        switch(choice)
        {
            case 1: operation = add;
                break;
            case 2: operation = sub;
                break;
            case 3: operation = mul;
                break;
            case 4: operation = divide;
                break;
            default: operation = NULL;
                break;
        }

        if(operation)
        {
            /* Get the first number */
            printf("Enter the first number: ");
            scanf("%f", &first_num);

            /* Get the second number */
            printf("Enter the second number: ");
            scanf("%f", &second_num);

            /* Perform the operation */
            operation(first_num, second_num);
        }
        else
        {
            printf("Invalid Input\n");
        }
        
        /* Exit the app or start a new operation */
        printf("Press enter to continue.\nOr [q] to Quit ");
        fflush(stdin); 
        
        char c = (char) getchar();
        if(('q' == c) || ('Q' == c))
        {
            return 0;
        }
        
        /* Clear the screen */
        system("cls"); 
    }    
}

