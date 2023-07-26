#include "unitronics.h"
#include <stdio.h>

#define BITS_IN_BYTE 8
#define BITS_IN_INT sizeof(int)*(BITS_IN_BYTE)

static int countDigits(int a_num);
static void buildWrongString(int a_len, char* a_cpOutPutStr);
static void convertNumToString(int a_num, int a_finalLength ,char* a_cpOutPutStr);
static int checkInputNumToStr(int a_lInputValue, int a_bStrLen, char* a_cpOutPutStr);
static void insertDecimalPoint(char* a_cpOutPutStr, int a_len, int a_startI, int a_decPoint);
static int convertToBinary(int a_num, char* a_cpOutPutStr, int a_bStrLen);
static void reverseString(char* a_cpOutPutStr, int a_size);
static int convertToHex(int a_num, char* a_cpOutPutStr, int a_bStrLen);

int bNumToStr(int a_lInputValue, int a_bStrLen, char* a_cpOutPutStr)
{
    int isNegative = 0, digitsNum = 0, finalLength = 0;
    int result = checkInputNumToStr(a_lInputValue, a_bStrLen, a_cpOutPutStr); 
    if(result != CORRECT_INPUT) {
        return result;
    }

    //case of negative number
    if(a_lInputValue < 0) {
        isNegative = 1;
    }

    digitsNum = countDigits(a_lInputValue);
    finalLength = digitsNum + isNegative;

    //output string is not long enough (including '\0')
    if(finalLength > a_bStrLen - 1) {
        buildWrongString(a_bStrLen, a_cpOutPutStr);
        return a_bStrLen;
    }

    convertNumToString(a_lInputValue, finalLength, a_cpOutPutStr);

    return finalLength;
}

int bNumToStrDeciPoint(int a_lInputValue, int a_bStrLen, int a_bDecPoint, char* a_cpOutPutStr)
{
    int isNegative = 0, digitsNum = 0, finalLength = 0;
    int isDecPoint = 0, zeroToAdd = 0;
    int result = checkInputNumToStr(a_lInputValue, a_bStrLen, a_cpOutPutStr); 
    if(result != CORRECT_INPUT) {
        return result;
    }

    //case of negative number
    if(a_lInputValue < 0) {
        isNegative = 1;
    }

    digitsNum = countDigits(a_lInputValue);

    //case of there is decPoint to add
    if(a_bDecPoint > 0) {
        isDecPoint = 1;
    }

    //add zeroes
    if(a_bDecPoint >= digitsNum) { 
        zeroToAdd = a_bDecPoint - digitsNum + 1;
        //add first zero after '-' if exist
        a_cpOutPutStr[0 + isNegative] = '0';
    }

    finalLength = digitsNum + isNegative + isDecPoint + zeroToAdd;

    //the output string is not long enough (including '\0')
    if(finalLength > a_bStrLen - 1) {
        buildWrongString(a_bStrLen, a_cpOutPutStr);
        return a_bStrLen;
    }
    convertNumToString(a_lInputValue, finalLength, a_cpOutPutStr);
    // printf("%s\n", a_cpOutPutStr);
    if(isDecPoint) {
        insertDecimalPoint(a_cpOutPutStr, finalLength, finalLength - digitsNum - 1, a_bDecPoint); 
    }
    return finalLength;
}

int bNumToStrFormat(int a_lInputValue, int a_bStrLen, int a_bDecPoint, int a_bFormat, char* a_cpOutPutStr)
{
    int finalLength, result;
    result = checkInputNumToStr(a_lInputValue, a_bStrLen, a_cpOutPutStr);
    if(result != CORRECT_INPUT) {
        return result;
    }
    switch (a_bFormat) {
        case DECIMAL : 
            finalLength = bNumToStrDeciPoint(a_lInputValue, a_bStrLen, a_bDecPoint, a_cpOutPutStr);
            break;

        case BINARY :
            finalLength = convertToBinary(a_lInputValue, a_cpOutPutStr, a_bStrLen);
            break;

        case HEX:
            finalLength = convertToHex(a_lInputValue, a_cpOutPutStr, a_bStrLen);
            break;
    }

    if(finalLength == NOT_ENOUGH_SPACE) {
        buildWrongString(a_bStrLen, a_cpOutPutStr);
        return a_bStrLen;
    }

    return finalLength;
}

