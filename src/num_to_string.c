#include <stdio.h>
#include "unitronics.h"

#define SWAP(left, right) { \
int temp = left;\
left = right;\
right = temp;\
}

static int convertNumToString(int a_num, int a_bStrLen, int a_base, char* a_cpOutPutStr); 
static void reverseString(int a_len, char* a_cpOutPutStr);
static void buildWrongOutput(int a_len, char* a_cpOutPutStr);
static int calcLengthByBase(int a_num, int a_bDecPoint, FORMAT_TYPE a_format);
static void convertNumToStringByBase(int a_num, int a_len, FORMAT_TYPE a_base, int a_isPoint, int a_fillLen, LEADING_TYPE a_fillSign, char* a_cpOutPutStr);
static void buildString(unsigned int a_unum, int a_base, int a_digitsNum, int a_isNegativeDeci, int a_fillLen, LEADING_TYPE a_fillSign, char* a_cpOutPutStr);
static int countDigitsDeci(int a_num, int a_base);
static int countDigitsUint(unsigned int a_num, int a_base);
static void addDecimalPoint(int a_bDecPoint, int a_finalLen, char* a_cpOutPutStr);

int bNumToStr(int a_lInputValue, int a_bStrLen, char* a_cpOutPutStr)
{
    int length;
    if(a_cpOutPutStr == NULL || a_bStrLen <= 0) {
        return 0;
    }

    //zero - special case
    if(a_lInputValue == 0) {
        a_cpOutPutStr[0] = '0';
        a_cpOutPutStr[1] = '\0';
        return 1;
    }

    length = convertNumToString(a_lInputValue, a_bStrLen, DECIMAL, a_cpOutPutStr);

    if(length == -1) {
        buildWrongOutput(a_bStrLen, a_cpOutPutStr);
        return a_bStrLen;
    }

    return length;
}

int bNumToStrDeciPoint(int a_lInputValue, int a_bStrLen, int a_bDecPoint, char* a_cpOutPutStr)
{
    int length, isPoint = 0;
    if(a_cpOutPutStr == NULL || a_bStrLen <= 0) {
        return 0;
    }

    length = calcLengthByBase(a_lInputValue, a_bDecPoint, DECIMAL);

    if(a_bStrLen < length) {
        buildWrongOutput(a_bStrLen, a_cpOutPutStr);
        return a_bStrLen;
    }

    if(a_bDecPoint > 0){
        isPoint = 1;
    }

    convertNumToStringByBase(a_lInputValue, length, DECIMAL, isPoint, 0, NO_LEADING, a_cpOutPutStr);

    if(isPoint){
        addDecimalPoint(a_bDecPoint, length, a_cpOutPutStr);
    }
    return length;
}

int bNumToStrFormat(int a_lInputValue, int a_bStrLen, int a_bDecPoint, FORMAT_TYPE a_bFormat, char* a_cpOutPutStr)
{
    int length, isPoint = 0;
    if(a_cpOutPutStr == NULL || a_bStrLen <= 0) {
        return 0;
    }

    length = calcLengthByBase(a_lInputValue, a_bDecPoint, a_bFormat);

    if(a_bStrLen < length) {
        buildWrongOutput(a_bStrLen, a_cpOutPutStr);
        return a_bStrLen;
    }

    if((a_bDecPoint > 0) && (a_bFormat == DECIMAL || a_bFormat == DECIMAL_WITH_SIGN)){
        isPoint = 1;
    }

    convertNumToStringByBase(a_lInputValue, length, a_bFormat, isPoint, 0, NO_LEADING, a_cpOutPutStr);

    if(isPoint){
        addDecimalPoint(a_bDecPoint, length, a_cpOutPutStr);
    }
    return length;
}

int bNumToStrLeading(int a_lInputValue, int a_bStrLen, int a_bDecPoint, FORMAT_TYPE a_bFormat, LEADING_TYPE a_bLeadingType, char* a_cpOutPutStr)
{
    int length, isPoint = 0;
    int fillLength = 0;
    if(a_cpOutPutStr == NULL || a_bStrLen <= 0) {
        return 0;
    }

    length = calcLengthByBase(a_lInputValue, a_bDecPoint, a_bFormat);
    if(a_bStrLen < length) {
        buildWrongOutput(a_bStrLen, a_cpOutPutStr);
        return a_bStrLen;
    }

    if(a_bLeadingType != NO_LEADING) {
        fillLength = a_bStrLen - length;
    }

    if((a_bDecPoint > 0) && (a_bFormat == DECIMAL || a_bFormat == DECIMAL_WITH_SIGN)){
        isPoint = 1;
    }

    convertNumToStringByBase(a_lInputValue, length, a_bFormat, isPoint, fillLength, a_bLeadingType, a_cpOutPutStr);
    
    length += fillLength;

    if(isPoint){
        addDecimalPoint(a_bDecPoint, length, a_cpOutPutStr);
    }
    return length;
}

//ASSISTANCE FUNCTIONS
static void convertNumToStringByBase(int a_num, int a_len, FORMAT_TYPE a_base, int a_isPoint, int a_fillLen, LEADING_TYPE a_fillSign, char* a_cpOutPutStr)
{
    int isNegativeDeci = 0; 
    int digitsNum = a_len;

    //num of divides need to be without the minus sign and point
    if(a_isPoint) {
        --digitsNum;
    }
    if((a_num < 0) && (a_base == DECIMAL)) {
        isNegativeDeci = 1;
        a_num = -a_num;
        --digitsNum;
    }
    else if(a_base == DECIMAL_WITH_SIGN) {
        --digitsNum;
    }
    buildString((unsigned int)a_num, a_base, digitsNum, isNegativeDeci, a_fillLen, a_fillSign, a_cpOutPutStr);

    reverseString(a_len + a_fillLen - a_isPoint, a_cpOutPutStr);
}

