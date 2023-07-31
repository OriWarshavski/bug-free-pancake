#include "stack_doubles.h"
#include <stdlib.h>

typedef struct StackDoubles {
    double* m_values;
    int m_topIndex; //index for insertion new top
    int m_maxSize;
} StackDoubles;

StackDoubles* StackDoublesCreate(int a_maxSize)
{
    StackDoubles* pStack;
    if(a_maxSize <= 0) {
        return NULL;
    }
    if((pStack = (StackDoubles*)malloc(sizeof(StackDoubles))) == NULL) {
        return NULL;
    }
    if((pStack -> m_values = (double*)malloc(sizeof(double) * a_maxSize)) == NULL) {
        free(pStack);
        return NULL;
    }
    pStack -> m_topIndex = 0;
    pStack -> m_maxSize = a_maxSize;

    return pStack;
}

ADTerr StackDoublesDestroy(StackDoubles** a_stack) {
    if(a_stack == NULL || *a_stack == NULL) {
        return STACK_UNINITIALIZED;
    }
    free((*a_stack) -> m_values);
    free(*a_stack);
    *a_stack = NULL;
    return STACK_SUCCESS;
}

ADTerr StackDoublesPush(StackDoubles* a_stack, double a_val) 
{
    if(a_stack == NULL) {
        return STACK_UNINITIALIZED;
    }

    if(a_stack -> m_topIndex == a_stack -> m_maxSize) {
        return STACK_OVERFLOW;
    }

    (a_stack -> m_values)[a_stack -> m_topIndex] = a_val;
    ++(a_stack -> m_topIndex);
    return STACK_SUCCESS;
}

double StackDoublesPop(StackDoubles* a_stack)
{
    int lastIndex;
    double lastVal;
    if(a_stack == NULL) {
        return STACK_UNINITIALIZED;
    }

    if(a_stack -> m_topIndex == 0) {
        return STACK_UNDERFLOW;
    }
    lastIndex = (a_stack -> m_topIndex) - 1;
    lastVal = (a_stack -> m_values)[lastIndex];
    a_stack -> m_topIndex = lastIndex; //decrease top by 1

    return lastVal;
}

double StackDoublesTop(StackDoubles* a_stack)
{
    int lastIndex;
    double lastVal;

    if(a_stack == NULL) {
        return STACK_UNINITIALIZED;
    }
    if(a_stack -> m_topIndex == 0) {
        return STACK_UNDERFLOW;
    }
    lastIndex = (a_stack -> m_topIndex) - 1;
    lastVal = (a_stack -> m_values)[lastIndex];

    return lastVal;
}

int StackDoublesIsEmpty(StackDoubles* a_stack) 
{
    if(a_stack == NULL) {
        return STACK_UNINITIALIZED;
    }
    if(a_stack -> m_topIndex == 0) {
        return 1;
    }
    return 0;
}
int StackDoublesSize(StackDoubles* a_stack) 
{
    if(a_stack == NULL) {
        return STACK_UNINITIALIZED;
    }

    return a_stack -> m_topIndex;
}