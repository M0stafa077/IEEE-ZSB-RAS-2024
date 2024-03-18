/*
 * A C program solves the problem :)
*/

#include <stdio.h>

int main(void)
{
    /* 1. Declare the Three variables */
    int x = 1, y = 2, z = 3;
    
    /* 2. Declare the Three pointers  */
    int *p = &x, *q = &y, *r = &z;
    
    /* 3. Print the values */
    printf("==========================================\n");
    printf(" x = %d,  y = %d,  z = %d\n", x, y, z);
    printf(" p = %d,  q = %d,  r = %d\n", p, q, r);
    printf("*p = %d, *q = %d, *r = %d\n", *p, *q, *r);

    /* 4. Swap the pointers */
    printf("============ Swapping Pointer ============\n");
    int *temp = r;
    r = p;
    p = q;
    q = temp;

    /* 5. Print the values */
    printf(" x = %d,  y = %d,  z = %d\n", x, y, z);
    printf(" p = %d,  q = %d,  r = %d\n", p, q, r);
    printf("*p = %d, *q = %d, *r = %d\n", *p, *q, *r);
    printf("==========================================\n");
}