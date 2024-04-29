/**
 * @file problem_1.c
 * @author Mostafa Asaad
 * @brief sizeof.
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF(TYPE)       ((uint8_t *)(&TYPE + 1) - (uint8_t *)(&TYPE))

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

inline size_t size_of(int type);


int main()
{
    return 0;
}

inline size_t size_of(int type) 
{
    return (size_t)((char *)(&type + 1) - (char *)(&type));
}
