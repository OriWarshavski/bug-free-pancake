#include <stdio.h>      /*printf*/
#include <stdlib.h>     /*malloc*/
#include <errno.h>      /*errno*/

#include "pointers.h"
//////////////////////////////////////////////SINGLE LINKED LIST/////////////////////////////////////////////////////////
static Node* allocNewNode(int a_data);
static int insertFirst(SingleLinkedList* a_list, int a_data);

struct Node {
    int m_data;
    Node* m_next; 
};

struct SingleLinkedList {
    Node* m_head;
};

SingleLinkedList* create_single_linked()
{
    SingleLinkedList* list = (SingleLinkedList*)(malloc(sizeof(SingleLinkedList)));
    if(list == NULL) {
        printf("allocation error: %d", errno);
        return NULL;
    }
    list -> m_head = NULL;
    return list;
}

void insert_to_head(SingleLinkedList* a_list, int a_data)
{
    Node* head;
    //insert first data to head OR allocation fail:
    if(insertFirst(a_list, a_data) != 0) {
        return;
    }

    //allocate new Node
    if((head = allocNewNode(a_data)) == NULL) {
        return;
    }
    head->m_next = a_list -> m_head;
    a_list -> m_head = head;
}

void insert_linked_list(SingleLinkedList* a_list, int a_data)
{
    Node* itr = a_list->m_head;
    Node* prev = itr;
    //insert first data to head OR allocation fail:
    if(insertFirst(a_list, a_data) != 0) {
        return;
    }
    itr = itr->m_next;
    while(itr != NULL) {
        prev = itr;
        itr = itr->m_next;
    }

    //allocate new Node
    if((itr = allocNewNode(a_data)) == NULL) {
        return;
    }
    itr->m_next = NULL;
    prev->m_next = itr;
}

void single_list_print(SingleLinkedList* a_list)
{
    Node* itr = a_list->m_head;
    while(itr != NULL) {
        printf("%d, ", itr->m_data);
        itr = itr -> m_next;
    }
    putchar('\n');
}

void list_destroy(SingleLinkedList** a_list)
{
    Node* cur, *prev;
    if(a_list == NULL || *a_list == NULL){
        return;
    }
    //free nodes
    cur = (*a_list) -> m_head;
    while(cur != NULL) {
        prev = cur;
        cur = cur -> m_next;
        free(prev);
    }
    free(*a_list);
}

static int insertFirst(SingleLinkedList* a_list, int a_data)
{
    if(a_list->m_head == NULL) {
        if((a_list->m_head = (Node*)malloc(sizeof(Node))) == NULL) {
            printf("allocation error: %d", errno);
            return -1;
        }
        a_list->m_head->m_next = NULL;
        a_list->m_head->m_data = a_data;
        return 1;
    }
    return 0;
}

static Node* allocNewNode(int a_data)
{
    Node* n;
    if((n = (Node*)malloc(sizeof(Node))) == NULL) {
        printf("allocation error: %d", errno);
    }
    else {
        n->m_data = a_data;
    }
    return n;
}

//////////////////////////////////////////////SINGLE LINKED LIST/////////////////////////////////////////////////////////
