/* --------------- Section : Includes --------------- */
#include "single_linked_list.h"
/*---------------  Section: Function Definitions --------------- */
void LinkedList_Insert_Beginning(Node_t **ListHead_ptr, int data)
{
    Node_t *newNode_ptr = NULL;
    newNode_ptr = (Node_t *) malloc(sizeof(Node_t));
    if(NULL == newNode_ptr)
    {
        printf("Error Allocating Memory\n");
        return;
    }
    else
    {      
        newNode_ptr -> data = data;
        newNode_ptr -> next = *ListHead_ptr;
        *ListHead_ptr = newNode_ptr;
    }
}

void LinkedList_Insert_End(Node_t **ListHead_ptr, int data)
{
    if(NULL == ListHead_ptr)
    {
        printf("Invalid List Head Pointer\n");
        return;
    }
    else
    {
        Node_t *newNode_ptr = NULL;
        Node_t *lastNode_ptr = NULL;
        newNode_ptr = (Node_t *) malloc(sizeof(Node_t));
        
        if(NULL == newNode_ptr)
        {
            printf("Error Allocating Memory!\n");
            return;
        }
        else
        {
            if(LinkedList_IsEmpty(ListHead_ptr))
            {
                free(newNode_ptr);  /* We don't need it anymore */
                LinkedList_Insert_Beginning(ListHead_ptr, data);
            }
            else
            {
                newNode_ptr -> data = data;
                newNode_ptr -> next = NULL;
                
                lastNode_ptr = *ListHead_ptr;
                while (NULL != lastNode_ptr -> next)
                { lastNode_ptr = lastNode_ptr -> next; }
                
                lastNode_ptr -> next = newNode_ptr;
            }
        }
    }
}

void LinkedList_Print(Node_t **ListHead_ptr)
{
    if(NULL == ListHead_ptr)
    {
        printf("Invalid List Head Pointer\n");
        return;
    }
    else
    {
        if(LinkedList_IsEmpty(ListHead_ptr))
        { 
            printf("List is Empty\n");
            return;
        }
        else
        {
            Node_t *tempNode_ptr = NULL;
            
            tempNode_ptr = (*ListHead_ptr);
            while (NULL != tempNode_ptr->next)
            {
                printf("%d ", tempNode_ptr->data);
                tempNode_ptr = tempNode_ptr->next;
            }
            
            printf("%d\n", tempNode_ptr -> data);
        }
    }
}

int LinkedList_getSize(Node_t **ListHead_ptr)
{
    if(NULL == ListHead_ptr)
    {
        printf("Invalid List Head Pointer\n");
        return 0;
    }
    else
    {
        int linkedList_size = 0;
        Node_t *temp_list_ptr = *ListHead_ptr;
        while (NULL != temp_list_ptr -> next)
        {
            ++linkedList_size;
            temp_list_ptr = temp_list_ptr->next;
        }
        return linkedList_size + 1;
    }
}

bool LinkedList_IsEmpty(Node_t **ListHead_ptr)
{
    if(NULL == ListHead_ptr)
    {
        printf("Invalid List Head Pointer\n");
        return 0;
    }
    else
    {
        return (NULL == (*ListHead_ptr));
    }
}

void LinkedList_InsertPos(Node_t **ListHead_ptr, int position, int data)
{
    if(NULL == ListHead_ptr)
    {
        printf("Invalid List Head Pointer\n");
        return;
    }
    else
    {
        int ListSize_old = 0;
        ListSize_old = LinkedList_getSize(ListHead_ptr);
        if(position - ListSize_old > 2)
        {
            printf("Index out of boundaries!!\n");
            return;
        }
        
        Node_t *newNode_ptr = NULL;
        newNode_ptr = (Node_t *) malloc(sizeof(Node_t));
        newNode_ptr -> data = data;

        Node_t *tempNode_ptr = (*ListHead_ptr);
        for(int counter = 0; counter < position - 1; ++counter)
        {
            tempNode_ptr = tempNode_ptr -> next;
        }

        newNode_ptr -> next = tempNode_ptr -> next;
        tempNode_ptr -> next = newNode_ptr;
    }
}

void LinkedList_DeletePos(Node_t **ListHead_ptr, int pos) 
{
    --pos;
    if (NULL == ListHead_ptr) 
    {
        printf("Invalid List Head Pointer\n");
        return;
    } 
    else 
    {
        int size = LinkedList_getSize(ListHead_ptr);
        if (pos >= size || pos < 0) 
        {
            printf("Index out of boundaries\n");
            return;
        }

        Node_t *tempNode_ptr = *ListHead_ptr;
        if (pos == 0) 
        {
            *ListHead_ptr = tempNode_ptr->next;
            free(tempNode_ptr);
            return;
        }

        for (int counter = 0; tempNode_ptr != NULL && counter < pos - 1; ++counter) 
            tempNode_ptr = tempNode_ptr->next;

        if (tempNode_ptr == NULL || tempNode_ptr->next == NULL) 
            return;

        Node_t *next = tempNode_ptr->next->next;

        free(tempNode_ptr->next);
        tempNode_ptr->next = next;
    }
}