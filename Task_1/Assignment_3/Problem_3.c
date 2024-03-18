/*
 * A C program compares two strings.
 * strcmp() function implementation.   
*/
#include <stdio.h>

#define STRING_MAX_SIZE     100

/**
 * @brief A software interface compares two strings
 * 
 * @param str1 The first string 
 * @param str2 The second string
 * @return char The result:
 *          -1 -> if str1 is less than str2.
 *          0  -> if both strings are identical.
 *          1  -> if str1 is greater than str2.
 */
char stringCompare(char *str1, char *str2);

int main(void)
{
    /* Define the two strings */
    char string1[STRING_MAX_SIZE] = { '\0' };
    char string2[STRING_MAX_SIZE] = { '\0' };
    
    /* Get the strings from user */
    printf("Enter the first  string: ");
    scanf("%[^\n]s", string1);
    fflush(stdin);
    printf("Enter the second string: ");
    scanf("%[^\n]s", string2);

    /* Call the function */
    char result = stringCompare(string1, string2);
    
    /* Print the result */
    if(0 == result)
    { printf("Two strings are identical!\n"); }
    else if(1 == result)
    { printf("String 1 is greater than String 2\n"); }
    else if(-1 == result)
    { printf ("String 1 is less than String 2"); }
    
    return 0;
}

char stringCompare(char *str1, char *str2)
{
    while (('\0' != *str1) && ('\0' != *str2) && (*str1 == *str2))
    {
        ++str1; 
        ++str2;
    }

    if(*str1 == *str2)
        {  return 0; }
    else if(*str1 - *str2 > 0)
        {  return 1; }
    else
        { return -1; }
    
}