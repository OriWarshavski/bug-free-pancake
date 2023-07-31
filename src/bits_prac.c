#include "bits_prac.h"

#define BYTE 8
#define INT (BYTE*4)

#define MAX_CHAR 256
#define NOT_EQUAL_BITS(left, right) (((left != 0) && (right == 0)) || ((left == 0) && (right != 0)))

unsigned char reverseChar(unsigned char a_num) 
{
    unsigned char leftBit, rightBit;
    int i;
    for(i = 0; i < BYTE / 2; ++i) {
        leftBit = a_num & (1 << (BYTE - 1 - i));
        rightBit = a_num & (1 << i);
        if(NOT_EQUAL_BITS(leftBit, rightBit)) {
            a_num ^= (1 << (BYTE - 1 - i));
            a_num ^= (1 << i);
        }
    }
    return a_num;
}

static void buildReverseTable(unsigned char* a_table)
{
    int i;
    for(i = 0; i < MAX_CHAR; ++i) {
        a_table[i] = reverseChar(i);
    }

}

unsigned int reverseBits(unsigned int a_num)
{
    int i;
    static int flag = 0;
    unsigned int result = 0;
    static unsigned char reverseTable[MAX_CHAR];
    if(!flag) {
        buildReverseTable(reverseTable);
        flag = 1;
    }
    for(i = 0; i < INT / BYTE; ++i) {
        result <<= BYTE;
        result |= reverseTable[a_num & 0xff];
        a_num >>= BYTE;
    }
    return result;
}
