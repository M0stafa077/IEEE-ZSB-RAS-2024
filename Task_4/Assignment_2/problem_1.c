/**
 * @file main.c
 * @author Mostafa Asaad
 * @brief C structs
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

typedef struct 
{
    uint16_t year;
    uint8_t month;
    uint8_t day; 
} date_t;


void get_date(date_t *dateObj);
uint8_t are_equal(date_t *first_date, date_t *second_date);

int main(void)
{
    date_t first_date, second_date;

    get_date(&first_date);
    get_date(&second_date);

    if(are_equal(&first_date, &second_date))
        printf("Dates are equal\n"); 
    else
        printf("Dates are not equal\n");
}

void get_date(date_t *dateObj)
{
    char input_date[11] = { '\0' };
    printf("Enter the date in this form dd/mm/yyyy \n");
    scanf("%s", input_date);

    char *token = strtok(input_date, "/");
    if(token != NULL)
        dateObj->day = atoi(token);
    
    token = strtok(NULL, "/");
    if(token != NULL)
        dateObj->month = atoi(token);

    token = strtok(NULL, "/");
    if(token != NULL)
        dateObj->year = atoi(token);
}

uint8_t are_equal(date_t *first_date, date_t *second_date)
{
    return (first_date->day == second_date->day) && (first_date->month == second_date->month) 
            && (first_date->year == second_date->year);
}