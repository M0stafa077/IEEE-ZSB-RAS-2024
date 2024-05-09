/**
 * @file problem_1.c
 * @author Mostafa Asaad
 * @brief General.
 */

#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;

#define MAX_LENGHT      100
#define STOP_SIGN       "!!"
#define UNIQUE          1
#define NOT_UNIQUE      0

uint8_t string[MAX_LENGHT];

int main()
{
    while (1) 
    {
        /* Prompt the user to enter the string */
        printf("Enter a string: ");
        fflush(stdin);
        scanf("%[^\n]s", string);

        /* Check for the stop sign */
        if (0 == strcmp(string, STOP_SIGN))
            break;

        printf("The unique characters are: ");
        for (uint8_t counter = 0; counter < strlen(string); ++counter) 
        {
            uint8_t unique_flag = UNIQUE;
            for (int j = 0; j < counter; j++)
            {
                if (string[counter] == string[j])
                {
                    unique_flag = NOT_UNIQUE;
                    break;
                }
            }

            if (unique_flag)
            {
                printf("%c", string[counter]);
            }
        }
        printf("\n=============================== \n");
    }
    return 0;
}
