/**
 * @file Problem_1.c
 * @author Mostafa Asaaad
 * @brief Exercise on C pointers arithmetic.
 * @version 0.1
 * @date 2024-04-06
 */

#include <stdio.h>

int main()
{
    /* A pointer to an integer value */
    int *numPtr = 0;
    
    /* A pointer to a character value */
    char *cPtr = 0;
    
    /* A pointer to a long long value */
    long long* lPtr = 0;

    /* Print the content of the pointers before incrementing them */
    printf("Before Incrementing..\n");
    printf("\tnumPtr : 0x%X\n", numPtr);
    printf("\tcPtr   : 0x%X\n", cPtr);
    printf("\tlPtr   : 0x%X\n", lPtr);
    
    /* Increment the pointer */
    numPtr++, cPtr++, lPtr++;

    /* Print the content of the pointers after incrementing them */
    printf("After Incrementing..\n");    
    printf("\tnumPtr : 0x%X\t// Incremented by 4 bytes (size of integer)\n", numPtr);
    printf("\tcPtr   : 0x%X\t// Incremented by 1 byte  (size of character)\n", cPtr);
    printf("\tlPtr   : 0x%X\t// Incremented by 8 bytes (size of long)\n", lPtr);

    /* End the program */
    return 0;
}
