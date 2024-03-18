/*
 * A C program takes a string as i/p
 * and prints it. 
*/
#include <stdio.h>
#include <stdlib.h>

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
    /* Prompt the user to enter the sreing */
    printf("Enter the string\n");
    scanf("%[^\n]s", string);
    /* Print the entered string */
    printf("The string you entered is \"%s\".\n", string);
    
    /* Free the heap */
    free(string);
    return 0;
}
