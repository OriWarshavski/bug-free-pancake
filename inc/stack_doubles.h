#ifndef _STACK_DOUBLES_H__
#define _STACK_DOUBLES_H__

typedef struct StackDoubles StackDoubles;

typedef enum ADTerr {
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    STACK_UNINITIALIZED, 
    STACK_SUCCESS
} ADTerr;

StackDoubles* StackDoublesCreate(int a_maxSize);
ADTerr StackDoublesDestroy(StackDoubles** a_stack);
ADTerr StackDoublesPush(StackDoubles* a_stack, double a_val) ;
double StackDoublesPop(StackDoubles* a_stack);
double StackDoublesTop(StackDoubles* a_stack);
int StackDoublesIsEmpty(StackDoubles* a_stack);
int StackDoublesSize(StackDoubles* a_stack);

#endif //_STACK_DOUBLES_H__
