#include "mu_test.h"
#include "unitronics.h"

#include <stdio.h> 
#include <string.h>

static int checkIfEqual(char* a_toCheck, char* a_expected, int a_length) 
{
    int i = 0;
    while(a_toCheck[i] != '\0') {
        if(a_toCheck[i] != a_expected[i]) {
            return 0;
        }
        ++i;
    }
    //if expected is longer
    if(a_expected[i] != '\0') {
        return 0;
    }
    return 1;
}

// ---> Q1

BEGIN_TEST(test0_uninitialized)
    ASSERT_EQUAL(bNumToStr(5123, 6, NULL), 0);
END_TEST

BEGIN_TEST(test1_zero_case)
    char output[6];
    char expected[6] = "0";
    ASSERT_EQUAL(bNumToStr(0, 6, output), 1);
    ASSERT_THAT(checkIfEqual(output, expected, 1) == 1);
END_TEST

BEGIN_TEST(test2_correct_positive_input)
    char output[6];
    char expected[5] = "1234";
    ASSERT_EQUAL(bNumToStr(1234, 4, output), 4);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

BEGIN_TEST(test3_correct_negative_input)
    char output[6];
    char expected[6] = "-1234";
    ASSERT_EQUAL(bNumToStr(-1234, 5, output), 5);
    ASSERT_THAT(checkIfEqual(output, expected, 5) == 1);
END_TEST

BEGIN_TEST(test4_positive_small_size)
    char output[6];
    char expected[5] = "???";
    ASSERT_EQUAL(bNumToStr(1234, 3, output), 3);
    ASSERT_THAT(checkIfEqual(output, expected, 3) == 1);
END_TEST

BEGIN_TEST(test5_negative_small_size)
    char output[6];
    char expected[5] = "????";
    ASSERT_EQUAL(bNumToStr(-1234, 4, output), 4);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

// ---> Q2

BEGIN_TEST(Q2_test0_uninitialized)
    ASSERT_EQUAL(bNumToStrDeciPoint(5123, 6, 0, NULL), 0);
END_TEST

BEGIN_TEST(Q2_test1_zero_case)
    char output[6];
    char expected[6] = "0";
    ASSERT_EQUAL(bNumToStrDeciPoint(0, 6, 0, output), 1);
    ASSERT_THAT(checkIfEqual(output, expected, 1) == 1);
END_TEST

BEGIN_TEST(Q2_test2_correct_positive_input)
    char output[6];
    char expected[5] = "1234";
    ASSERT_EQUAL(bNumToStrDeciPoint(1234, 4, 0, output), 4);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

BEGIN_TEST(Q2_test3_correct_negative_input)
    char output[6];
    char expected[6] = "-1234";
    ASSERT_EQUAL(bNumToStrDeciPoint(-1234, 5, 0, output), 5);
    ASSERT_THAT(checkIfEqual(output, expected, 5) == 1);
END_TEST

BEGIN_TEST(Q2_test4_positive_small_size)
    char output[6];
    char expected[5] = "???";
    ASSERT_EQUAL(bNumToStrDeciPoint(1234, 3, 0, output), 3);
    ASSERT_THAT(checkIfEqual(output, expected, 3) == 1);
END_TEST

BEGIN_TEST(Q2_test5_negative_small_size)
    char output[6];
    char expected[5] = "????";
    ASSERT_EQUAL(bNumToStrDeciPoint(-1234, 4, 0, output), 4);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

BEGIN_TEST(Q2_test6_withoutZeros)
    char output[6];
    char expected[6] = "12.34";
    ASSERT_EQUAL(bNumToStrDeciPoint(1234, 5, 2, output), 5);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 5) == 1);
END_TEST

BEGIN_TEST(Q2_test7_withZeros)
    char output[6];
    char expected[7] = "0.0012";
    ASSERT_EQUAL(bNumToStrDeciPoint(12, 6, 4, output), 6);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 6) == 1);
END_TEST

BEGIN_TEST(Q2_test9_withoutZeros_small_size)
    char output[6];
    char expected[6] = "????";
    ASSERT_EQUAL(bNumToStrDeciPoint(1234, 4, 2, output), 4);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

BEGIN_TEST(Q2_test10_withZeros_small_size)
    char output[6];
    char expected[7] = "?????";
    ASSERT_EQUAL(bNumToStrDeciPoint(12, 5, 4, output), 5);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 5) == 1);
