/**
 * @file problem_1.c
 * @author Mostafa Asaad
 * @brief Dynamic Memory Allocation in C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INDEX       122

int main()
{
    /* Define the local variables */
    unsigned int max_lenght = 0, l_counter = 0;
    unsigned char *string = NULL;
    unsigned char max = 0, most_repeated_char = 0;

    /* Define an array for the frequency of each */
    unsigned char *freq = NULL;
    freq = (unsigned char *) calloc(MAX_INDEX + 1, sizeof(unsigned char));

    /* Prompt the user to enter the maximum lenght of the string */
    printf("Enter the maximum lenght of the string: ");
    scanf("%d", &max_lenght);
    fflush(stdin);

    /* Allocate the required memory + the null termination */
    string = (char *) malloc((max_lenght + 1) * sizeof(char));
    
    /* Initialize the allocated memory with null terminators */
    for(l_counter = 0; l_counter < max_lenght; ++l_counter)
        string[l_counter] = '\0';

    /* Prompt the user to enter the string */
    printf("Enter the string: ");
    scanf("%[^\n]s", string);

    /* Print the output */
    printf("You entered: %s\n", string);

    /* Calculate the frequency of the most repeated char */
    for (l_counter = 0; l_counter < strlen(string); ++l_counter)
        { freq[string[l_counter]]++; }

    for (l_counter = 0; l_counter < MAX_INDEX; l_counter++)
        if (freq[l_counter] > max)
        {
            max = freq[l_counter];
            most_repeated_char = l_counter;
        }
    printf("The most repeated character is %c, with frequency %d\n", most_repeated_char, max);

    /* Free the heap */
    free(string);
    free(freq);

    return 0;
}