int bNumToStrLeading(int a_lInputValue, int a_bStrLen, int a_bDecPoint, int a_bFormat, int a_bLeadingType, char* a_cpOutPutStr)
{
    int finalLength, result, i, j;
    char leadSign;
    result = checkInputNumToStr(a_lInputValue, a_bStrLen, a_cpOutPutStr);
    if(result != CORRECT_INPUT) {
        return result;
    }

    switch(a_bFormat) {
        case DECIMAL : 
            finalLength = bNumToStrDeciPoint(a_lInputValue, a_bStrLen, a_bDecPoint, a_cpOutPutStr);
            break;

        case BINARY :
            finalLength = convertToBinary(a_lInputValue, a_cpOutPutStr, a_bStrLen);
            break;

        case HEX:
            finalLength = convertToHex(a_lInputValue, a_cpOutPutStr, a_bStrLen);
            break;
    }

    if(finalLength == NOT_ENOUGH_SPACE) {
        buildWrongString(a_bStrLen, a_cpOutPutStr);
        return a_bStrLen;
    }

    switch (a_bLeadingType) {
        case LEADING_SPACES :
            leadSign = ' ';
            break;

        case LEADING_ZEROS:
            leadSign = '0';
            break;
    }
    if((finalLength < a_bStrLen) && (a_bLeadingType != NO_LEADING)) {
        for(i = finalLength - 1, j = a_bStrLen - 1; i >= 0; --i, --j) {
            a_cpOutPutStr[j] = a_cpOutPutStr[i];
        }
        for(i = 0; i < a_bStrLen - finalLength; ++i) {
            a_cpOutPutStr[i] = leadSign;
        }
        finalLength = a_bStrLen;
    }
    a_cpOutPutStr[finalLength] = '\0';
    return finalLength;
}

//ASSISTANCE FUNCTIONS

static int checkInputNumToStr(int a_lInputValue, int a_bStrLen, char* a_cpOutPutStr) 
{
    if(a_cpOutPutStr == NULL || a_bStrLen <= 0) {
        return 0;
    }

    //case of 0 as a_lInputValue
    if(a_lInputValue == 0) {
        if(a_bStrLen >= 2) {
            a_cpOutPutStr[0] = '0';
            a_cpOutPutStr[1] = '\0';
            return 1;
        }
        return 0;
    }
    return CORRECT_INPUT;
}

static int countDigits(int a_num)
{
    int count = 0;
    while(a_num) {
        ++count;
        a_num /= 10;
    }
    return count;
}

static void buildWrongString(int a_len, char* a_cpOutPutStr)
{
    int i;
    for (i = 0; i < a_len; ++i) {
        a_cpOutPutStr[i] = '?';
    }
    a_cpOutPutStr[a_len] = '\0';
}

static void convertNumToString(int a_num, int a_finalLength ,char* a_cpOutPutStr)
{
    int i, digit;
    if(a_num < 0) {
        a_num *= (-1);
        a_cpOutPutStr[0] = '-';
    }

    i = a_finalLength - 1;
    while(a_num != 0) {
        digit = a_num % 10;
        a_cpOutPutStr[i] = digit + '0';
        --i;
        a_num /= 10;
    }
    a_cpOutPutStr[a_finalLength] = '\0';
}

static void insertDecimalPoint(char* a_cpOutPutStr, int a_len, int a_startI, int a_decPoint)
{
    int i, pointIndex;
    pointIndex = a_len - a_decPoint - 1;
    if(a_startI > pointIndex) {
        for(i = a_startI; i > pointIndex; --i) {
            a_cpOutPutStr[i] = '0';
        }
    }

    //shift digits before point to the left
    else {
        for(i = 0; i <= pointIndex; ++i) {
            a_cpOutPutStr[i] = a_cpOutPutStr[i + 1];
        }
    }

    a_cpOutPutStr[pointIndex] = '.'; // Insert the decimal point

}

static int convertToHex(int a_num, char* a_cpOutPutStr, int a_bStrLen)
{
    const char hexDigits[] = "0123456789ABCDEF";
    int index = 0; 

    while (a_num > 0) {
        if(index + 1 > a_bStrLen) {
            return NOT_ENOUGH_SPACE;
        }
        a_cpOutPutStr[index] = hexDigits[a_num % 16];
        a_num /= 16;
        ++index;
    }

    a_cpOutPutStr[index] = '\0';
    reverseString(a_cpOutPutStr, index);
    return index;
}

static int convertToBinary(int a_num, char* a_cpOutPutStr, int a_bStrLen) 
{
	int length = 0, i;
	int isBitOn;

	for(i = 0; a_num && i < (int)BITS_IN_INT; ++i) {
        if(length + 1 > a_bStrLen) {
            return NOT_ENOUGH_SPACE;
        }
		isBitOn = a_num & 1;
		if(isBitOn) {
			a_cpOutPutStr[length] = '1';
            ++length;
		}
		else {
			a_cpOutPutStr[length] = '0';
            ++length;		
        }
        a_num >>= 1;
	}
    a_cpOutPutStr[length] = '\0';

    reverseString(a_cpOutPutStr, length);

    return length;

}

static void reverseString(char* a_cpOutPutStr, int a_size)
{
    int start, end;
    for(start = 0, end = a_size - 1; start < end; ++start, --end) {
        char temp = a_cpOutPutStr[start];
        a_cpOutPutStr[start] = a_cpOutPutStr[end];
        a_cpOutPutStr[end] = temp;
    }
}
