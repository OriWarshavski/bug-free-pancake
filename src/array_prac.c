#include "array_prac.h"
#include <stdio.h>
#include <stdlib.h>
int sum(int* a_arr, int a_size)
{
    int i;
    int sum = 0;
    if(a_arr == NULL || a_size <= 0) {
        return WRONG_INPUT;
    }

    for(i = 0; i < a_size; ++i) {
        sum += a_arr[i];
    }
    return sum;
}

int max(int* a_arr, int a_size)
{
    int i, max;
    if(a_arr == NULL ||a_size <= 0) {
        return WRONG_INPUT;
    }
    max = a_arr[0];
    for(i = 1; i < a_size; ++i) {
        if(a_arr[i] > max) {
            max = a_arr[i];
        }
    }
    return max;
}

void merge(int* a_arr1, int a_size1, int* a_arr2, int a_size2, int* a_result)
{
    int i = 0, j = 0, k = 0;
    if(a_arr1 == NULL || a_arr2 == NULL || a_size1 <= 0 
        || a_size2 <= 0) {
        return;
    }

    while(i < a_size1 && j < a_size2) {
        while((i < a_size1) && (a_arr1[i] <= a_arr2[j])) {
            a_result[k] = a_arr1[i];
            ++i;
            ++k;
        }
        while((j < a_size2) && (a_arr2[j] <= a_arr1[i])) {
            a_result[k] = a_arr2[j];
            ++j;
            ++k;
        }
    }
    while(i < a_size1) {
        a_result[k] = a_arr1[i];
        ++i;
        ++k;
    }
    while(j < a_size2) {
        a_result[k] = a_arr2[j];
        ++j;
        ++k;
    }
}
