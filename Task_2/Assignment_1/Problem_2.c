/**
 * @file Problem_1.c
 * @author Mostafa Asaaad
 * @brief Exercises on C pointers arithmetic.
 * @version 0.1
 * @date 2024-04-06
 */
#include<stdio.h>

int a = 0x121212;
int b = 2;
int c = 3;
int* ptr = NULL;

int main()
{
    printf("-----------------------\n");

    /* ------------- First operation : *ptr++ ----------------- */
    ptr = &a;
    printf("*ptr++ : 0x%X\n", *ptr++);

    /*
    * output is 0x121212
    * As this operation (*ptr++)
    * is compiled as follows:
    *      1: printing *ptr which is (a) or (0x121212)
    *      2: Post-Incrementing the pointer by 1 (or 4 Bytes)
    *          which is the size of the integer value.
    */

    /*
    * And since we're dealing with global variables,
    * these variables are stored in the
    * the data section in main memory.
    * which is as follows before the *ptr++ operation:
    *                ---------------
    *               |      ...      |
    *                ---------------
    *               |   ptr = 1000  | e.x. @1020 -- as ptr is stored in 8 bytes (On my machine)
    *                ---------------  
    *               |    d = 4      | e.x. @1012
    *                ---------------  
    *               |    c = 3      | e.x. @1008
    *                ---------------
    *               |    b = 2      | e.x. @1004
    *                ---------------
    *               | a = 0x121212  | e.x. @1000
    *                ---------------
    *               |     .data     | 
    *                ---------------
    * 
    * But after the operation becomes:
    *                ---------------
    *               |      ...      |
    *                ---------------
    *               |   ptr = 1004  | e.x. @1020 -- as ptr is stored in 8 bytes (On my machine)
    *                ---------------  
    *               |    d = 4      | e.x. @1012
    *                ---------------  
    *               |    c = 3      | e.x. @1008
    *                ---------------
    *               |    b = 2      | e.x. @1004
    *                ---------------
    *               | a = 0x121212  | e.x. @1000
    *                ---------------
    *               |     .data     |
    *                ---------------
    */
    printf("-----------------------\n");

    /* ------------ Second operation : *++ptr ---------------- */
    printf("*++ptr : 0x%X\n", *++ptr);
    /*
    * output is 0x3
    * As this operation (*++ptr)
    * is compiled as follows:
    *      1: Pre-Incrementing the pointer by 1 (or 4 Bytes)
    *          which is the size of the integer value.
    *      2: printing *ptr which is (c) or (0X3)
    */
    /* The same as first operation */
    printf("-----------------------\n");
    
    /* ----------------- Third operation : ++*ptr ------------- */
    printf("++*ptr : 0x%X\n", ++*ptr);
    /*
    * output is 0x4
    * As this operation (*++ptr)
    * is compiled as follows:
    *       1: Accessing the contntt of the address pointed by ptr
    *       2: Pre-Incrementing this content which is (c) ot (0x3) + 0x1 = 0x4
    */
    /* The same as first operation */

   printf("-----------------------\n");
    return 0;
}
