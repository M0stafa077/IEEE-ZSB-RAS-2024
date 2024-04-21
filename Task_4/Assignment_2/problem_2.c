/**
 * @file main.c
 * @author Mostafa Asaad
 * @brief C structs
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char uint8_t;

typedef struct 
{
    char name[30];
    uint8_t age;
} info_t;

info_t mostafa_info = { "Mostafa", 22};
info_t *mostafa_info_ptr = NULL;

int main(void)
{
    mostafa_info_ptr = (info_t *) malloc(sizeof(info_t));
    mostafa_info_ptr = &mostafa_info;

    printf("Name    :%s\n", mostafa_info_ptr->name);
    printf("Age     :%d\n", mostafa_info_ptr->age);

}