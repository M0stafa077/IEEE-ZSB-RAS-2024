/**
 * @file Problem_1.c
 * @author Mostafa Asaad
 * @brief C structs.
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_STUDENTS      15

typedef unsigned char uint8_t;

typedef struct
{
    /**
     * @brief String holds the 
     * name of the student.
     */
    uint8_t name[30];
    /**
     * @brief String holds the address
     * of the student. 
     */
    uint8_t address[30];
    /**
     * @brief Marks of the student. 
     */
    float marks;
    /**
     * @brief Age of the student. 
     */
    uint8_t age;
    /**
     * @brief ID of the student.
     * 
     */
    uint8_t roll_number; 
} student_info_t;

student_info_t students_array[NUMBER_OF_STUDENTS] = 
{
    {"Ahmed", "Cairo", 15.0, 18, 1},
    {"Mohamed", "Cairo", 12.0, 18, 2},
    {"Khaled", "Cairo", 13.5, 18, 3},
    {"Ibrahim", "Cairo", 11.7, 18, 4},
    {"Sayed", "Cairo", 10.9, 18, 5},
    {"Bla Bla", "Cairo", 16.0, 18, 6},
    {"Bla Bla", "Cairo", 17.8, 18, 7},
    {"Bla Bla", "Cairo", 20.0, 18, 8},
    {"Bla Bla", "Cairo", 13.0, 18, 9},
    {"Bla Bla", "Cairo", 9.0, 18, 10},
    {"Bla Bla", "Cairo", 6.0, 18, 11},
    {"Bla Bla", "Cairo", 5.0, 18, 12},
    {"Bla Bla", "Cairo", 16.5, 18, 13},
    {"Bla Bla", "Cairo", 17.6, 18, 14},
    {"Bla Bla", "Cairo", 0.0, 18, 15}
};

void print_student_data(student_info_t *student);
void print_student_below_12(student_info_t *student);

int main(void)
{
    printf("All the students\n========================\n");
    for(uint8_t counter = 0; counter < NUMBER_OF_STUDENTS; ++counter)
    {
        print_student_data(&students_array[counter]);        
    }

    printf("====================================================== \n");

    printf("Students with less than 12 degrees: \n");
    for(uint8_t counter = 0; counter < NUMBER_OF_STUDENTS; ++counter)
    {
        print_student_below_12(&students_array[counter]);        
    }
}

void print_student_data(student_info_t *student)
{
    printf("Name    : %s\n", student->name);
    printf("Address : %s\n", student->address);
    printf("Marks   : %.2f\n", student->marks);
    printf("Age     : %d\n", student->age);
    printf("Roll Number: %d\n", student->roll_number);
    printf("=========================== \n");
}

void print_student_below_12(student_info_t *student)
{
    if(student->marks < 12)
        print_student_data(student);
}
