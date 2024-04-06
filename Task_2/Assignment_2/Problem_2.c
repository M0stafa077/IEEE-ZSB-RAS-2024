/**
 * @file Problem_2.c
 * @author Mostafa Asaaad
 * @brief Exercise on C array traversing using pointers.
 * @version 0.1
 * @date 2024-04-06
 */
#include <stdio.h>

#define ARRAY_SIZE      10

int main()
{
    /* A local counter used in loops. */
    size_t l_counter = 0;   

    /* Declare the array of integers and initialize it with zeros */
    int arrayOfInt[ARRAY_SIZE] = { 0 };

    /* Initialize the array from 1 to ARRAY_SIZE  */
    for(l_counter = 0; l_counter < ARRAY_SIZE; ++l_counter)
        arrayOfInt[l_counter] = l_counter + 1;
    
    /* Declare a pointer points to this array */
    int *ptrToArray = NULL;
    ptrToArray = &arrayOfInt[0];
    
    /* Print the array */
    l_counter = 0;
    while (l_counter < ARRAY_SIZE)
        printf("arrayOfInt[%d] = %d\n", l_counter++, *ptrToArray++);

    /* End the program */
    return 0;
}