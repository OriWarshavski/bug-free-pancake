#include "mu_test.h"
#include "stack_doubles.h"
#include <string.h>
#include <math.h>

#define IS_CHAR_BLANK(c) ((c == ' ') || (c == '\t') ||(c == '\n'))

#define MAX_LEN 100
#define IS_SPACE(x) (x == ' ' || x == '\t')
#define IS_DIGIT(x) (x >= '0' && x <= '9')

#define IS_LETTER(x) (x >= 'A' && x <= 'F')

void reverseSentence(char* a_input, char* a_output)
{
    int size, i, j = 0, end, start;
    if(a_input == NULL || a_output == NULL || a_input[0] == '\0') {
        a_output[0] = '\0';
        return;
    }
    size = strlen(a_input);

    for(i = size - 1, end = i; i >= 0; --i) {
        if(IS_CHAR_BLANK(a_input[i]) || i == 0) {
            start = i;
            if(IS_CHAR_BLANK(a_input[i])) {
                ++start;
            }
            while(start <= end) {
                printf("i:%d, %c\n", i, a_input[start]);
                a_output[j] = a_input[start];
                ++start;
                ++j;
            }
            while(i >= 0 && IS_CHAR_BLANK(a_input[i])) {
                a_output[j] = a_input[i];
                --i;
                ++j;
            }
            if(i == 0 && j < size) {
                a_output[j] = a_input[i];
                --i;
                ++j;           
            }
            end = i;
        }
    }
    a_output[j] = '\0';
}
typedef enum FORMAT {
    BINARY = 2,
    DECIMAL = 10,
    HEX = 16
} FORMAT;

// static int checkIfEqual(char* a_toCheck, char* a_expected, int a_length) 
// {
//     int i = 0;
//     while(a_toCheck[i] != '\0') {
//         if(a_toCheck[i] != a_expected[i]) {
//             return 0;
//         }
//         ++i;
//     }
//     //if expected is longer
//     if(a_expected[i] != '\0') {
//         return 0;
//     }
//     return 1;
// }

double convertStrToDouble(char* a_str, int a_size, FORMAT a_format)
{
    int i, pointIndex, isPoint = 0, isNegative = 0;
    double res = 0, power;
    char cur;

    if(a_str == NULL || a_size <= 0){
        return -1;
    }

    if(a_str[0] == '-') {
        ++a_str;
        --a_size;
        isNegative = 1;
    }

    pointIndex = a_size;
    //find point index
    for(i = 0; i < a_size; ++i) {
        if(a_str[i] == '.') {
            pointIndex = i;
            isPoint = 1;
            break;
        }
    }
    i = a_size - 1;
    //fraction part
    if(isPoint) {
        for( ; i >= pointIndex; --i) {
            cur = a_str[i];

            if(IS_DIGIT(cur) && cur != '0') {
                power = pow((int)a_format, pointIndex - i);
                res += (power * (cur - '0'));
            }
        }
    }
    //integral part
    for(; i >= 0; --i) {
        cur = a_str[i];

        if(IS_LETTER(cur)) {
            power = pow((int)a_format, pointIndex - i - 1);
            res += (power * (cur - 'A' + 10));
        }
        else if(IS_DIGIT(cur) && cur != '0') {
            power = pow((int)a_format, pointIndex - i - 1);
            res += (power * (cur - '0'));
        }
    }

    if(isNegative) {
        res = -res;
    }

    return res;
}

static double binaryStrToDouble(char* a_str, int a_size)
{
    int i, pointIndex = a_size, isPoint = 0, isNegative = 0;
    int carry;
    double res = 0;

    //find point index
    for(i = 0; i < a_size; ++i) {
        if(a_str[i] == '.') {
            pointIndex = i;
            isPoint = 1;
            break;
        }
    }
    //check if negative
    if(a_str[0] == '1') {
        isNegative = 1;
        //flip all bits
        for(i = 0; i < a_size; ++i) {
            if(a_str[i] == '0') {
                a_str[i] = '1';
            }
            else {
                a_str[i] = '0';
            }
        }
        //add 1
        carry = 1;
        for (i = a_size - 1; i >= 0; --i) {
            if (a_str[i] == '0' && carry == 1) {
                a_str[i] = '1';
                carry = 0;
            } else if (a_str[i] == '1' && carry == 1) {
                a_str[i] = '0';
            }
        }
    }

    i = a_size - 1;

    //fraction part
    if(isPoint) {
        for( ; i >= pointIndex; --i) {
            if(a_str[i] == '1') {
                res += pow(2, pointIndex - i);
            }
        }
    }
    //integral part
    for(; i >= 0; --i) {
        if(a_str[i] == '1') {
            res += pow(2, pointIndex - 1 - i);
        }
    }

    if(isNegative) {
        res = -res;
    }
    return res;
}

