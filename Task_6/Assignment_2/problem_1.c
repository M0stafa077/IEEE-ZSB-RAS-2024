/**
 * @file problem_1.c
 * @author Mostafa Asaad
 * @brief General.
 */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

uint32_t time = 0;

int main()
{       
    /* Define a helper pointer, points to only one byte of the variable */
    uint8_t *working_ptr = NULL;
    working_ptr = &time;
    
    /* Prompt the user to enter the time */
    printf("Enter the time in the format [hh:mm:ss]: ");

    /* 
     * Store the hours in the first byte, minutes in the second byte, 
     * and seconds in the third byte of the integer variable.
     */
    scanf("%d:%d:%d", working_ptr, (working_ptr + 1), (working_ptr + 2));

    /* Print the result */
    printf("The time is %d:%d:%d\n", *(working_ptr), *(working_ptr + 1), *(working_ptr + 2));

    return 0;
}