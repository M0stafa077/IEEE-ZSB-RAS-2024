/*
 * A C program compares two strings.
 * strcpy() function implementation.   
*/
#include <stdio.h>

/**
 * @brief A software interface copies one string 
 * to another one.
 * 
 * @param str1 The copied string.
 * @param str2 The target string.
 */
void stringCopy(char *str1, char *str2);

int main(void)
{
    char s1[13] = "I'm a string";
    char s2[13] = "I'm Nothing";

    printf("Before:\n");
    printf("===========================\n");
    printf("string 1: %s\n", s1);
    printf("string 2: %s\n", s2);

    stringCopy(s1, s2);

    printf("After:\n");
    printf("===========================\n");
    printf("string 1: %s\n", s1);
    printf("string 2: %s\n", s2);
}

void stringCopy(char *str1, char *str2)
{
    int counter = 0;
    while (str1[counter] != '\0')
    {
        str2[counter++] = str1[counter];
    }
    str2[counter] = '\0';
} 