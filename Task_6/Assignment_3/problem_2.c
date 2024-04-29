/**
 * @file problem_1.c
 * @author Mostafa Asaad
 * @brief sizeof.
 */
#include <stdio.h>
#include <stdlib.h>
#include "Linked_List/single_linked_list.h"

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

uint8_t choice = 0;

Node_t* list_head = NULL;

int main()
{
    while (1)
    {
        system("cls");
        fflush(stdin);        

        printf("Choose operation:\n");
        printf("[+] adds a node.\t[-] deletes a node\n");   
        printf("[p] prints the list.\t[x] stop\n");
        scanf("%c", &choice);
        
        switch (choice)
        {
        case '+':
            uint32_t data = 0;
            printf("Enter the data: ");
            fflush(stdin);
            scanf("%d", &data);
            LinkedList_Insert_End(&list_head, data);
            break;
        case '-':
            uint32_t pos = 0;
            fflush(stdin);
            printf("Enter the position: ");
            scanf("%d", &pos);
            LinkedList_DeletePos(&list_head, pos);    
            break;
        case 'p':
            printf("The linked list data: ");
            LinkedList_Print(&list_head);
            break;    
        case 'x':
            return 0;
        default:
            printf("Invalid Input\n");
            break;
        }
        
        printf("Press enter to continue");
        fflush(stdin);
        getchar();
    }    
}