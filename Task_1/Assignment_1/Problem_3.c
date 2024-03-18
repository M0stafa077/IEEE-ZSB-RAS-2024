/*
 *  A C program that counts the frequency of each
 * element in an array
*/
#include <stdio.h>
#include <stdlib.h>
/*
 * The size of the array 
*/
#define ARRAY_SIZE          7

#define VISITED             0
/* ----------------- Functions Declaration -------------------- */ 

/**
 * @brief A software interface counts the frequency of each element 
 * in an array and print them.
 * 
 * @param array a pointer to the array of integers. (int)
 * @param arraySize the size of the array. (int)
 */
void arrayCountElementFreq(int *, int arraySize);

int main(void)
{
    /* Declare and initialize the array */
    int numbers[ARRAY_SIZE] = {5, 1, 2, 4, 5, 4, 1};
    
    arrayCountElementFreq(numbers, ARRAY_SIZE);

    return 0;
}

void arrayCountElementFreq(int *array, int arraySize)
{
    if(NULL == array)
    {
        return;
    }
    else
    {
        /* Declare and allocate memory for the frequency array */
        int *freq = NULL;
        freq = (int *) malloc(arraySize * sizeof(int));
        /* Initialize the array with -1 */
        for(int iterator = 0; iterator < arraySize; ++iterator)
            { freq[iterator] = -1; }
        
        // int freq[arraySize] = { NOT_VISITED };

        /* Find the frequency of the elements using two pointers approach */
        int left_ptr = 0, right_ptr = left_ptr + 1;
        for(; left_ptr < arraySize; ++left_ptr)
        {
            int count = 1;
            /* Visit the same number in all the array and calc. its frequency */
            right_ptr = left_ptr + 1;
            while (right_ptr < arraySize)
            {
                if(array[left_ptr] == array[right_ptr])
                {
                    ++count;
                    freq[right_ptr] = VISITED;
                }
                right_ptr++;
            }
            /* Assign the calculated frequency to the number */
            if(VISITED != freq[left_ptr])
            {
                freq[left_ptr] = count;
            }            
        }
        /* Print the array elements */
        printf("     element     :[");
        for(int iterator = 0; iterator < arraySize; ++iterator)
        {   if(VISITED != freq[iterator])
                { printf("%d, ", array[iterator]); }
        }
        printf("\b\b]\n");

        /* Print the frequency of each element */
        printf("element frequency:[");
        for(int iterator = 0; iterator < arraySize; ++iterator)
        { 
            if(VISITED != freq[iterator])
                { printf("%d, ", freq[iterator]); }
        }
        printf("\b\b]\n");

        /* Free the heap */
        free(freq);
    }
}