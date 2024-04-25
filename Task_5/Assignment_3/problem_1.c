/**
 * @file problem_1.c
 * @author Mostafa Asaad
 * @brief Preproccessor
 */

#include <stdio.h>
#include <stdlib.h>

#define ASC_SORTING     0
#define DSC_SORTING     1

#define SORT_TYPE       ASC_SORTING

/* Ascending sort function */
void ASC_sort(int *array, int size)
{
    int key, i, f_counter;
    for (f_counter = 1; f_counter < size; ++f_counter)
    {
        key = array[f_counter];
        i = f_counter - 1;
        while (i >= 0 && array[i] > key)
        {
            array[i + 1] = array[i];
            --i;
        }
        array[i + 1] = key;
    }
}
/* Descending sort function */
void DSC_sort(int *array, int size)
{
    int key, i, f_counter;
    for (f_counter = 1; f_counter < size; ++f_counter)
    {
        key = array[f_counter];
        i = f_counter - 1;
        while (i >= 0 && array[i] < key)
        {
            array[i + 1] = array[i];
            --i;
        }
        array[i + 1] = key;
    }
}

void print_array(unsigned int *array_ptr, unsigned int array_size);

int main()
{
    unsigned int array_size = 0, counter = 0;
    unsigned int *array = NULL;
    
    printf("Enter the array size: ");
    scanf("%d", &array_size);
    array = (unsigned int *) malloc(array_size * sizeof(unsigned int));
   
    printf("Enter the numbers: ");
    for(unsigned int l_counter = 0; l_counter < array_size; ++l_counter)
    {
        scanf("%d", &array[counter++]);
    }

    printf("Numbers before sorting: \n");
    print_array(array, array_size);

    #if SORT_TYPE==ASC_SORTING
    ASC_sort(array, array_size);
    #elif SORT_TYPE==DSC_SORTING
    DSC_sort(array, array_size);
    #endif
    
    printf("Numbers after sorting: \n");
    print_array(array, array_size);
}   

void print_array(unsigned int *array_ptr, unsigned int array_size)
{
    for(unsigned int l_counter = 0; l_counter < array_size; ++l_counter)
    {
        printf("%d ", array_ptr[l_counter]);
    }
    printf("\n");
}