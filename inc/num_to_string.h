#pragma once

#define CORRECT_INPUT 2
#define NOT_ENOUGH_SPACE -1

typedef enum FORMAT_TYPE {
    DECIMAL = 10,
    DECIMAL_WITH_SIGN,
    HEX = 16,
    BINARY = 2
} FORMAT_TYPE;

typedef enum LEADING_TYPE {
    NO_LEADING = -1,
    LEADING_SPACES = ' ',
    LEADING_ZEROS = '0'
} LEADING_TYPE;

/** 
 * @brief Builds a string of input integer
 * @param a_lInputValue: input integer
 * @param a_bStrLen: max length of the output string
 * @param a_cpOutPutStr: the output string
 * @return the actual length of the output string
 * @warning if the maximum value is less then the output string(include '\0') - '?' string will be return 
 *          in the maximum length
 *          return 0 if a_cpOutPutStr uninitialized or a_bStrLen == 0;
 */
int bNumToStr(int a_lInputValue, int a_bStrLen, char* a_cpOutPutStr);

/** 
 * @brief Builds a string of the input integer with add of decimal point in a_bDecPoint
 * @param a_lInputValue: input integer
 * @param a_bStrLen: max length of the output string
 * @param a_bDecPoint: number of digits before the decimal point
 * @param a_cpOutPutStr: the output string
 * @return the actual length of the output string
 * @warning if the maximum value is less then the output string(include '\0') - '?' string will be return 
 *          in the maximum length
 *          return 0 if a_cpOutPutStr uninitialized or a_bStrLen == 0;
 */
int bNumToStrDeciPoint(int a_lInputValue, int a_bStrLen, int a_bDecPoint, char* a_cpOutPutStr);
int bNumToStrDeciPointV2(int a_lInputValue, int a_bStrLen, int a_bDecPoint, char* a_cpOutPutStr);

/** 
 * @brief Builds a string of the input integer in the format was chosen
 * @param a_lInputValue: input integer
 * @param a_bStrLen: max length of the output string
 * @param a_bDecPoint: number of digits before the decimal point
 * @param a_bformat: chosen format from the enum list
 * @param a_cpOutPutStr: the output string
 * @return the actual length of the output string
 * @warning if the maximum value is less then the output string(include '\0') - '?' string will be return 
 *          in the maximum length
 *          return 0 if a_cpOutPutStr uninitialized or a_bStrLen == 0;
 */
int bNumToStrFormat(int a_lInputValue, int a_bStrLen, int a_bDecPoint, FORMAT_TYPE a_bFormat, char* a_cpOutPutStr);

/** 
 * @brief Builds a string of the input integer in the format was chosen and fill it if necessery
 * @param a_lInputValue: input integer
 * @param a_bStrLen: max length of the output string
 * @param a_bDecPoint: number of digits before the decimal point
 * @param a_bformat: chosen format from the enum list
 * @param a_bLeadingType: chosen filling from the enum list

 * @param a_cpOutPutStr: the output string
 * @return the actual length of the output string
 * @warning if the maximum value is less then the output string(include '\0') - '?' string will be return 
 *          in the maximum length
 *          return 0 if a_cpOutPutStr uninitialized or a_bStrLen == 0;
 */
int bNumToStrLeading(int a_lInputValue, int a_bStrLen, int a_bDecPoint, FORMAT_TYPE a_bFormat, LEADING_TYPE a_bLeadingType, char* a_cpOutPutStr);