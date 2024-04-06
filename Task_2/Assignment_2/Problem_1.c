/**
 * @file Problem_1.c
 * @author Mostafa Asaaad
 * @brief Exercise on C pointer to function.
 * @version 0.1
 * @date 2024-04-06
 */
#include <stdio.h>

/**
 * @brief A software interface increments an integer value.
 * @param value The value to be incremented.
 */
void incrementInt(int* value);

int main()
{
    /* Declare a pointer to function */
    void (*ptrToFunction)(int*);
    
    /* Assign the function address to the declared pointer */
    ptrToFunction = incrementInt;
    
    /* Define an integer value for testing */
    int value = 10;
    
    /* Print the value before incrementing */
    printf("value before incrementing is %d\n", value);
    
    /* Increment the value using the pointer */
    ptrToFunction(&value);
    
    /* Print the value after incrementing */
    printf("value after  incrementing is %d\n", value);
    
    /* End the program */
    return 0;
}

void incrementInt(int* value)
{
    (*value)++;
}
