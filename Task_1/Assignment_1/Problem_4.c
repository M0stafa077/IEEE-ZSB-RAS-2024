/*
 *  A C program that adds two numbers
 * using call by ref.
*/

#include <stdio.h>

/**
 * @brief A software interface adds two numbers
 * using call by reference
 * 
 * @param firstNumber The first number
 * @param secondNumber The second number
 * @return The result of adding the two numbers. (float) 
 */
float addCallByRef(float *firstNumber, float *secondNumber);

int main(void)
{
    float firstNumber = 5.2, secondNumber = 3.8;

    printf("%.2f + %.2f = %.2f\n", firstNumber, secondNumber, addCallByRef(&firstNumber, &secondNumber));
    
    return 0;
}

float addCallByRef(float *firstNumber, float *secondNumber)
{
    if(NULL == firstNumber || NULL == secondNumber)
    {
        return 0.0;
    }
    else
    {
        return *firstNumber + *secondNumber;
    }

}