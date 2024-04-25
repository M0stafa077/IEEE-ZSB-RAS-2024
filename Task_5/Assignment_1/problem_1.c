/**
 * @file problem_1.c
 * @author Mostafa Asaad
 * @brief Bit fields and typedef keyword in C language.
 */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char       uint8_t;

typedef struct
{
    uint8_t age             :8;
    uint8_t roll_number     :4;
    uint8_t marks           :3;
    uint8_t reserved        :1; 
    uint8_t name[30];
    uint8_t address[30];
} student_info_t;

void print_student_data(student_info_t *student);

student_info_t students_array[15] = 
{
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"},
    {.age = 18, .roll_number = 1, .marks = 6, .name = "Eivor Of The Raven Clan", .address = "Ravensthorpe"}
};

int main(void)
{
    for(uint8_t counter = 0; counter < 15; ++counter)
        print_student_data(&students_array[counter]);
        

    printf("Size of the struct is %i Bytes\n", sizeof(student_info_t));
    return 0; 
}

void print_student_data(student_info_t *student)
{
    printf("Name        : %s\n", student -> name);
    printf("Address     : %s\n", student -> address);
    printf("Marks       : %i\n", student -> marks);
    printf("Age         : %i\n", student -> age);
    printf("Roll Number : %i\n", student -> roll_number);
    printf("=========================== \n");
}

/*
 * The processor assigns the memory for the struct as follows:
 * First Byte for: age as it's 8-bits
 * Second Byte is shared between roll_number, marks and a single reserved bit 
 * |age|age|age|age|marks|marks|marks|reserved|
 * MSB                                    LSB
 * 30 Bytes for the name
 * 30 Bytes for the address
 * (Bit-fields) cannot be applied on strings
 * So the total size of the struct is 62 Bytes
 */