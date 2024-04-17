/**
 * @file main.c
 * @author Mostafa Asaad
 * @brief Difference between pre-processor directives conditions
 * and normal C conditions.
 */

#include <stdio.h>

int main(void)
{
    /* 
     * Pre-Processor directive #if, #ifdef, #else etc are 
     * processed at the compilation time, so they never get executed by the cpu
     * as they're text replaced in the preprocessor stage in the compilation process
     * 
     * Pre-processor directives ( #if, #ifdef, #else etc) work only with defined directives
     * using #define, and if it's used with global or local variables, these variables are
     * replaced with 0
     * 
     * Normal if, else are exceccuted during the run-time after the compilation 
     */

    /* Here's some examples */

    /* 1. Using normal variables with pre-processed #if and #else */
    int number = 5;
#if number==5
    printf("#if is excecutd \n");
#else
    printf("#else is excecuted because number will be replaced with 0\n");
#endif
    /* The same variable with the same conditions with normal if, else */
    if(5 == number)
        printf("Normal if is excecuted because number equals 5\n");
    else
        printf("Normal else is excecuted \n");

    /* 2. Using defined macros with pre-processor directives */
#define NUMBER      5
#if NUMBER==5
    printf("#if is excecuted because NUMBER will be replaced with 5\n");
#else
    printf("#else is excecuted \n");
#endif
    
    /* 3.Using random text with pre-processor directives */
#if ABC==5
    printf("#if is excecuted \n");
#else
    printf("#else is excecuted because ABC will be replaced with 0\n");
#endif

    /* 4. Using #ifdef and #ifndef */
#define X   5

#ifdef X
    printf("X is defined\n");
#endif

#ifndef X
    printf("X is not defined\n");
#endif  
}