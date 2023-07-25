#ifndef __POINTERS_H__
#define __POINTERS_H__

//////////////////////////////////////////////FUNC POINTERS//////////////////////////////////////////////////////////////
typedef int(*operation_func)(int);
void func_pointers(int* a_arr, size_t a_size, operation_func a_ptr);
//////////////////////////////////////////////FUNC POINTERS//////////////////////////////////////////////////////////////

//////////////////////////////////////////////SINGLE LINKED LIST/////////////////////////////////////////////////////////
// Linked List using Pointers:
// Implement a simple singly linked list using pointers. 
//Create functions to insert elements at the beginning and end, 
//and print the list.
#define ALLOCATION_ERROR -2
#define SWAP(first, sec, type) { \
type temp = first; \
first = sec; \
sec = temp; \
}
typedef struct Node Node;
typedef struct SingleLinkedList SingleLinkedList;

/** 
 * @brief Creates single_linked
 * @param none
 * @return  pointer to the list.
 * @warning NULL will return if: allocation failed.
 */
SingleLinkedList* create_single_linked();

/** 
 * @brief Destroys initialized list.
 * @param a_list: pointer to hash poiter to destroy.
 * @return NONE.
 * @warning **_hash and *_hash must be initialized! 
 */
void list_destroy(SingleLinkedList** a_list);

/** 
 * @brief Insert data to the head of the list.
 * @param a_list: pointer to the list
 * @param a_data: pointer to data to insert
 * @return none ---> need to update to:
    * @retval SET_UNINITIALIZED - _hash/_data uninitialized
    * @retval SET_OVERFLOW - hash is full (capacity == numOfItems).
    * @retval SET_KEY_DUPLICATE - data has already in the hash, duplicate is forbidden.
 */
void insert_to_head(SingleLinkedList* a_list, int a_data);

/** 
 * @brief Insert data to the end of the list.
 * @param a_list: pointer to the list
 * @param a_data: pointer to data to insert
 * @return none ---> need to update to:
    * @retval SET_UNINITIALIZED - _hash/_data uninitialized
    * @retval SET_OVERFLOW - hash is full (capacity == numOfItems).
    * @retval SET_KEY_DUPLICATE - data has already in the hash, duplicate is forbidden.
 */
void insert_linked_list(SingleLinkedList* a_list, int a_data);

/** 
 * @brief Prints the items int list.
 * @param a_list: pointer to the list.
 * @return none.
 * @warning if _hash/PrintKey uninitialized or the hash is empty - nothing will be printed.
 */
void single_list_print(SingleLinkedList* a_list);
//////////////////////////////////////////////SINGLE LINKED LIST/////////////////////////////////////////////////////////

#endif /* __POINTERS_H__ */
