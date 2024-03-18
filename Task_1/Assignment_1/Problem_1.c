/*
 * A C program counts the number of
 * duplicate elements in an array.
*/
#include <stdio.h>
/*
 * The size of the array 
*/
#define ARRAY_SIZE          7
/* ----------------- Functions Declaration -------------------- */

/**
 * @brief A software interface calculates the number
 * of duplicates in an array.
 * 
 * @param array a pointer to the array of integers. (int)
 * @param arraySize the size of the array. (int)
 * @return duplicates_n: the number of duplicates (int).
 */
int arrayGetDuplicates(int *array, int arraySize);

/**
 * @brief A software interface sorts an array of integers 
 * in an ascending order using insertion sort algorithm.  
 * 
 * @param array a pointer to the array of integers. (int)
 * @param arraySize the size of the array. (int)
 */
void arraySort(int *array, int arraySize);

int main(void)
{   
    /* Declare and initialize the array */
    int numbers[ARRAY_SIZE] = {5, 1, 2, 4, 5, 4, 1};
    /* Print the solution */
    printf("Number of duplicates : %d", arrayGetDuplicates(numbers, ARRAY_SIZE));
    return 0;
}

/* ----------------- Functions Definitions -------------------- */

int arrayGetDuplicates(int *array, int arraySize)
{
    if(NULL == array)
    {
        return -1;
    }
    else
    {
        int duplicates_n = 0;
        /* 1. First we sort the array in an ascending order */
        arraySort(array, arraySize);
        /* 2. We find the duplicates using two pointers approach */
        int left_ptr, right_ptr;
        left_ptr = 0, right_ptr = left_ptr + 1;
        for(left_ptr = 0; left_ptr < ARRAY_SIZE; ++left_ptr)
        {
            while (left_ptr < right_ptr && right_ptr < arraySize)
            {
                if(array[left_ptr] == array[right_ptr])
                {
                    ++duplicates_n;
                    ++right_ptr;
                }
                else
                {
                    left_ptr = right_ptr;
                    ++right_ptr;
                }
            }
        }
        return duplicates_n;
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
        int key = 0, i = 0, iterator = 0;
        for (iterator = 1; iterator < arraySize; ++iterator)
        {
            key = array[iterator];
            i = iterator - 1;
            while (i >= 0 && array[i] > key)
            {
                array[i-- + 1] = array[i];
                // --i;
            }
            array[i + 1] = key;
        }
    }
}