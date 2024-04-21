/**
 * @file main.c
 * @author Mostafa Asaad
 * @brief C structs
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char uint8_t;

typedef struct 
{
    int id;         /* 4 Bytes */
    char name[30];  /* 30 Bytes */
    char class_id;  /* One byte */
} test1_t;

typedef struct 
{
    char name[30];  /* 30 Bytes */
    int id;         /* 4 Bytes */
    char class_id;  /* One byte */
} test2_t;

int main(void)
{
    printf("Size of the first  test %d\n", sizeof(test1_t));
    printf("Size of the second test %d\n", sizeof(test2_t));
    printf("Size of the third  test %d\n", sizeof(test3_t));
}
/*
    => In the first test the data will be organized in memory as follows <=
+---+ +---+ +---+ +---+
|id | |id | |id | |id |     => int id <=
+---+ +---+ +---+ +---+ 
| n | | n | | n | | n |     => 30 Byte for the string <=
+---+ +---+ +---+ +---+
| n | | n | | n | | n |
+---+ +---+ +---+ +---+
| n | | n | | n | | n |
+---+ +---+ +---+ +---+
| n | | n | | n | | n |
+---+ +---+ +---+ +---+
| n | | n | | n | | n |
+---+ +---+ +---+ +---+
| n | | n | | n | | n |
+---+ +---+ +---+ +---+
| n | | n | | n | | n |
+---+ +---+ +---+ +---+
| n | | n | | c | |///|     => One byte for the class_id and only one byte padding <=
+---+ +---+ +---+ +---+

So the size is 36 Bytes
===============================================================================================
    => In the second test the data will be organized in memory as follows <=

+---+ +---+ +---+ +---+
| n | | n | | n | | n | {
+---+ +---+ +---+ +---+
| n | | n | | n | | n |
+---+ +---+ +---+ +---+
| n | | n | | n | | n |
+---+ +---+ +---+ +---+
| n | | n | | n | | n |         30 Bytes for the string
+---+ +---+ +---+ +---+
| n | | n | | n | | n |
+---+ +---+ +---+ +---+
| n | | n | | n | | n |
+---+ +---+ +---+ +---+
| n | | n | | n | | n |
+---+ +---+ +---+ +---+
| n | | n | |///| |///| with 2 Bytes padding }
+---+ +---+ +---+ +---+
|id | |id | |id | |id |         4 Bytes for the integer
+---+ +---+ +---+ +---+
| c | |///| |///| |///|         One byte for the character and the remaining three bytes are padding
+---+ +---+ +---+ +---+

So the size is 40 Bytes
*/