END_TEST

// ---> Q3

BEGIN_TEST(Q3_test0_uninitialized)
    ASSERT_EQUAL(bNumToStrFormat(5123, 6, 0, DECIMAL, NULL), 0);
END_TEST

BEGIN_TEST(Q3_test1_zero_case)
    char output[6];
    char expected[6] = "0";
    ASSERT_EQUAL(bNumToStrFormat(0, 6, 0, DECIMAL, output), 1);
    ASSERT_THAT(checkIfEqual(output, expected, 1) == 1);
END_TEST

BEGIN_TEST(Q3_test2_correct_positive_input)
    char output[6];
    char expected[5] = "1234";
    ASSERT_EQUAL(bNumToStrFormat(1234, 4, 0, DECIMAL, output), 4);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

BEGIN_TEST(Q3_test3_correct_negative_input)
    char output[6];
    char expected[6] = "-1234";
    ASSERT_EQUAL(bNumToStrFormat(-1234, 5, 0, DECIMAL, output), 5);
    ASSERT_THAT(checkIfEqual(output, expected, 5) == 1);
END_TEST

BEGIN_TEST(Q3_test4_positive_small_size)
    char output[6];
    char expected[5] = "???";
    ASSERT_EQUAL(bNumToStrFormat(1234, 3, 0, DECIMAL, output), 3);
    ASSERT_THAT(checkIfEqual(output, expected, 3) == 1);
END_TEST

BEGIN_TEST(Q3_test5_negative_small_size)
    char output[6];
    char expected[5] = "????";
    ASSERT_EQUAL(bNumToStrFormat(-1234, 4, 0, DECIMAL, output), 4);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

BEGIN_TEST(Q3_test6_withoutZeros)
    char output[6];
    char expected[6] = "12.34";
    ASSERT_EQUAL(bNumToStrFormat(1234, 5, 2, DECIMAL, output), 5);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 5) == 1);
END_TEST

BEGIN_TEST(Q3_test7_withZeros)
    char output[6];
    char expected[7] = "0.0012";
    ASSERT_EQUAL(bNumToStrFormat(12, 6, 4, DECIMAL, output), 6);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 6) == 1);
END_TEST

BEGIN_TEST(Q3_test7_1_withZeros)
    char output[8];
    char expected[8] = "-0.0012";
    ASSERT_EQUAL(bNumToStrFormat(-12, 77, 4, DECIMAL, output), 7);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 7) == 1);
END_TEST

BEGIN_TEST(Q3_test9_withoutZeros_small_size)
    char output[6];
    char expected[6] = "????";
    ASSERT_EQUAL(bNumToStrFormat(1234, 4, 2, DECIMAL, output), 4);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

BEGIN_TEST(Q3_test10_withZeros_small_size)
    char output[6];
    char expected[7] = "?????";
    ASSERT_EQUAL(bNumToStrFormat(12, 5, 4, DECIMAL, output), 5);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 5) == 1);
END_TEST


BEGIN_TEST(Q3_test11_binary)
    char output[6];
    char expected[7] = "101";
    ASSERT_EQUAL(bNumToStrFormat(5, 6, 0, BINARY, output), 3);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 3) == 1);
END_TEST

BEGIN_TEST(Q3_test12_binary)
    char output[9];
    char expected[9] = "11111111";
    ASSERT_EQUAL(bNumToStrFormat(255, 8, 0, BINARY, output), 8);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 8) == 1);
END_TEST

BEGIN_TEST(Q3_test13_binary)
    char output[9];
    char expected[9] = "1010";
    ASSERT_EQUAL(bNumToStrFormat(10, 8, 0, BINARY, output), 4);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

BEGIN_TEST(Q3_test14_hexa)
    char output[4];
    char expected[4] = "4D2";
    ASSERT_EQUAL(bNumToStrFormat(1234, 3, 0, HEX, output), 3);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 3) == 1);
END_TEST

BEGIN_TEST(Q3_test15_hexa)
    char output[9];
    char expected1[9] = "FFFFFFFF";
    char expected2[9] = "B22C";
    ASSERT_EQUAL(bNumToStrFormat(-1, 8, 0, HEX, output), 8);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected1, 8) == 1);

    ASSERT_EQUAL(bNumToStrFormat(45612, 7, 0, HEX, output), 4);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected2, 3) == 1);
END_TEST

