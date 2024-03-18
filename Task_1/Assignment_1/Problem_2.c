/*
 * A C program prints all the unique 
* elements in an array.
*/

#include <stdio.h>
#include <stdlib.h>
/*
 * The size of the array 
*/
#define ARRAY_SIZE          8
/* ----------------- Functions Declaration -------------------- */

/**
 * @brief A software interface prints all
 * the unique elements in an array.
 * 
 * @param array a pointer to the array of integers. (int)
 * @param arraySize the size of the array. (int)
 */
void arrayPrintUniqueElements(int *array, int arraySize);

/**
 * @brief A software interface sorts an array of integers 
 * in an ascending order.  
 * 
 * @param array a pointer to the array of integers. (int)
 * @param arraySize the size of the array. (int)
 */
void arraySort(int *array, int arraySize);

int main(void)
{   
    /* Declare and initialize the array */
    int numbers[ARRAY_SIZE] = {5, 1, 2, 4, 5, 4, 1, 0};

    arrayPrintUniqueElements(numbers, ARRAY_SIZE);

    return 0;
}
/* ----------------- Functions Definitions -------------------- */

void arrayPrintUniqueElements(int *array, int arraySize)
{
    if(NULL == array)
    {
        return;
    }
    else
    {
        /* 1. Sort the array */
        arraySort(array, arraySize);
        
        /* 2. Declare the array in which the unique elements will be stored */
        int *uniqueElements_ptr = NULL;
        uniqueElements_ptr = (int *) malloc(arraySize * sizeof(int));
        
        /* 3. Find the unique elements using the two pointers approach */
        int left_ptr = 0, right_ptr = left_ptr + 1, counter = 0;
        while (left_ptr < right_ptr && right_ptr < arraySize)
        {
            if(array[left_ptr] == array[right_ptr])
            {
                left_ptr = right_ptr + 1;
                right_ptr += 2;
            }
            else
            {
                uniqueElements_ptr[counter++] = array[left_ptr];
                ++left_ptr;
                ++right_ptr;
            }
        }

        /* Print the answer */
        printf("The unique elements in the array are: [");
        for(int iterator = 0; iterator < counter; ++iterator)
            { printf("%d, ", uniqueElements_ptr[iterator]); }
        printf("\b\b]\n");

        /* Free the heap */
        free(uniqueElements_ptr);
    }
}

void arraySort(int *array, int arraySize)
{
    if(NULL == array)
    {
        return;
    }
    else
    {
        int key, i, l_counter;
        for (l_counter = 1; l_counter < arraySize; ++l_counter)
        {
            key = array[l_counter];
            i = l_counter - 1;
            while (i >= 0 && array[i] > key)
            {
                array[i + 1] = array[i];
                --i;
            }
            array[i + 1] = key;
        }
    }
}