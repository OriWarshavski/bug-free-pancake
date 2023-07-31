#include "bits_prac.h"
#include "mu_test.h"

#define BITS_IN_INT 32

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

static void reverseStr(char* a_str, int a_size)
{
    int start = 0, end = a_size - 1, temp;
    while(start < end) {
        temp = a_str[start];
        a_str[start] = a_str[end];
        a_str[end] = temp;
        ++start;
        --end;
    }
}
static void printBinary(unsigned int a_num, char* a_result)
{
    int i;
    for(i = 0; i < BITS_IN_INT; ++i) {
        if ((a_num & (1 << i)) != 0) {
            a_result[i] = '1';
        }
        else {
            a_result[i] = '0';
        }
    }
    a_result[i] = '\0';
    reverseStr(a_result, BITS_IN_INT);
}

BEGIN_TEST(test_reverse_char)
    char strResult[BITS_IN_INT + 1] = {0};
    char expected[BITS_IN_INT + 1] = "11100000000000000000000000000000";
    ASSERT_EQUAL(reverseChar(3), 192);
    ASSERT_EQUAL(reverseChar(255), 255);

    int result7 = reverseBits(7);
    printBinary(result7, strResult);
    printf("%s\n", strResult);
    ASSERT_EQUAL(checkIfEqual(strResult, expected, BITS_IN_INT), 1);
    ASSERT_EQUAL(reverseBits(50), 1275068416);
END_TEST


TEST_SUITE("tests")
    TEST(test_reverse_char)

END_SUITE