BEGIN_TEST(Q3_test16_hexa_small_size)
    char output[7];
    char expected[9] = "???????";
    ASSERT_EQUAL(bNumToStrFormat(-1, 7, 0, HEX, output), 7);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 3) == 1);
    
END_TEST

BEGIN_TEST(Q3_test17_binary_small_size)
    char output[3];
    char expected[9] = "??";
    ASSERT_EQUAL(bNumToStrFormat(7, 2, 0, BINARY, output), 2);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

BEGIN_TEST(Q3_test18_zero_case_binary)
    char output[3];
    char expected[9] = "0";
    ASSERT_EQUAL(bNumToStrFormat(0, 2, 0, BINARY, output), 1);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 1) == 1);
END_TEST

BEGIN_TEST(Q3_test19_deci_with_sign_correct)
    char output[7];
    char expected[7] = "+12.34";
    ASSERT_EQUAL(bNumToStrFormat(1234, 6, 2, DECIMAL_WITH_SIGN, output), 6);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 6) == 1);
END_TEST

BEGIN_TEST(Q3_test20_deci_with_sign_and_zeros)
    char output[8];
    char expected[8] = "+0.0012";
    ASSERT_EQUAL(bNumToStrFormat(12, 7, 4, DECIMAL_WITH_SIGN, output), 7);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 6) == 1);
END_TEST

BEGIN_TEST(Q3_test21_deci_with_sign_and_zeros_small_size)
    char output[8];
    char expected[8] = "??????";
    ASSERT_EQUAL(bNumToStrFormat(12, 6, 4, DECIMAL_WITH_SIGN, output), 6);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 6) == 1);
END_TEST

// ------------------------------------> Q4

BEGIN_TEST(Q4_test0_uninitialized)
    ASSERT_EQUAL(bNumToStrLeading(5123, 6, 0, DECIMAL, NO_LEADING, NULL), 0);
END_TEST

BEGIN_TEST(Q4_test1_zero_case)
    char output[6];
    char expected[6] = "0";
    ASSERT_EQUAL(bNumToStrLeading(0, 6, 0, DECIMAL, NO_LEADING, output), 1);
    ASSERT_THAT(checkIfEqual(output, expected, 1) == 1);
END_TEST

BEGIN_TEST(Q4_test2_correct_positive_input)
    char output[6];
    char expected[5] = "1234";
    ASSERT_EQUAL(bNumToStrLeading(1234, 4, 0, DECIMAL, NO_LEADING, output), 4);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

BEGIN_TEST(Q4_test3_correct_negative_input)
    char output[6];
    char expected[6] = "-1234";
    ASSERT_EQUAL(bNumToStrLeading(-1234, 5, 0, DECIMAL, NO_LEADING, output), 5);
    ASSERT_THAT(checkIfEqual(output, expected, 5) == 1);
END_TEST

BEGIN_TEST(Q4_test4_positive_small_size)
    char output[6];
    char expected[5] = "???";
    ASSERT_EQUAL(bNumToStrLeading(1234, 3, 0, DECIMAL, NO_LEADING, output), 3);
    ASSERT_THAT(checkIfEqual(output, expected, 3) == 1);
END_TEST

BEGIN_TEST(Q4_test5_negative_small_size)
    char output[6];
    char expected[5] = "????";
    ASSERT_EQUAL(bNumToStrLeading(-1234, 4, 0, DECIMAL, NO_LEADING, output), 4);
    ASSERT_THAT(checkIfEqual(output, expected, 4) == 1);
END_TEST

BEGIN_TEST(Q4_test6_zero_case_with_leading)
    char output[7];
    char expected1[7] = "000000";
    char expected2[7] = "     0";
    ASSERT_EQUAL(bNumToStrLeading(0, 6, 0, DECIMAL, LEADING_ZEROS, output), 6);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected1, 6) == 1);
    
    ASSERT_EQUAL(bNumToStrLeading(0, 6, 0, DECIMAL, LEADING_SPACES, output), 6);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected2, 6) == 1);
END_TEST

BEGIN_TEST(Q4_test7_correct_positive_leading)
    char output[11];
    char expected[11] = "      1234";
    char expected2[11] = "0000001234"; 
    ASSERT_EQUAL(bNumToStrLeading(1234, 10, 0, DECIMAL, LEADING_SPACES, output), 10);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 10) == 1);

    ASSERT_EQUAL(bNumToStrLeading(1234, 10, 0, DECIMAL, LEADING_ZEROS, output), 10);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected2, 10) == 1);
