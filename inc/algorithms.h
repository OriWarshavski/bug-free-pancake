#pragma once
#include <stddef.h>

typedef enum AlgoResult 
{
    FALSE = 0,
    TRUE = 1
}AlgoResult;

AlgoResult isPrimary(size_t a_num);

int squareRootBinarySearch(int a_num);