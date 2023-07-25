#pragma once
#include <stddef.h>

typedef enum AlgoResult 
{
    FALSE = 0,
    TRUE = 1
}AlgoResult;

AlgoResult isPrimary(size_t a_num);

int squareRootBinarySearch(int a_num);

//Newton's method: root = 2 * (X + N/X)
double squareRootNewton(double a_num, double a_tolerance);