static void buildString(unsigned int a_unum, int a_base, int a_digitsNum, int a_isNegativeDeci, int a_fillLen, LEADING_TYPE a_fillSign, char* a_cpOutPutStr)
{
    int i, digit;
    int isSigned = 0;
    if(a_base == DECIMAL_WITH_SIGN){
        isSigned = 1;
        a_base = DECIMAL;
    }
    for(i = 0; i < a_digitsNum; ++i) {
        digit = a_unum % a_base;
        if(digit > 9) {
            a_cpOutPutStr[i] = digit - 10 + 'A';
        }
        else {
            a_cpOutPutStr[i] = digit + '0';
        }
        a_unum /= a_base;
    }
    if(a_fillSign == '0') {
        while(a_fillLen) {
            a_cpOutPutStr[i] = a_fillSign;
            --a_fillLen;
            ++i;
        }
    }

    if(a_isNegativeDeci) {
        a_cpOutPutStr[i] = '-';
        ++i;
    }
    else if(isSigned) {
        a_cpOutPutStr[i] = '+';
        ++i;
    }

    if(a_fillSign == ' ') {
        while(a_fillLen) {
            a_cpOutPutStr[i] = a_fillSign;
            --a_fillLen;
            ++i;
        }
    }

    a_cpOutPutStr[i] = '\0';
}

static int convertNumToString(int a_num, int a_bStrLen, int a_base, char* a_cpOutPutStr)
{
    int length = 0, isNegative = 0; 
    int digit; 

    if(a_num < 0) {
        //max len must be greater or equal to 2
        if(a_bStrLen == 1) {
            return -1;
        }
        isNegative = 1;
        a_num = -a_num;
    }

    while(a_num) {
        digit = a_num % a_base;
        a_cpOutPutStr[length] = digit + '0';
        ++length;

        //check if the current length is not bigger thant the max possible
        if(a_bStrLen < length) {
            return -1;
        }
        a_num /= a_base;
    }

    if(isNegative) {
        a_cpOutPutStr[length] = '-';
        ++length;
        if(a_bStrLen < length) {
            return -1;
        }
    }

    a_cpOutPutStr[length] = '\0';

    reverseString(length, a_cpOutPutStr);

    return length;
}

static void reverseString(int a_len, char* a_cpOutPutStr)
{
    int start = 0, end = a_len - 1;
    while(start < end) {
        SWAP(a_cpOutPutStr[start], a_cpOutPutStr[end]);
        --end;
        ++start;
    }
}

static void buildWrongOutput(int a_len, char* a_cpOutPutStr)
{
    int i;
    for(i = 0; i < a_len; ++i) {
        a_cpOutPutStr[i] = '?';
    }
    a_cpOutPutStr[a_len] = '\0';
}

static int calcLengthByBase(int a_num, int a_bDecPoint, FORMAT_TYPE a_format)
{
    int addZeros = 0, isPoint = 0, isSigned = 0;
    int digitsNum, finalLength;

    //change to unsigned for HEX and BINARY
    if((a_num < 0) && (a_format == HEX || a_format == BINARY)) {
        digitsNum = countDigitsUint((unsigned int)a_num, a_format);
    }
    //for decimal - signed int
    else {
        digitsNum = countDigitsDeci(a_num, a_format);
    }

    //there is decimal point
    if((a_format == DECIMAL || a_format == DECIMAL_WITH_SIGN) && (a_bDecPoint > 0)){
        isPoint = 1;
        //there are additional zeros
        if(digitsNum <= a_bDecPoint) {
            addZeros = a_bDecPoint - digitsNum + 1; //additional 1 for the zero on the left of the decimal point
        }
    }

    //add sign
    if((a_num < 0 && a_format == DECIMAL) || a_format == DECIMAL_WITH_SIGN) {
        isSigned = 1;
    }

    finalLength = digitsNum + addZeros + isPoint + isSigned; //additional 1 for the decimal point and sign
    return finalLength;
}

static int countDigitsDeci(int a_num, int a_base)
{
    int count = 0;
    if(a_base == DECIMAL_WITH_SIGN) {
        a_base = DECIMAL;
    }

    //zero = special case
    if(a_num == 0) {
        return 1;
    }

    while(a_num){
        a_num /= a_base; 
        ++count;
    }

    return count;
}

static int countDigitsUint(unsigned int a_num, int a_base)
{
    int count = 0;

    while(a_num){
        a_num /= a_base; 
        ++count;
    }

    return count;
}

static void addDecimalPoint(int a_bDecPoint, int a_finalLen, char* a_cpOutPutStr)
{
    int i, pointIndex;
    //shift right include '\0' - a_bDecPoint of digits
    for(i = 0; i <= a_bDecPoint; ++i) {
        a_cpOutPutStr[a_finalLen - i] = a_cpOutPutStr[a_finalLen - i - 1]; 
    }

    pointIndex = a_finalLen - a_bDecPoint - 1;
    a_cpOutPutStr[pointIndex] = '.';
}