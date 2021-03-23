#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;

/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Ransika Perera
 */
void PQ_insert(int priority, char * data) {
 //FIX THIS
    Node_ptr_t temp = (Node_ptr_t)malloc(sizeof(Node_t));
    Node_ptr_t tempNode = head;
    temp -> data = data;
    temp -> priority = priority;
    
    if (head==NULL || head->priority<temp->priority) {
        temp->next = head;
        head = temp;
    } else {
        while (tempNode->next!=NULL && tempNode->next->priority>temp->priority) {
            tempNode = tempNode->next;
        }
        temp->next = tempNode->next;
        tempNode->next = temp;
    }
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
  //FIX THIS
    Node_ptr_t temp = head;
    head = head->next;
    return temp;
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}


