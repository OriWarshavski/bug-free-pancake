#include "array_prac.h"
#include "mu_test.h"

BEGIN_TEST(sum_array)
    int arr[] = {1,2,3,4,5};
    int* arr2;
    int arr3[5] = {-1,-2,-3,-4,-5};

    ASSERT_EQUAL(sum(arr, 5), 15);
    ASSERT_EQUAL(sum(NULL, 5), WRONG_INPUT);
    ASSERT_EQUAL(sum(arr2, 0), WRONG_INPUT);
    ASSERT_EQUAL(sum(arr3, 5), -15);
END_TEST

BEGIN_TEST(max_array_element)
    int arr[] = {1,2,3,4,5};
    int* arr2;
    int arr3[5] = {-1,-2,-3,-4,-5};

    ASSERT_EQUAL(max(arr, 5), 5);
    ASSERT_EQUAL(max(NULL, 5), WRONG_INPUT);
    ASSERT_EQUAL(max(arr2, 0), WRONG_INPUT);
    ASSERT_EQUAL(max(arr3, 5), -1);
END_TEST

BEGIN_TEST(test1_merge)
    int arr[] = {1,2,3,4,5};
    int merged[10];
    int arr3[5] = {-5,-4,-3,-2,-1};
    int expected[10] = {-5,-4,-3,-2,-1,1,2,3,4,5};
    merge(arr, 5, arr3, 5, merged);

    for(int i = 0; i < 10; ++i) {
        ASSERT_EQUAL(merged[i], expected[i]);
    }
END_TEST

BEGIN_TEST(test2_merge)
    int arr[] = {1,20,31,43,55};
    int merged[10];
    int arr3[5] = {17,20,21,70,90};
    int expected[10] = {1,17,20,20,21,31,43,55,70,90};
    merge(arr, 5, arr3, 5, merged);

    for(int i = 0; i < 10; ++i) {
        ASSERT_EQUAL(merged[i], expected[i]);
    }
END_TEST

BEGIN_TEST(test3_merge)
    int arr[] = {30};
    int arr3[5] = {17,20,21,70,90};
    int merged[6];
    int expected[6] = {17,20,21,30,70,90};
    merge(arr, 1, arr3, 5, merged);

    for(int i = 0; i < 6; ++i) {
        ASSERT_EQUAL(merged[i], expected[i]);
    }
END_TEST

TEST_SUITE("tests")
    TEST(sum_array)
    TEST(max_array_element)
    TEST(test1_merge)
    TEST(test2_merge)
    TEST(test3_merge)
END_SUITE
