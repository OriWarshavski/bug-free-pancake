#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "algorithms.h"

AlgoResult isPrimary(size_t a_num)
{
    size_t sqrtNum = sqrt(a_num);
    for(int i = 2; i <= sqrtNum; ++i) {
        if(a_num % i == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

int squareRootBinarySearch(int a_num)
{
    int m, check;
    int low = 1, high = a_num;
    while(low <= high) {
        m = (low + high) / 2; //13, 6.5, 3.25, 4.875
        check = m * m; //169, 42.25, 10.5625, 23.765725
        if(check == a_num) { //no, no, no, no
            return m;
        }
        if(check < a_num) { // no, no, yes, yes
            low = m + 1; // 4.25 to 5.5, 
        }
        else {
            high = m - 1; //1 to 12, 1 to 5.5
        }
    }
    return high;
}
//Newton's method: root = 0.5 * (X + N/X)
double squareRootNewton(double a_num, double a_tolerance)
{
    double x = a_num;
    double root;
    while(TRUE) {
        root = 0.5 * (x + (a_num / x));
        if(fabs(root - x) <= a_tolerance) {
            break;
        }
        x = root;
    }
    return root;
}