static double decimalStrToDouble(char* a_str, int a_size) //a_str has only numbers and symbols!!
{
    int i = 0, countFpart = 0, isNegative = 0;
    double leftVal = 0.0, fracPart = 0.0;
    double res;

    if(a_str == NULL) {
        return -1;
    }

    if(a_str[i] == '-') {
        isNegative = 1;
        ++i;
    }

    for(; (i < a_size) && (a_str[i] != '.'); ++i) {
        leftVal *= 10;
        leftVal += a_str[i] - '0';
    }
    if(a_str[i] == '.') {
        ++i;
        for(; i < a_size; ++i) {
            ++countFpart;
            fracPart *= 10;
            fracPart += a_str[i] - '0';
        }
    }
    res = (double)leftVal + (fracPart / pow(10, countFpart));
    if(isNegative) {
        res = -res;
    }
    return res;
}

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

void StackPush(char* a_stack, char a_val) 
{
    int size;
    if(a_stack == NULL) {
        return;
    }
    size = strlen(a_stack);
    if(size == MAX_LEN) {
        return;
    }
    a_stack[size] = a_val;
    a_stack[size + 1] = '\0';

}
char StackPop(char* a_stack)
{
    int size;
    char save;
    if(a_stack == NULL) {
        return -1;
    }
    size = strlen(a_stack);
    if(size == 0) {
        return '\0';
    }
    save = a_stack[size - 1];
    a_stack[size - 1] = '\0';
    return save;
}
char StackTop(char* a_stack)
{
    int size;
    if(a_stack == NULL) {
        return -1;
    }
    size = strlen(a_stack);
    if(size == 0) {
        return '\0';
    }
    return a_stack[size - 1];
}
int StackIsEmpty(char* a_stack) 
{
    if(a_stack == NULL) {
        return -1;
    }
    if(strlen(a_stack) == 0) {
        return 1;
    }
    return 0;
}

int checkPreference(char a_symbol)
{
    int p = 0;
    switch (a_symbol) {
        case '+':
        case '-':
            p = 1;
            break;

        case '*':
        case '/':
            p = 2;
            break;

        default:
            p = 0;
            break;
    }
    return p;
}

void InfixToPostfix(char* a_infix, char* a_postfixOutput)
{
    char stack[MAX_LEN];
    char curr, popped;
    int size, i, postIndex = 0;
    stack[0] = '\0';

    size = strlen(a_infix);
    for(i = 0; i < size; ++i) {
        curr = a_infix[i];
        if(IS_SPACE(curr)) {
            continue;
        }
        switch (curr) {
        case '(':
            StackPush(stack, curr);
            break;

        case ')':
            popped = StackPop(stack);
            while(popped != '(') {
                a_postfixOutput[postIndex] = popped;
                ++postIndex;
                popped = StackPop(stack);
            }
            break;

        case '+':
        case '-':
        case '*':
        case '/':
            while(!StackIsEmpty(stack) && checkPreference(curr) <= checkPreference(StackTop(stack))) {
                a_postfixOutput[postIndex] = StackPop(stack);
                ++postIndex;
            }
            StackPush(stack, curr);
            break;

        default: //digits
            while(IS_DIGIT(curr) || curr == '.') {
                a_postfixOutput[postIndex] = curr;
                ++postIndex;
                ++i;
                curr = a_infix[i];
            }
            a_postfixOutput[postIndex] = '|';
            ++postIndex;
            --i;
            break;
        }
    }
    while(!StackIsEmpty(stack)) {
        a_postfixOutput[postIndex] = StackPop(stack);
        ++postIndex;
    }
    a_postfixOutput[postIndex] = '\0';
}

