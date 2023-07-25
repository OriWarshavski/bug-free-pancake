#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ALLOCATION_ERROR -1
#define SWAP(first, sec, type) { \
type temp = first; \
first = sec; \
sec = temp; \
}
typedef struct Node Node;
typedef struct SingleLinkedList SingleLinkedList;

static Node* allocNewNode(int a_data);
static int insertFirst(SingleLinkedList* a_list, int a_data);

typedef int(*operation_func)(int);
void func_pointers(int* a_arr, size_t a_size, operation_func a_ptr);
/*1) Swap Two Numbers:
Write a function that takes two integer pointers as 
arguments and swaps the values of the integers they point to.*/
void swap_pointers(int* a_first, int* a_second)
{
    SWAP(*a_first, *a_second, int);
}


/*2) Dynamic Memory Allocation:
Write a program that dynamically allocates memory for an 
integer array based on user input for the array size. 
Then, take input for the array elements and print them.*/
int* allocate_array(size_t a_size)
{
    int i, input;
    int* ptr = (int*)malloc(sizeof(int) * a_size);
    if(ptr == NULL) {
        return NULL;
    }
    for(i = 0; i < a_size; ++i) {
        printf("type the %d'th element: ", i + 1);
        scanf("%d", &input);
        ptr[i] = input;
    }
    return ptr;
}

/*3) Array Reversal using Pointers:
Write a function that takes an integer array 
and its size as input and reverses the array using pointers.*/

void reverse_array(int* a_arr, size_t a_size)
{
    int* start = &a_arr[0];
    int* end = &a_arr[a_size - 1];
    while(start < end) {
        SWAP(*start, *end, int);
        ++start;
        --end;
    }
}

/*4) String Length using Pointers:
Implement a function that calculates the length of a string using
pointers (without using the standard library function strlen()).
*/
size_t string_length(char* a_str)
{
    size_t count = 0;
    while(*a_str != '\0') {
        ++count;
        ++a_str;
    }
    return count;
}

/*5) Pointers to Functions:
Create a function that takes an array of integers and its 
size as arguments, and a pointer to a function. This function 
should apply the given function to each element of the array 
and modify the array accordingly.
*/
void func_pointers(int* a_arr, size_t a_size, operation_func a_ptr)
{
    int i;
    for(i = 0; i < a_size; ++i) {
        a_arr[i] = a_ptr(a_arr[i]);
    }
}


int multiply_by_two(int a_num)
{
    return 2 * a_num;
}

// Linked List using Pointers:
// Implement a simple singly linked list using pointers. 
//Create functions to insert elements at the beginning and end, 
//and print the list.

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

/*5) Array of Pointers to Strings:
Create an array of pointers to strings (char arrays). 
Sort the array of strings in lexicographic (alphabetical) order using pointers.
ACBAC*/ 
void sort_strings(char** a_arr, size_t a_size)
{
    int i, j, flag = 1;

    if(a_arr == NULL){
        printf("pointer uninitialized\n");
        return;
    }
    for(i = 0; (i < a_size - 1) && flag; ++i) {
        flag = 0;
        for(j = 0; j < a_size - 1 - i; ++j) {
            if(strcmp(a_arr[j], a_arr[j + 1]) > 0) {
                SWAP(a_arr[j], a_arr[j + 1], char*);
                flag = 1;
            }

        }

    }
}

/*............................................................*/
int main()
{
    //1
    int x = 5, y = 7;
    int* px, *py;
    px = &x;
    py = &y;
    printf("before: px points to:%d, py points to:%d\n", *px, *py);
    swap_pointers(px, py);
    printf("after: px points to:%d, py points to:%d\n", *px, *py);


    //2
    // int size = 5;
    // int* ptr = allocate_array(size);
    // if(ptr == NULL) {
    //     printf("allocation error\n");
    // }
    // for(int i = 0; i < size; ++i) {
    //     printf("%d\n", ptr[i]);
    // }
    // free(ptr);

    //3
    int arr[] = {1, 2, 3, 4, 5};
    reverse_array(arr, 5);
    for(int i = 0; i < 5; ++i) {
        printf("%d\n", arr[i]);
    }

    printf("size of 12345678:%ld\n", string_length("12345678"));

    //4
    int arr2[] = {1, 2, 3, 4, 5};
    size_t size = 5;
    func_pointers(arr2, size, multiply_by_two);
    for(int i = 0; i < 5; ++i) {
        printf("%d\n", arr2[i]);
    }

    //5
    SingleLinkedList* list = create_single_linked();
    insert_to_head(list, 5);
    insert_to_head(list, 10);
    insert_to_head(list, 123);
    single_list_print(list);
    list_destroy(&list);

    //6
    char* strArr[5] = {"a", "c", "b", "a", "c"};
    sort_strings(strArr, 5);
    for(int i = 0; i < 5; ++i) {
        printf("%s, ", strArr[i]);
    }
    putchar('\n');


    
}
/*Working with pointers is an important aspect of programming in C. Here are some exercises that can help you exercise pointers in C:

Pointer to Pointer:
Write a program that uses a pointer to a pointer to swap two integers.
Dynamic Data Structures:
Implement a stack or queue using dynamic memory allocation, and create functions to push/pop or enqueue/dequeue elements.
Pointers and Structures:
Create a structure representing a student with attributes like name, roll number, and marks. Use pointers to allocate memory for the structure and access its members.
Remember to handle memory allocation and deallocation carefully to avoid memory leaks and undefined behavior. These exercises will help you become more comfortable and proficient in working with pointers in C. Happy coding!*/