END_TEST

BEGIN_TEST(Q4_test8_leading_with_sign)
    char output[12];
    char expected[12] = "-000001234";
    char expected2[12] = "+000001234";

    ASSERT_EQUAL(bNumToStrLeading(-1234, 10, 0, DECIMAL, LEADING_ZEROS, output), 10);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 10) == 1);

    ASSERT_EQUAL(bNumToStrLeading(1234, 10, 0, DECIMAL_WITH_SIGN, LEADING_ZEROS, output), 10);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected2, 11) == 1);
END_TEST

BEGIN_TEST(Q4_test8_leading_with_point)
    char output[11];
    char expected[11] = "-00001.234";
    char expected2[11] = "   -0.1234";      

    ASSERT_EQUAL(bNumToStrLeading(-1234, 10, 3, DECIMAL, LEADING_ZEROS, output), 10);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 10) == 1);

    ASSERT_EQUAL(bNumToStrLeading(-1234, 10, 4, DECIMAL, LEADING_SPACES, output), 10);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected2, 10) == 1);
END_TEST

BEGIN_TEST(Q4_test9_leading_binary)
    char output[11];
    char expected[11] = "0000000111";
    ASSERT_EQUAL(bNumToStrLeading(7, 10, 0, BINARY, LEADING_ZEROS, output), 10);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 10) == 1);
END_TEST


BEGIN_TEST(Q4_test9_leading_HEX)
    char output[11];
    char expected[11] = "   2BBE3D3";
    ASSERT_EQUAL(bNumToStrLeading(45867987, 10, 0, HEX, LEADING_SPACES, output), 10);
    TRACE(output);
    ASSERT_THAT(checkIfEqual(output, expected, 10) == 1);
END_TEST

TEST_SUITE("tests")
    TEST(test0_uninitialized)
    TEST(test1_zero_case)
    TEST(test2_correct_positive_input)
    TEST(test3_correct_negative_input)
    TEST(test4_positive_small_size)
    TEST(test5_negative_small_size)

    TEST(Q2_test0_uninitialized)
    TEST(Q2_test1_zero_case)
    TEST(Q2_test2_correct_positive_input)
    TEST(Q2_test3_correct_negative_input)
    TEST(Q2_test4_positive_small_size)
    TEST(Q2_test5_negative_small_size)
    TEST(Q2_test6_withoutZeros)
    TEST(Q2_test7_withZeros)
    TEST(Q2_test9_withoutZeros_small_size)
    TEST(Q2_test10_withZeros_small_size)

    TEST(Q3_test0_uninitialized)
    TEST(Q3_test1_zero_case)
    TEST(Q3_test2_correct_positive_input)
    TEST(Q3_test3_correct_negative_input)
    TEST(Q3_test4_positive_small_size)
    TEST(Q3_test5_negative_small_size)
    TEST(Q3_test6_withoutZeros)
    TEST(Q3_test7_withZeros)
    TEST(Q3_test9_withoutZeros_small_size)
    TEST(Q3_test10_withZeros_small_size)
    TEST(Q3_test11_binary)
    TEST(Q3_test12_binary)
    TEST(Q3_test13_binary)
    TEST(Q3_test14_hexa)
    TEST(Q3_test15_hexa)
    TEST(Q3_test16_hexa_small_size)
    TEST(Q3_test17_binary_small_size)
    TEST(Q3_test18_zero_case_binary)
    
    TEST(Q3_test19_deci_with_sign_correct)
    TEST(Q3_test20_deci_with_sign_and_zeros)
    TEST(Q3_test7_1_withZeros)
    TEST(Q3_test21_deci_with_sign_and_zeros_small_size)

    TEST(Q4_test0_uninitialized)
    TEST(Q4_test1_zero_case)
    TEST(Q4_test2_correct_positive_input)
    TEST(Q4_test3_correct_negative_input)
    TEST(Q4_test4_positive_small_size)
    TEST(Q4_test5_negative_small_size)
    TEST(Q4_test6_zero_case_with_leading)
    TEST(Q4_test7_correct_positive_leading)
    TEST(Q4_test8_leading_with_sign)
    TEST(Q4_test8_leading_with_point)
    TEST(Q4_test9_leading_binary)
    TEST(Q4_test9_leading_HEX)
END_SUITE
