/*
 * A C program separates the individual 
 * characters from a string.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_MAX_SIZE     100

int main(void)
{
    /* Allocate memory for the string */
    char *string = NULL;
    string = (char *) malloc(STRING_MAX_SIZE * sizeof(char));
    if(NULL == string)
    {
        printf("Error allocating memory\n");
        return 1;
    }
    
    /* Initialize the string */
    strcpy(string, "3allawy 7abib gulpy");

    /* print the string */
    unsigned char counter = 0;
    while (string[counter] != '\0')
    {
        printf("%c ", string[counter++]);
    }    
    printf("\n");
    
    /* Free the heap */
    free(string);
 
    return 0;
}