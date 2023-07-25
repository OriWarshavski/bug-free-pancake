#include <stdio.h>
#include "algorithms.h"

void test_primary();
void test_squareRootBinarySearch();
void test_squareRootNewton();

int main() {
    test_squareRootBinarySearch();
    test_primary();
    test_squareRootNewton();

    return 0;
}

void test_primary() {
    if(isPrimary(5) == TRUE && isPrimary(71) == TRUE && isPrimary(100) == FALSE && isPrimary(55) == FALSE && isPrimary(60) == FALSE && isPrimary(77) == FALSE) 
	{
		printf("test_primary ......................................PASS\n");
	}
	else
	{
		printf("test_primary ......................................FAIL\n");
	}
}

void test_squareRootBinarySearch() {
    printf("%d\n", squareRootBinarySearch(10));
    if(squareRootBinarySearch(25) == 5 && squareRootBinarySearch(9) == 3 ) 
	{
		printf("test_squareRoot ......................................PASS\n");
	}
	else
	{
		printf("test_squareRoot ......................................FAIL\n");
	}
}

void test_squareRootNewton() {
    printf("%f\n", squareRootNewton(327, 0.0001));
    if(squareRootNewton(25, 0.00001) == 5 && squareRootNewton(9, 0) == 3 && (squareRootNewton(327, 0.0001) == 18.083141)) 
	{
		printf("test_squareRoot ......................................PASS\n");
	}
	else
	{
		printf("test_squareRoot ......................................FAIL\n");
	}
}