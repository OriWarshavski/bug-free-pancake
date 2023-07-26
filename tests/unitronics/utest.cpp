#include "mu_test.h"
#include "unitronics.h"

#include <stdio.h> 
#include <string.h>

static int checkIfEqual(char* a_toCheck, char* a_expected, int a_length) 
{
    int i;
    for(i = 0; i < a_length; ++i) {
        if(a_toCheck[i] != a_expected[i]) {
            return 0;
        }
    }
    return 1;
}

// ---> Q1

BEGIN_TEST(test0_unilitialized)
    ASSERT_EQUAL(bNumToStr(5123, 6, NULL), 0);
END_TEST

BEGIN_TEST(test1_length_smaller_than_max)
    char output[6];
    char expected[5] = "5123";

    ASSERT_EQUAL(bNumToStr(5123, 6, output), 4);
    ASSERT_THAT(checkIfEqual(output, expected, 4));
END_TEST


BEGIN_TEST(test2_length_equal_max) //include '\0'
    char output[6];
    char expected[6] = "12345";

    ASSERT_EQUAL(bNumToStr(12345, 6, output), 5);
    ASSERT_THAT(checkIfEqual(output, expected, 6));
END_TEST

BEGIN_TEST(test3_length_bigger_than_max)
    char output[6];
    char expected[6] = "?????";

    ASSERT_EQUAL(bNumToStr(123456, 5, output), 5);
    ASSERT_THAT(checkIfEqual(output, expected, 6));
END_TEST


BEGIN_TEST(test4_zero_max_bigger)
    char output[2];
    char expected[2] = "0";

    ASSERT_EQUAL(bNumToStr(0, 2, output), 1);
    ASSERT_THAT(checkIfEqual(output, expected, 1));
END_TEST


BEGIN_TEST(test5_negative_max_bigger)
    char output[10];
    char expected[10] = "-1123";

    ASSERT_EQUAL(bNumToStr(-1123, 10, output), 5); //enough place for wrong input
    ASSERT_THAT(checkIfEqual(output, expected, 5));
END_TEST

BEGIN_TEST(test6_minus_one)
    char output[10];
    char expected[10] = "0.12";

    ASSERT_EQUAL(bNumToStrDeciPoint(12, 10, 2, output), 4); //enough place for wrong input
    printf("%s\n", output);
    ASSERT_THAT(checkIfEqual(output, expected, 4));
END_TEST

// -----> Q2

BEGIN_TEST(test1_decP_positive_correct)
    char output[10];
    for(int i = 0; i < 10; ++i) {
        output[i] = '\0';
    }
    char expected[10] = "12.34";

    ASSERT_EQUAL(bNumToStrDeciPoint(1234, 10, 2, output), 5);
    printf("%s\n", output);
    ASSERT_THAT(checkIfEqual(output, expected, 5));
END_TEST

BEGIN_TEST(test2_decP_positive_with_zeros)
    char output[10];
    char expected[10] = "0.0012";

    ASSERT_EQUAL(bNumToStrDeciPoint(12, 10, 4, output), 6);
     printf("%s\n", output);
    ASSERT_THAT(checkIfEqual(output, expected, 5));
END_TEST


// ----> Q3

BEGIN_TEST(test1_Binary)
    char output[10];
    char expected[10] = "101";

    ASSERT_EQUAL(bNumToStrFormat(5, 10, 0, BINARY, output), 3);
    ASSERT_THAT(checkIfEqual(output, expected, 3));
END_TEST

BEGIN_TEST(test2_Binary_zero_input)
    char output[10];
    char expected[10] = "0";

    ASSERT_EQUAL(bNumToStrFormat(0, 10, 0, BINARY, output), 1);
    ASSERT_THAT(checkIfEqual(output, expected, 1));
END_TEST

BEGIN_TEST(test3_Binary)
    char output[10];
    char expected[10] = "11111111";

    ASSERT_EQUAL(bNumToStrFormat(255, 10, 0, BINARY, output), 8);
    ASSERT_THAT(checkIfEqual(output, expected, 8));
END_TEST

BEGIN_TEST(test4_Binary_not_enough_space)
    char output[2];
    char expected[3] = "??";

    ASSERT_EQUAL(bNumToStrFormat(5, 2, 0, BINARY, output), 2);
    ASSERT_THAT(checkIfEqual(output, expected, 2));

END_TEST

BEGIN_TEST(test1_HEX)
    char output[10];
    char expected[10] = "4D2";

    ASSERT_EQUAL(bNumToStrFormat(1234, 10, 0, HEX, output), 3);
    ASSERT_THAT(checkIfEqual(output, expected, 3));
END_TEST

BEGIN_TEST(test2_HEX_not_enough_space)
    char output[2];
    char expected[10] = "??";

    ASSERT_EQUAL(bNumToStrFormat(1234, 2, 0, HEX, output), 2);
    ASSERT_THAT(checkIfEqual(output, expected, 2));
END_TEST

BEGIN_TEST(test3_HEX)
    char output[10];
    char expected[10] = "ffffffff";

    ASSERT_EQUAL(bNumToStrFormat(-1, 10, 0, HEX, output), 3);
    printf("%s\n", output);
    ASSERT_THAT(checkIfEqual(output, expected, 3));
END_TEST

// ---> Q4
BEGIN_TEST(test1_no_leading)
    char output[10];
    char expected[11] = "101";

    ASSERT_EQUAL(bNumToStrLeading(5, 10, 0, BINARY, NO_LEADING, output), 3);
    ASSERT_THAT(checkIfEqual(output, expected, 3));
END_TEST

BEGIN_TEST(test2_leading_zeros)
    char output[10];
    char expected[11] = "0000000101";

    ASSERT_EQUAL(bNumToStrLeading(5, 10, 0, BINARY, LEADING_ZEROS, output), 10);
    ASSERT_THAT(checkIfEqual(output, expected, 10));
END_TEST

BEGIN_TEST(test3_leading_spaces)
    char output[10];
    char expected[11] = "       101";

    ASSERT_EQUAL(bNumToStrLeading(5, 10, 0, BINARY, LEADING_SPACES, output), 10);
    ASSERT_THAT(checkIfEqual(output, expected, 10));
END_TEST

TEST_SUITE("tests")
    TEST(test0_unilitialized)
	TEST(test1_length_smaller_than_max)
    TEST(test2_length_equal_max) 
    TEST(test3_length_bigger_than_max)
    TEST(test4_zero_max_bigger)
    TEST(test5_negative_max_bigger)

    TEST(test1_Binary)
    TEST(test2_Binary_zero_input)
    TEST(test3_Binary)
    TEST(test4_Binary_not_enough_space)

    TEST(test1_HEX)
    TEST(test2_HEX_not_enough_space)

    TEST(test1_no_leading)
    TEST(test2_leading_zeros)
    TEST(test3_leading_spaces)

    TEST(test6_minus_one)

    TEST(test1_decP_positive_correct)
    TEST(test2_decP_positive_with_zeros)

    TEST(test3_HEX)
END_SUITE
