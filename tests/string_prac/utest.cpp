#include "mu_test.h"
 
#define IS_CHAR_BLANK(c) ((c == ' ') || (c == '\t') ||(c == '\n'))

#define MAX_LEN 30
#define NOT_NUM(x) (x < '0' || x > '9')

static int stringToNum(char* a_str, int a_size);
static float calcOp(float a_num1, float a_num2, char a_opt);

int NumOfWords(char* a_phrase)
{
    int count = 0;
    int i = 1;
    if(a_phrase == NULL) {
        return -1;
    }

    if(a_phrase[0] == '\0') {
        return 0;
    }
    
    while(a_phrase[i] != '\0') {
        if(IS_CHAR_BLANK(a_phrase[i]) && !IS_CHAR_BLANK(a_phrase[i - 1])) {
            ++count;
        }
        ++i;
    }

    if(!IS_CHAR_BLANK(a_phrase[i - 1])) {
        ++count;
    }

    return count;
}

float CalcPhrase(char* a_phrase)
{
    int i, j, nums[MAX_LEN];
    float result = 0;
    char signs[MAX_LEN];
    int start = 0, end = 0, countNums = 0, countSigns = 0;
    if(a_phrase == NULL) {
        return -1;
    }   
    while((a_phrase[end] != '\0') && (countNums < MAX_LEN) && (a_phrase[start] != '\0')) {
        if(NOT_NUM(a_phrase[end])) {
            nums[countNums] = stringToNum(a_phrase + start, end - start);
            signs[countSigns] = a_phrase[end];
            ++countNums;
            ++countSigns;
            start = end + 1;
        }

        ++end;
    }
    
    if(countNums == MAX_LEN) {
        return -1;
    }

    if(a_phrase[end - 1] != '\0'){
        nums[countNums] = stringToNum(a_phrase + start, end - start);
        ++countNums;
    }

    result = nums[0];

    for(i = 0, j = 1; i < countSigns; ++i, ++j) {
        result = calcOp(result, nums[j], signs[i]);
    }

    return result;
}

static int stringToNum(char* a_str, int a_size)
{
    int i;
    int num = 0;
    for(i = 0; i < a_size; ++i){
        num *= 10;
        num += a_str[i] - '0';
    }
    return num;
}

static float calcOp(float a_num1, float a_num2, char a_opt)
{
    float result;
    switch(a_opt) {
    case '+':
        result =  a_num1 + a_num2;
        break;
    case '-':
        result =  a_num1 - a_num2;
        break;

    case '/':
        result =  a_num1 / a_num2;
        break;
    case '*':
        result =  a_num1 * a_num2;
        break;
    }
    return result;
}

BEGIN_TEST(test1_uninitialized)
    ASSERT_EQUAL(NumOfWords(NULL), -1);
END_TEST

BEGIN_TEST(test2_num_of_words)
    char phrase[30] = "s  asd asd asd  6 ";
    ASSERT_EQUAL(NumOfWords(phrase), 5);
END_TEST

BEGIN_TEST(test3_one_word)
    char phrase[30] = "abc";
    ASSERT_EQUAL(NumOfWords(phrase), 1);
END_TEST

BEGIN_TEST(test4_blank_first)
    char phrase[30] = " abc df";
    ASSERT_EQUAL(NumOfWords(phrase), 2);
END_TEST

BEGIN_TEST(test5_many_blanks)
    char phrase[30] = "   abc   d  f  ";
    ASSERT_EQUAL(NumOfWords(phrase), 3);
END_TEST

/////////////////////////////////////////////////////////////////////////
BEGIN_TEST(test_string_to_num)
    char phrase[30] = "0102";
    ASSERT_EQUAL(stringToNum(phrase, 4), 102);
END_TEST

BEGIN_TEST(test1_calc_phrase)
    char phrase[30] = "30/20";
    ASSERT_EQUAL(CalcPhrase(phrase), 1.5);
END_TEST

TEST_SUITE("tests")
    TEST(test1_uninitialized)
    TEST(test2_num_of_words)
    TEST(test3_one_word)
    TEST(test4_blank_first)
    TEST(test5_many_blanks)

    TEST(test_string_to_num)
    TEST(test1_calc_phrase)
END_SUITE