float CalcPhrase(char* a_infix)
{
    char postfix[MAX_LEN];
    StackDoubles* stack = StackDoublesCreate(MAX_LEN);
    char curr;
    int i = 0, start = 0;
    double op1, op2, result = 0;
    if(a_infix == NULL) {
        return -1;
    }

    InfixToPostfix(a_infix, postfix);
    printf("postfix: %s\n", postfix);

    while(postfix[i] != '\0') {
        curr = postfix[i];
        //push doubles from postfix into the stack
        while(IS_DIGIT(curr)) {
            start = i;
            while(IS_DIGIT(postfix[i]) || postfix[i] == '.') {
                ++i;
            }
            // must be '|'
            StackDoublesPush(stack, decimalStrToDouble(postfix + start, i - start));
            ++i;
            curr = postfix[i];
        }
        //curr is a symbol
        if(StackDoublesSize(stack) < 2) {
            op1 = StackDoublesPop(stack);
            op2 = 0;
        }
        else {
            op1 = StackDoublesPop(stack);
            op2 = StackDoublesPop(stack);
        }
        switch (curr) {
        case '+':
            result = op2 + op1;
            break;
        case '-':
            result = op2 - op1;
            break;
        case '*':
            result = op2 * op1;
            break;
        case '/':
            result = op2 / op1;
            break;  
        }
        StackDoublesPush(stack, result);
        ++i;
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

BEGIN_TEST(test1_calc_phrase)
    char phrase[MAX_LEN] = "-20 + 4*(15 + 5)/7";
    double expected = (80.0 / 7.0) - 20.0;
    double res;
    expected = floor(10000*expected)/10000;
    res = CalcPhrase(phrase);
    res = floor(10000*res)/10000;
    TRACE(res);
    ASSERT_EQUAL(res, expected);
END_TEST

BEGIN_TEST(test2_calc_phrase)
    char phrase[MAX_LEN] = "6.5 + 1.2 - 3 * (3 - 5)";
    double expected = 6.5+1.2+6.0;
    double res;
    res = CalcPhrase(phrase);

    res = roundf(10000*res)/10000;
    expected = roundf(10000*expected)/10000;
    ASSERT_EQUAL(res, expected);
END_TEST

BEGIN_TEST(test0_Stack_uninitialized)
    StackDoublesIsEmpty(NULL);
    ASSERT_PASS();
END_TEST

BEGIN_TEST(test1_Stack)
    StackDoubles* p = StackDoublesCreate(MAX_LEN);
    ASSERT_EQUAL(StackDoublesIsEmpty(p), 1);
    StackDoublesDestroy(&p);
END_TEST

BEGIN_TEST(test2_Stack_doubleFree)
    StackDoubles* p = StackDoublesCreate(MAX_LEN);
    StackDoublesDestroy(&p);
    StackDoublesDestroy(&p);
    ASSERT_PASS();
END_TEST

BEGIN_TEST(test3_Stack_push_pop_top)
    StackDoubles* p = StackDoublesCreate(MAX_LEN);
    StackDoublesPush(p, 1.2);
    StackDoublesPush(p, 7.8);
    StackDoublesPush(p, 12.13);
    ASSERT_EQUAL(StackDoublesSize(p), 3);

    ASSERT_EQUAL(StackDoublesTop(p), 12.13);
    ASSERT_EQUAL(StackDoublesPop(p), 12.13);
    ASSERT_EQUAL(StackDoublesSize(p), 2);
    ASSERT_EQUAL(StackDoublesIsEmpty(p), 0);

    ASSERT_EQUAL(StackDoublesTop(p), 7.8);
    ASSERT_EQUAL(StackDoublesPop(p), 7.8);
    ASSERT_EQUAL(StackDoublesSize(p), 1);

    ASSERT_EQUAL(StackDoublesPop(p), 1.2);
    ASSERT_EQUAL(StackDoublesSize(p), 0);
    ASSERT_EQUAL(StackDoublesIsEmpty(p), 1);

    StackDoublesDestroy(&p);
END_TEST
/////////////////////////////////////////////////////////////////////////
BEGIN_TEST(test1_decimalStr_to_double)
    char str[30] = "12.34";
    char str2[30] = "0.012";
    char str3[30] = "1";

    double res1 = decimalStrToDouble(str, strlen(str));
    double res2 = decimalStrToDouble(str2, strlen(str2));

    TRACE(res1);
    TRACE(res2);

    ASSERT_EQUAL(res1, 12.34);
    ASSERT_EQUAL(res2, 0.012);
    ASSERT_EQUAL(decimalStrToDouble(str3, 1), 1);
END_TEST

BEGIN_TEST(test1_decimalStr_to_double_negative)
    char str[30] = "-12.34";
    char str2[30] = "-0.012";
    char str3[30] = "-1";

    double res1 = decimalStrToDouble(str, strlen(str));
    double res2 = decimalStrToDouble(str2, strlen(str2));

    TRACE(res1);
    TRACE(res2);

    ASSERT_EQUAL(res1, -12.34);
    ASSERT_EQUAL(res2, -0.012);
    ASSERT_EQUAL(decimalStrToDouble(str3, strlen(str3)), -1);
END_TEST

BEGIN_TEST(test1_binaryStr_to_double)
    char str[100] = "01001100000000000000000000000000";
    int res1 = binaryStrToDouble(str, strlen(str));
    TRACE(res1);
    ASSERT_EQUAL(res1, 1275068416);
END_TEST

BEGIN_TEST(test2_binaryStr_to_double)
    char str[100] = "0110.101";
    double res1 = binaryStrToDouble(str, strlen(str));
    TRACE(res1);
    ASSERT_EQUAL(res1, 6.625);
END_TEST

BEGIN_TEST(test1_convert_by_format_to_double)
    char str[100] = "1010";
    double res1 = convertStrToDouble(str, strlen(str), BINARY);
    TRACE(res1);
    ASSERT_EQUAL(res1, 10);
END_TEST

BEGIN_TEST(test2_convert_by_format_to_double)
    char str[100] = "01001100000000000000000000000000";
    double res1 = convertStrToDouble(str, strlen(str), BINARY);
    TRACE(res1);
    ASSERT_EQUAL(res1, 1275068416);
END_TEST

BEGIN_TEST(test3_convert_by_format_to_double)
    char str[100] = "110.101";
    double res1 = convertStrToDouble(str, strlen(str), BINARY);
    TRACE(res1);
    ASSERT_EQUAL(res1, 6.625);
END_TEST

BEGIN_TEST(test4_convert_by_format_to_double)
    char str[100] = "123";
    double res1 = convertStrToDouble(str, strlen(str), DECIMAL);
    TRACE(res1);
    ASSERT_EQUAL(res1, 123);
END_TEST

BEGIN_TEST(test5_convert_by_format_to_double)
    char str[100] = "12.34";
    double res1 = convertStrToDouble(str, strlen(str), DECIMAL);
    TRACE(res1);
    ASSERT_EQUAL(res1, 12.34);
END_TEST

BEGIN_TEST(test6_convert_by_format_to_double)
    char str[100] = "0.00123";
    double res1 = convertStrToDouble(str, strlen(str), DECIMAL);
    TRACE(res1);
    ASSERT_EQUAL(res1, 0.00123);
END_TEST

BEGIN_TEST(test7_convert_by_format_to_double)
    char str[100] = "-123";
    double res1 = convertStrToDouble(str, strlen(str), DECIMAL);
    TRACE(res1);
    ASSERT_EQUAL(res1, -123);
END_TEST

BEGIN_TEST(test8_convert_by_format_to_double)
    char str[100] = "-12.3";
    double res1 = convertStrToDouble(str, strlen(str), DECIMAL);
    TRACE(res1);
    ASSERT_EQUAL(res1, -12.3);
END_TEST

BEGIN_TEST(test9_convert_by_format_to_double)
    char str[100] = "-0.0001";
    double res1 = convertStrToDouble(str, strlen(str), DECIMAL);
    TRACE(res1);
    ASSERT_EQUAL(res1, -0.0001);
END_TEST

BEGIN_TEST(test10_convert_by_format_to_double)
    char str[100] = "11E8";
    double res1 = convertStrToDouble(str, strlen(str), HEX);
    TRACE(res1);
    ASSERT_EQUAL(res1, 4584);
END_TEST

BEGIN_TEST(test11_convert_by_format_to_double)
    char str[100] = "C.8";
    double res1 = convertStrToDouble(str, strlen(str), HEX);
    TRACE(res1);
    ASSERT_EQUAL(res1, 12.5);
END_TEST

BEGIN_TEST(test12_binary_to_double)
    char str[100] = "11111111";
    double res1 = binaryStrToDouble(str, strlen(str));
    TRACE(res1);
    ASSERT_EQUAL(res1, -1);
END_TEST

//////////////////////////////////////////////////////////////////

BEGIN_TEST(test1_reverse_sentence)
    char str[100] = "hello world";
    char output[100];
    char expected[100] = "world hello";
    reverseSentence(str, output);
    TRACE(output);
    ASSERT_EQUAL(strcmp(output, expected), 0);
END_TEST

BEGIN_TEST(test2_reverse_sentence)
    char str[100] = " hello  world ";
    char output[100];
    char expected[100] = " world  hello ";
    reverseSentence(str, output);
    TRACE(output);
    ASSERT_EQUAL(strcmp(output, expected), 0);
END_TEST

BEGIN_TEST(test3_reverse_sentence)
    char str[100] = "! hello world";
    char output[100];
    char expected[100] = "world hello !";
    reverseSentence(str, output);
    TRACE(output);
    ASSERT_EQUAL(strcmp(output, expected), 0);
END_TEST

BEGIN_TEST(test4_reverse_sentence)
    char str[100] = "Hello, this is a sample sentence.";
    char output[100];
    char expected[100] = "sentence. sample a is this Hello,";
    reverseSentence(str, output);
    TRACE(output);
    ASSERT_EQUAL(strcmp(output, expected), 0);
END_TEST

BEGIN_TEST(test5_reverse_sentence)
    char str[100] = "";
    char output[100];
    char expected[100] = "";
    reverseSentence(str, output);
    TRACE(output);
    ASSERT_EQUAL(strcmp(output, expected), 0);
END_TEST

BEGIN_TEST(test6_reverse_sentence)
    char str[100] = "hello";
    char output[100];
    char expected[100] = "hello";
    reverseSentence(str, output);
    TRACE(output);
    ASSERT_EQUAL(strcmp(output, expected), 0);
END_TEST

BEGIN_TEST(test7_reverse_sentence)
    char str[100] = "\tHello\tworld!\t";
    char output[100];
    char expected[100] = "\tworld!\tHello\t";
    reverseSentence(str, output);
    TRACE(output);
    ASSERT_EQUAL(strcmp(output, expected), 0);
END_TEST

BEGIN_TEST(test8_reverse_sentence)
    char str[100] = "   Leading and Trailing spaces   ";
    char output[100];
    char expected[100] = "   spaces Trailing and Leading   ";
    reverseSentence(str, output);
    TRACE(output);
    ASSERT_EQUAL(strcmp(output, expected), 0);
END_TEST

TEST_SUITE("tests")
    TEST(test1_decimalStr_to_double)
    TEST(test1_decimalStr_to_double_negative)
    TEST(test1_binaryStr_to_double)
    TEST(test2_binaryStr_to_double)
    TEST(test1_convert_by_format_to_double)
    TEST(test2_convert_by_format_to_double)
    TEST(test3_convert_by_format_to_double) 
    TEST(test4_convert_by_format_to_double) 
    TEST(test5_convert_by_format_to_double)
    TEST(test6_convert_by_format_to_double)
    TEST(test7_convert_by_format_to_double)
    TEST(test8_convert_by_format_to_double)
    TEST(test9_convert_by_format_to_double)
    TEST(test10_convert_by_format_to_double)
    TEST(test11_convert_by_format_to_double)
    TEST(test12_binary_to_double)

    TEST(test1_uninitialized)
    TEST(test2_num_of_words)
    TEST(test3_one_word)
    TEST(test4_blank_first)
    TEST(test5_many_blanks)

    TEST(test0_Stack_uninitialized)
    TEST(test1_Stack)
    TEST(test2_Stack_doubleFree)
    TEST(test3_Stack_push_pop_top)

    // TEST(test_string_to_num)
    TEST(test1_calc_phrase)
    TEST(test2_calc_phrase)

    TEST(test1_reverse_sentence)
    TEST(test2_reverse_sentence)
    TEST(test3_reverse_sentence)
    TEST(test4_reverse_sentence)
    TEST(test5_reverse_sentence)
    TEST(test6_reverse_sentence)
    TEST(test7_reverse_sentence)
    TEST(test8_reverse_sentence)

END_SUITE

