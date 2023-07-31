#pragma once

typedef enum STATUS_RESULT {
    WRONG_INPUT = -1,
} STATUS_RESULT;
/** 
 * @brief find the sum of all elements in an integer array
 * @param a_arr: integer array
 * @param a_size: size of the array

 * @return the sum of the a_size first elements in the array
 * @warning if a_arr uninitialized or a_size<=0 - 0 will return
 */
int sum(int* a_arr, int a_size);

/** 
 * @brief find the max element in an integer array
 * @param a_arr: integer array
 * @param a_size: size of the array

 * @return the max element value in the array
 * @warning if a_arr uninitialized or a_size<=0 - error wrong_input will return
 */
int max(int* a_arr, int a_size);

/** 
 * @brief merge two sorted integer arrays into a single sorted array
 * @param a_arr1: integer array1
 * @param a_size1: size of the array1
 * @param a_arr2: integer array2
 * @param a_size2: size of the array2
 * @param a_result: integer array of the merged result
 * @return NONE
 * @warning if a_arr uninitialized or a_size1/a_size2<=0 - 
 *          the result will be uninitialized.
 */
void merge(int* a_arr1, int a_size1, int* a_arr2, int a_size2, int* a_result);

// Create a function to remove duplicates from a given integer array.
// Write a function to perform a binary search on a sorted integer array to find a specific element's index.
// Implement a function to rotate the elements of an integer array by a given number of positions to the right.