/**
 * @file problem_1.c
 * @author Mostafa Asaad
 * @brief Dynamic Memory Allocation in C.
 */

#include <stdio.h>
#include <stdlib.h>

#define MALLOC_SIZE         10
#define CALLOC_SIZE         20
#define CALLOC_SIZE2        25
#define CALLOC_SIZE3        40

int main()
{
unsigned int *first = NULL;
    unsigned int *second = NULL;
    unsigned int *third = NULL;
    unsigned int *fourth = NULL;
    unsigned int l_counter = 0;

    printf("=======================================================\n");
    /* Allocate a space for 10 integers using malloc() */
    first = (unsigned int *) malloc(MALLOC_SIZE * sizeof(unsigned int));
    if(NULL == first)
        { printf("Error allocating memory using malloc() function\n"); return 1; }
    else
        { printf("Allocated memory for %d Integers using malloc() function\n", MALLOC_SIZE); }

    printf("Values Assigned to the allocated memory: \n");
    for(l_counter = 0; l_counter < MALLOC_SIZE; ++l_counter)
        { printf("%d ", first[l_counter]); }
    printf("\nGarbage values\n");
    printf("=======================================================\n");

    /* Allocate a space for 20 integers using calloc() */
    second = (unsigned int *) calloc(CALLOC_SIZE, sizeof(unsigned int));
    if(NULL == second)
        { printf("Error allocating memory using calloc() function\n"); return 1; }
    else
        { printf("Allocated memory for %d Integers using calloc() function\n", CALLOC_SIZE); }
    
    printf("Values Assigned to the allocated memory: \n");
    for(l_counter = 0; l_counter < CALLOC_SIZE; ++l_counter)
        { printf("%d ", second[l_counter]); }
    printf("\nZeros\n");
    printf("=======================================================\n");

    /* Allocate a space for 25 integers using calloc() */
    third = (unsigned int *) calloc(CALLOC_SIZE2, sizeof(unsigned int));
    if(NULL == second)
        { printf("Error allocating memory using calloc() function\n"); return 1; }
    else
        { printf("Allocated memory for %d Integers using calloc() function\n", CALLOC_SIZE2); }
    
    printf("Values Assigned to the allocated memory: \n");
    for(l_counter = 0; l_counter < CALLOC_SIZE2; ++l_counter)
        { printf("%d ", third[l_counter]); }
    printf("\nZeros\n");
    printf("=======================================================\n");

    /* De-allocate the memory allocated with calloc() usign free() */
    free(third);

    /* Allocate a bigger space in memory using calloc */
    fourth = (unsigned int *) calloc(CALLOC_SIZE3, sizeof(unsigned int));
    if(NULL == second)
        { printf("Error allocating memory using calloc() function\n"); return 1; }
    else
        { printf("Allocated memory for %d Integers using calloc() function\n", CALLOC_SIZE3); }
    
    printf("Values Assigned to the allocated memory: \n");
    for(l_counter = 0; l_counter < CALLOC_SIZE3; ++l_counter)
        { printf("%d ", fourth[l_counter]); }
    printf("\nZeros\n");
    printf("=======================================================\n");
    /*
     * If the memory is limited this would help us make use
     * of the de-allocated memory.
     * This ensures that we don't keep allocating memory unnecessarily 
     * and potentially run out of available memory. 
    */
   
   /* Free the heap */
   free(first);
   free(second);
   free(fourth);
}