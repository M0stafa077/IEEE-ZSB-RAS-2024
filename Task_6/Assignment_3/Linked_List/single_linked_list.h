/* --------------- Section : Includes --------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* --------------- Section: Data Type Declarations --------------- */
typedef struct node
{
    int data;
    struct node *next;
} Node_t;
/*---------------  Section: Function Declarations --------------- */

/**
 * @brief A software Interface inserts a new node in
 * the begining of a linked-list.
 * @param ListHead_ptr A pointer to the linked-list head pointer.
 * @param data The data to be inserted.
 */
void LinkedList_Insert_Beginning(Node_t **ListHead_ptr, int data);
/**
 * @brief A software Interface inserts a new node in
 * the end of a linked-list.
 * @param ListHead_ptr A pointer to the linked-list head pointer.
 * @param data The data to be inserted.
 */
void LinkedList_Insert_End(Node_t **ListHead_ptr, int data);
/**
 * @brief A software Interface inserts a new node in
 * the certain position of a linked-list.
 * @param ListHead_ptr A pointer to the linked-list head pointer.
 * @param position The position to the data to be inserted at.
 * @param data The data to be inserted.
 */
void LinkedList_InsertPos(Node_t **ListHead_ptr, int position, int data);
/**
 * @brief A software Interface Checks if a linked-list is empty. 
 * @param ListHead_ptr A pointer to the linked-list head pointer.
 * @return true if the list is empty
 * @return false if the list is not empty
 */
bool LinkedList_IsEmpty(Node_t **ListHead_ptr);
/**
 * @brief A software Interface returns the size of a linked-list.
 * @param ListHead_ptr A pointer to the linked-list head pointer.
 * @return int the size of the linked-list
 */
int LinkedList_getSize(Node_t **ListHead_ptr);
/**
 * @brief A software Interface prints the content of a linked-list
 * @param ListHead_ptr A pointer to the linked-list head pointer.
 */
void LinkedList_Print(Node_t **ListHead_ptr);
/**
 * @brief A software Interface deletes a certain node. 
 * @param ListHead_ptr A pointer to the linked-list head pointer.
 * @param pos The position of the node to be deleted.
 */
void LinkedList_DeletePos(Node_t **ListHead_ptr, int pos);
